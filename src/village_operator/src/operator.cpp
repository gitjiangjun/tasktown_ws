// ROS 2 C++头文件
#include "rclcpp/rclcpp.hpp"
#include <rclcpp/client.hpp>
#include <iostream>  // 打印txt文档用
#include <fstream>   // 包含文件流头文件，打印txt文档用
#include <cstdlib>   // 标准库头文件
#include <ctime>     // 时间头文件
#include <vector>    // 向量头文件
#include <algorithm> // 算法头文件
#include <chrono>    // 时间头文件
#include <memory>    // 内存管理头文件
#include <thread>    // 时间管理
#include <future>             // 包含用于std::async和std::future的头文件，20240806新增
#include <mutex>              // 包含用于std::lock_guard的头文件，20240806新增
#include <condition_variable> // 记录操作员状态变化头文件，20240806新增
#include <limits>             // 需要包含此头文件以使用 std::numeric_limits
#include <cmath>              // 包含数学函数库以使用 exp()
#include <fstream> // 引入文件流库

// 1. 导入服务接口
// 任务更新的服务接口 [创建完srv文件要记得编译才会出现"task_update.hpp"!!!]
#include "village_interfaces/srv/task_update.hpp"
// 任务分配的服务接口
#include "village_interfaces/srv/task_assign.hpp"



// 20240914修改：任务数据类型修改为包含任务到达时间的pair
std::vector<std::pair<std::vector<int32_t>, std::chrono::steady_clock::time_point>> global_task_sequence; 

// 20240819新增：用于保护全局任务序列的互斥锁
std::mutex global_task_sequence_mutex;

bool global_signal;
std::mutex global_signal_mutex;


// 写俩占位符，用于创建客户端时绑定回调函数
// 回调函数有request和response，所以是两个占位符
using std::placeholders::_1;
using std::placeholders::_2;

// 使用标准命名空间
using namespace std;
//KM算法，去他妈的
class KMAlgorithm
{
private:
    size_t n;                                     // 固定的操作员数量（左边顶点数）
    size_t m;                                     // 任务数量（右边顶点数）
    std::vector<std::vector<double>> rewards;     // 存储收益矩阵
    std::vector<double> lx, ly;                   // 左边和右边顶点的标号，lx对应操作员，ly对应任务
    std::vector<int> match;                       // 记录右边顶点（任务）匹配的左边顶点（操作员）
    std::vector<bool> visitedX, visitedY;         // 记录左右顶点是否被访问
    std::vector<double> slack;                    // 松弛变量，用于更新顶点标号
    int left_size;

public:
    // 构造函数，传入收益矩阵，并初始化相关数据
    KMAlgorithm(std::vector<std::vector<double>> reward_matrix)//其实相当于权重信息  改动前面const，中间&
    {
        left_size=reward_matrix[0].size();
        // 假设 reward_matrix 是一个二维 vector
        if (left_size < 3) {
            // 将新列添加到矩阵中
            for(int i=0;i < (3-left_size);i++)
            {
                for (auto &row : reward_matrix) {
                    row.push_back(0);
                }
            }
        }
        n = reward_matrix.size();  // 左边顶点数量：固定的操作员数量，返回矩阵的行数，有几行就有几个操作员
        m = reward_matrix[0].size();  // 右边顶点数量：动态变化的任务数量
        rewards = reward_matrix;  // 收益矩阵

        lx.resize(n, 0);  // 初始化左边顶点标号（操作员）
        ly.resize(m, 0);  // 初始化右边顶点标号（任务）
        match.resize(m, -1);  // 初始化任务未匹配状态
        visitedX.resize(n, false);  // 初始化操作员未访问状态
        visitedY.resize(m, false);  // 初始化任务未访问状态
        slack.resize(m, std::numeric_limits<double>::infinity());  // 初始化松弛变量

        // 初始化左边顶点标号为操作员可以获得的最大收益
        for (size_t i = 0; i < n; ++i)
        {
            lx[i] = *std::max_element(reward_matrix[i].begin(), reward_matrix[i].end());
        }
    }

    // 主函数：执行KM算法，找到最大收益的任务分配方案
    double getMaxReward()
    {
        // 遍历每个操作员，尝试为其分配任务
        for (size_t x = 0; x < n; ++x)
        {
            while (true)
            {
                visitedX.assign(n, false);
                visitedY.assign(m, false);
                slack.assign(m, std::numeric_limits<double>::infinity());

                if (dfs(x))  // 如果为当前操作员找到匹配任务，则跳出循环
                    break;

                // 否则需要调整顶点标号
                double delta = std::numeric_limits<double>::infinity();
                for (size_t y = 0; y < m; ++y)
                {
                    if (!visitedY[y])
                    {
                        delta = std::min(delta, slack[y]);  // 找到最小的松弛量
                    }
                }

                // 更新顶点标号
                for (size_t i = 0; i < n; ++i)
                {
                    if (visitedX[i])
                    {
                        lx[i] -= delta;
                    }
                }

                for (size_t j = 0; j < m; ++j)
                {
                    if (visitedY[j])
                    {
                        ly[j] += delta;
                    }
                    else
                    {
                        slack[j] -= delta;
                    }
                }
            }
        }

        // 计算最大总收益
        double max_reward = 0;
        for (size_t y = 0; y < m; ++y)
        {
            if (match[y] != -1)
            {
                max_reward += rewards[match[y]][y];  // 计算匹配后的总收益
            }
        }
        return max_reward;
    }

    // 获取匹配结果
    std::vector<int> getMatchingResult() //const 改动
    {
        if(left_size < 3 && left_size != 0){
            match.resize(left_size);
        }
        return match;  // 返回匹配结果：任务y对应的操作员是match[y]
    }

private:
    // 深度优先搜索寻找增广路径
    bool dfs(size_t x)
    {
        visitedX[x] = true;  // 标记操作员x被访问
        for (size_t y = 0; y < m; ++y)
        {
            if (visitedY[y])
                continue;  // 如果任务y已经被访问，跳过

            double gap = lx[x] + ly[y] - rewards[x][y];  // 计算松弛值
            if (gap < 1e-9)  // 如果松弛值接近0，意味着可以匹配
            {
                visitedY[y] = true;  // 标记任务y被访问
                // 如果任务y未被匹配，或者它的匹配操作员可以找到新的匹配
                if (match[y] == -1 || dfs(match[y]))
                {
                    match[y] = x;  // 将任务y分配给操作员x
                    return true;  // 匹配成功
                }
            }
            else
            {
                slack[y] = std::min(slack[y], gap);  // 更新松弛变量
            }
        }
        return false;  // 匹配失败
    }
};


// 0 (0.1) 操作员（复制C++程序，这里没有改动）
// Class Operator
class Operator
{
private:
    // 操作员的成功率，一个double类型的动态数组，保存double类型的数据
    vector<double> success_rates; // 操作员成功率

public:
    // 操作员构造函数，接收成功率vector<double> rates作为参数，初始化success_rates成员变量
    // 并将传入的rates直接赋值给success_rates
    Operator(vector<double> rates) : success_rates(rates) {}

    // 获取操作员对应任务上的成功率
    double getSuccessRate(int taskIndex) const
    { return success_rates[taskIndex]; }
};

// 0(0.2)任务（复制C++程序，这里没有改动）
// Class Task
class Task
{
private:
    int value; // 任务的价值
    int time;  // 任务的执行时间

public:
    // 任务构造函数，接收价值和执行时间作为参数
    Task(int val, int t) : value(val), time(t) {}
    // 获取任务的价值
    int getValue() const
    { return value; }

    // 获取任务的执行时间
    int getTime() const
    { return time; }
};

/*
  0(0.3)（复制C++程序，这里没有改动）
  任务分配计算，管理任务分配，计算分配任务的总时间和总收益
  包括任务分配矩阵，任务执行总时间，任务总收益
*/

//0(0.4)没有改动
// Class TaskAssignmentManager
class TaskAssignmentManager
{
private:

    // vector<vector<int>>创建二维向量，任务分配矩阵
    vector<vector<int>> taskAssignment; // 创建二维向量，任务分配矩阵
    vector<vector<int>> taskValueMatrix; // 创建二维向量，任务价值矩阵，新增
    vector<int> task_index_record;
    vector<int> operatorTimes;           // 20240521：记录每个操作员的总执行时间（记录任务执行总时间）
    double totalReward;                  // 总收益

    // Flag：用bool类型逻辑值Flag表示操作员状态和任务完成情况
    vector<bool> operatorBusyFlags;   // 记录每个操作员的忙碌状态
    vector<bool> taskCompletionFlags; // 记录每个任务的完成状态
    mutable std::mutex cv_mtx;             // 互斥变量

    mutable std::condition_variable cv;    // 条件变量，20240806新增
public:
    // 初始化任务执行总时间和任务总收益，totalTime和totalReward的初始值都为0
    TaskAssignmentManager() : totalReward(0) {}

    /*
       initializeMatrix接受两个参数：operators（操作员数量）和tasks（任务数量）。
       初始化taskAssignment矩阵，使其具有operators行和tasks列，并将所有元素初始化为0。
       初始化operatorTimes向量，使其大小为operators，并将所有元素初始化为0。

       已经这这定义了initializeMatrix（操作员数量，任务数量）,后面只给出操作员数量就可以了
    */
    void initializeMatrix(size_t operators, size_t tasks)
    {
        task_index_record = vector<int>(tasks,0);

        taskAssignment = vector<vector<int>>(operators, vector<int>(tasks, 0));

        // 初始化任务价值矩阵，新增
        taskValueMatrix = vector<vector<int>>(operators, vector<int>(tasks, 0));

        // 初始化任务执行总时间
        operatorTimes = vector<int>(operators, 0); // 20240521：记录任务执行总时间
        // 初始化操作员和任务状态
        operatorBusyFlags = vector<bool>(operators, false); // 记录操作员忙碌状态，false表示空闲
        taskCompletionFlags = vector<bool>(tasks, false);   // 记录任务完成状态，false表示空闲
    }

    // assignTask函数作用是更新任务分配状态、累计任务时间和计算总收益
    void assignTask(int operatorIndex, int taskIndex, int taskTime, double successRate, int taskValue, double time_interval)
    {
        task_index_record.push_back(taskIndex);
        /* exp( - time_interval.count()/12.0
          标记操作员分配了该任务
          assignTask函数中，将任务分配矩阵中对应操作员和任务的元素设置为1，表示该任务已经被分配
        */
        taskAssignment[operatorIndex][task_index_record.size()-1] = 1; // 标记操作员分配了该任务

        // 20240521新增：更新操作员的总执行时间（记录任务执行总时间的）：累计执行任务总时间
        operatorTimes[operatorIndex] += taskTime; // 累计执行任务总时间

        // 任务价值矩阵：更新任务价值矩阵
        if (successRate > static_cast<double>(rand()) / RAND_MAX) // 使用随机数模拟任务成功与否
        {
            taskValueMatrix[operatorIndex][task_index_record.size()-1] = taskValue; // 任务成功，填入任务价值
        }
        else
        {
            taskValueMatrix[operatorIndex][task_index_record.size()-1] = 0; // 任务失败，填入0
        }

        // 计算总收益，将当前任务的收益累加到totalReward中
        totalReward += successRate * taskValue * exp(-time_interval/120.0);  // 修改后的收益公式
        operatorBusyFlags[operatorIndex] = true; // 标记操作员为忙碌状态，true表示忙碌
    }

    // 向taskAssignment矩阵添加一个新的任务列
    void addNewTaskColumn()
    {
        // 遍历taskAssignment矩阵的每一行，并在每一行的末尾添加一个值为0的新元素
        for (auto &row : taskAssignment)
        {
            row.push_back(0);
        }

        // 价值矩阵：向taskValueMatrix矩阵添加一个新的任务列
        for (auto &row : taskValueMatrix)
        {
            row.push_back(0);
        }

        // 标记任务没有完成
        taskCompletionFlags.push_back(false);
    }

    const vector<int> &getTaskIndexRecord() const
    { return task_index_record; }
    /*
      获取任务分配矩阵
      const vector<vector<int>>& 作为函数的返回类型
      表示 getTaskAssignment 函数返回一个对二维整数向量矩阵的常量引用
    */
    const vector<vector<int>> &getTaskAssignment() const
    { return taskAssignment; }

    // 价值矩阵：获取任务价值矩阵
    const vector<vector<int>> &getTaskValueMatrix() const
    { 
        return taskValueMatrix; 
    }

    // 获取任务执行总时间的引用，允许修改总时间
    int getTotalTime() const
    { return *max_element(operatorTimes.begin(), operatorTimes.end()); }

    // 获取任务总收益
    double getTotalReward() const
    { return totalReward; }

    // 检查操作员是否正在执行任务（处于忙碌状态）
    bool isOperatorBusy(int operatorIndex) const
    { 
        std::lock_guard<std::mutex> lock(cv_mtx);//改动
        if(operatorBusyFlags[operatorIndex])
        {
            cv.notify_all();
            return true;
        }
        else
        {
            cv.notify_all();
            return false;
        }
        
    }
    // 设置操作员为空闲状态
    void setOperatorIdle(int operatorIndex)
    { 
        {
            std::lock_guard<std::mutex> lock(cv_mtx); // 使用互斥锁检查操作员是否忙碌
            operatorBusyFlags[operatorIndex] = false; 
        }
        cv.notify_all();
    }
    // 检查任务是否完成
    bool isTaskCompleted(int taskIndex) const
    { return taskCompletionFlags[taskIndex]; }
    // 设置任务为完成状态
    void completeTask()
    { taskCompletionFlags[task_index_record.size()-1] = true; }
};

/*-----------------------------------好戏开场-------------------------------*/ 

// 20240524新增：全局变量，存储客户端发送来的随机任务序列
// 20240914修改：任务数据类型修改为包含任务到达时间的pair
//std::vector<std::pair<std::vector<int32_t>, std::chrono::steady_clock::time_point>> global_task_sequence; 

// 20240819新增：用于保护全局任务序列的互斥锁
//std::mutex global_task_sequence_mutex;换位置

//0(0.5)没有改动
// 20240607新增：创建任务更新节点，TaskUpdateNode，继承ROS2 rclcpp::Node
class TaskUpdateNode : public rclcpp::Node
{
public:
    TaskUpdateNode(const std::string &name) : Node(name),is_first(true)
    {
        // 创建任务更新服务
        task_update_service = this->create_service<village_interfaces::srv::TaskUpdate>("task_update",
                                                                                        std::bind(&TaskUpdateNode::handle_task_update_sequence_callback, this, _1, _2));

        //------------------------------------------------------------------------------------------------------
        // 创建任务分配客户端
        task_assign_client = this->create_client<village_interfaces::srv::TaskAssign>("task_assignment");
    }

private:
    bool is_first;
    // 声明任务更新服务
    rclcpp::Service<village_interfaces::srv::TaskUpdate>::SharedPtr task_update_service;
    // 声明任务分配服务
    rclcpp::Client<village_interfaces::srv::TaskAssign>::SharedPtr task_assign_client;

    //任务更新回调函数
    void handle_task_update_sequence_callback(
        const std::shared_ptr<village_interfaces::srv::TaskUpdate::Request> request,
        const std::shared_ptr<village_interfaces::srv::TaskUpdate::Response> response)
    {
        // 20240914新增：记录任务的到达时间
        auto task_arrival_time = std::chrono::steady_clock::now();

        int signal;
        std::unique_lock<std::mutex> task_lock(global_task_sequence_mutex); // 加锁保护全局任务序列
        if(request->tasks[1]!=0)
        {
            // 将新任务添加到全局任务序列，并标记任务到达时间
            global_task_sequence.push_back({request->tasks, task_arrival_time});  // 20240914新增
            task_lock.unlock();
        }
        signal=request->tasks[1];
        std::cout<<"signal:"<<signal<<std::endl;
        if(signal == 0)
        {
            std::unique_lock<std::mutex> signal_lock(global_signal_mutex,std::defer_lock); // 加锁保护全局任务序列
            signal_lock.lock();
            global_signal=true;
            std::cout<<"global_signal"<<global_signal<<std::endl;
            signal_lock.unlock();
            return;  
        }

        // 设置响应结果
        response->success = true; // 或根据实际更新情况设置

        // 打印日志
        RCLCPP_INFO(this->get_logger(), "任务序列更新成功,将任务更新结果返回给客户端");

        // 打印全局任务序列，横向扩展
        RCLCPP_INFO(this->get_logger(), "当前全局任务序列：");
        //std::unique_lock<std::mutex> lock(global_task_sequence_mutex); // 加锁保护全局任务序列
        task_lock.lock();
        for (size_t i = 0; i < 6; ++i) // 假设每个任务都有6个属性
        {
            std::stringstream ss;
            {
                //std::lock_guard<std::mutex> lock(global_task_sequence_mutex); // 加锁保护全局任务序列
                for (size_t j = 0; j < global_task_sequence.size(); ++j)
                {
                    ss << global_task_sequence[j].first[i] << "\t"; // 每个任务值之间用TAB分隔
                }
            }
            RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
        }
        task_lock.unlock();

        // 在任务序列更新后，构造异步请求，调用任务分配服务
        auto task_assign_request = std::make_shared<village_interfaces::srv::TaskAssign::Request>();
        {
            //std::lock_guard<std::mutex> lock(global_task_sequence_mutex); // 加锁保护全局任务序列
            task_lock.lock();
            for (const auto &task : global_task_sequence)
            {
                task_assign_request->tasks.insert(task_assign_request->tasks.end(), task.first.begin(), task.first.end());
            }
            task_lock.unlock();

        }
        if(is_first){

            // 使用回调函数处理异步请求的响应
            task_assign_client->async_send_request(task_assign_request,
                                                [this](rclcpp::Client<village_interfaces::srv::TaskAssign>::SharedFuture response_future)
                                                {
                                                    auto response = response_future.get();
                                                    // 在这里处理任务分配服务的响应，如果需要的话
                                                    RCLCPP_INFO(this->get_logger(), "任务分配服务响应已收到");
                                                });
            is_first=false;                            
            std::unique_lock<std::mutex> signal_lock(global_signal_mutex,std::defer_lock); // 加锁保护全局任务序列
            signal_lock.lock();
            global_signal=false;
            signal_lock.unlock();  
        }



    }
};

// 创建一个TaskAssignServer的类，继承自ROS2的rclcpp::Node
// Class TaskAssignServer
class TaskAssignServer : public rclcpp::Node
{
public:
    // 构造函数，(const std::string &name)为构造函数参数列表，参数名为name
    // manager是成员初始化列表的一部分
    // manager作为任务分配管理器对象，用于封装和操作与任务分配相关的所有数据和逻辑
    // 通过manager() 进行初始化，为后续的任务分配作准备
    TaskAssignServer(const std::string &name) : Node(name), manager()
    {
        // 初始化操作员成功率和任务信息
        initOperators();
        initTasks();
        // 初始化任务分配矩阵的大小
        manager.initializeMatrix(operators_.size(), 0);

        // 初始化operatorOnMissionFlags，大小与操作员数量相同，初始值均为false（标记飞行任务专用）
        OperatorOnMissionFlags = std::vector<bool>(operators_.size(), false);

        // 3.(3.1)声明并创建服务端,在这里只是创建服务端，也就是对服务端实例化
        // 在C++中如果用成员函数作为回调函数必须使用std::bind把成员函数转化为回调函数
        task_assign_service = this->create_service<village_interfaces::srv::TaskAssign>("task_assignment",
                                                                                        std::bind(&TaskAssignServer::handle_task_assign_request_callback, this, _1, _2));
        // 打印服务端任务分配程序启动提示
        RCLCPP_INFO(this->get_logger(), "任务分配服务已启动，准备对客户端发来的随机任务序列进行分配");
    }

private:


    rclcpp::Service<village_interfaces::srv::TaskAssign>::SharedPtr task_assign_service; // 任务分配服务对象

    std::vector<Operator> operators_; // 修改为二维向量
    std::vector<Task> tasks_info;     // 修改为Task对象的向量
    TaskAssignmentManager manager; // 管理任务分配矩阵

    std::vector<bool> operatorBusyFlags; // 操作员空闲状态标志（可以删除）

    // 新增：用于跟踪哪些操作员正在执行特殊任务的标志（标记飞行任务专用）
    std::vector<bool> OperatorOnMissionFlags;
    //std::condition_variable cv;    // 条件变量，20240806新增
    //std::mutex cv_mtx;             // 互斥变量  改动，互斥锁放错位置
    // 初始化操作员成功率
    void initOperators()
    {
        operators_ = {
            Operator({0.9, 0.8, 0.7, 0.6}),
            Operator({0.8, 0.9, 0.8, 0.7}),
            Operator({0.8, 0.8, 0.7, 0.9})};

        // 初始化操作员空闲状态标志，全部初始化为true，表示初始状态下所有操作员都是空闲的
        operatorBusyFlags = std::vector<bool>(operators_.size(), false);
    }

    // 初始化任务信息
    void initTasks()
    {
        tasks_info = {Task(4, 100000000), Task(2, 20), Task(1, 10), Task(3, 30)};
    }

    // 2.创建服务端回调函数，也就是创建任务分配回调函数
    void handle_task_assign_request_callback(const village_interfaces::srv::TaskAssign::Request::SharedPtr request,
                                             const village_interfaces::srv::TaskAssign::Response::SharedPtr response)
    {

        // 4.编写回调函数逻辑处理请求
        // 打印接收任务分配请求
        RCLCPP_INFO(this->get_logger(), "收到来自客户端的任务分配请求，准备对不同类型的任务进行分配.");
        (void)request;  // 明确告知编译器，request参数暂时未使用
    // 分配任务时，不需要传递 request->tasks，直接调用 assignTasks，并传递 response
        assignTasks(response);
        // 打印任务分配完成信息
        RCLCPP_INFO(this->get_logger(), "已完成任务分配，将任务分配结果返回给客户端.");
    }

    // 分配任务给操作员，任务分配算法核心逻辑！！！
void assignTasks(std::shared_ptr<village_interfaces::srv::TaskAssign::Response> response)
{
    std::unique_lock<std::mutex> task_lock(global_task_sequence_mutex,std::defer_lock); //暂时不上锁// 使用互斥锁来保护对全局任务序列的访问
    std::unique_lock<std::mutex> signal_lock(global_signal_mutex,std::defer_lock); // 加锁保护全局任务序列
    bool tt;
loop:
    while (true) // 无限循环：持续检查操作员和任务状态，并对任务进行分配
    {
        bool allTasksAssigned = true; // 初始化allTasksAssigned=true，跟踪并标记是否所有任务都已经分配

        //RCLCPP_INFO(this->get_logger(), "开始任务分配循环，检查所有操作员和任务。");改动
        //std::unique_lock<std::mutex> task_lock(global_task_sequence_mutex); // 加锁保护全局任务序列

       // vector<vector<double>> reward_matrix(3, vector<double>(global_task_sequence.size(), 0.0)); // 任务收益矩阵，行数固定为3（操作员数量），列数根据当前任务数动态调整
        vector<int> idle_operators;                                                               // 存储空闲的操作员索引
        vector<size_t> task_indices;  
        vector<int> busy_operators;                                                            // 未处理的任务索引
        //task_lock.unlock();
        // 遍历所有操作员，检查哪些操作员空闲
        for (size_t operator_index = 0; operator_index < operators_.size(); ++operator_index)
        {
            //std::unique_lock<std::mutex> lock(cv_mtx); // 使用互斥锁检查操作员是否忙碌
            if (!manager.isOperatorBusy(operator_index))
            {
                idle_operators.push_back(operator_index); // 记录空闲操作员
                RCLCPP_INFO(this->get_logger(), "操作员 %d 已空闲，可以分配任务。", operator_index);
            }
            else
            {
                busy_operators.push_back(operator_index); // 记录忙碌的操作员
                //RCLCPP_INFO(this->get_logger(), "操作员 %d 正在处理任务，无法分配任务。", operator_index);
            }

        }

        // 如果没有空闲操作员，结束循环
        if (idle_operators.empty())
        {
            //RCLCPP_INFO(this->get_logger(), "没有空闲的操作员，等待空闲。");//改动
            //break;改动
            continue;
        }

        // 如果有空闲操作员，三名操作员都要一起遍历任务
        RCLCPP_INFO(this->get_logger(), "至少有一个操作员空闲，所有操作员一起遍历任务。");

        //std::unique_lock<std::mutex> task_lock(global_task_sequence_mutex); // 使用互斥锁来保护对全局任务序列的访问
        int task_count = 0;
        task_lock.lock();
        for (size_t i = 0; i < global_task_sequence.size(); ++i)
        {
            if (global_task_sequence[i].second != std::chrono::steady_clock::time_point()) // 如果任务未被处理
            {
                task_count++;
                task_indices.push_back(i); // 记录未处理任务的索引
                //allTasksAssigned = false;
            }
        }
        task_lock.unlock();
        /*if (allTasksAssigned)
        {
            RCLCPP_INFO(this->get_logger(), "所有任务都已分配，结束循环。");
            break;
        }*/
       if(task_count == 0)
       {
            RCLCPP_INFO(this->get_logger(), "没有未处理的任务，结束循环。");
            tt=global_signal;
            //std::cout<<"global_signal"<<global_signal<<std::endl;
            break;
       }
        vector<vector<double>> reward_matrix(3, vector<double>(task_count, 0.0)); // 任务收益矩阵，行数固定为3（操作员数量），列数根据当前任务数动态调整
         //改动
         task_lock.lock();
        // 遍历全局任务序列，构建收益矩阵
        for (size_t i = 0; i < global_task_sequence.size(); ++i)
        {
            //std::lock_guard<std::mutex> task_lock(global_task_sequence_mutex); // 使用互斥锁来保护对全局任务序列的访问

            if (global_task_sequence[i].second == std::chrono::steady_clock::time_point()) // 如果任务已经被处理，跳过
            {
                RCLCPP_INFO(this->get_logger(), "任务 %zu 已经被处理，跳过。", i);
                continue;
            }

            //task_indices.push_back(i); // 记录未处理任务的索引  改动
            allTasksAssigned = false;  // 只要有未被处理的任务，将allTasksAssigned设为false

            const auto &task_data = global_task_sequence[i].first;
            int task_value = task_data[1]; // 获取任务价值

            // 遍历所有操作员，填充收益矩阵
            for (size_t j = 0; j < operators_.size(); ++j)
            {
                double success_rate = task_data[3 + j] / 100.0; // 获取成功率

                // 计算任务分配的时间间隔
                auto task_arrival_time = global_task_sequence[i].second;           // 任务到达时间
                auto current_time = std::chrono::steady_clock::now();              // 当前时间
                std::chrono::duration<double> time_interval = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - task_arrival_time); // 计算时间间隔

                // 计算收益
                double reward = success_rate * task_value * exp(-time_interval.count() / 1200.0);//改动
                //reward_matrix[j][task_indices.size() - 1] = reward; // 填充收益矩阵
                reward_matrix[j][task_indices.size() - 1] = reward; // 填充收益矩阵
            }
        }
        task_lock.unlock();

        // 如果当前的未处理任务少于3个，KM算法无法应用，跳出循环，等待更多任务
        /*
        if (task_indices.size() < 3)
        {
            if(task_indices.size()==0)
            {
                RCLCPP_INFO(this->get_logger(), "退出程序");
                break;
            }
            RCLCPP_INFO(this->get_logger(), "未处理任务数量不足，等待更多任务到来。");
            //break;改动
            continue;
        }
        */

        // 使用KM算法计算最大收益匹配
        KMAlgorithm km(reward_matrix);
        double max_reward = km.getMaxReward();
        

        auto matching_result = km.getMatchingResult();//重要节点
        RCLCPP_INFO(this->get_logger(), "调试:KM算法计算得到的匹配结果为:");
        for (const auto& element : matching_result) {
            RCLCPP_INFO(this->get_logger(), "%d", element);
        }
        RCLCPP_INFO(this->get_logger(), "KM算法计算的最大总收益为: %.2f", max_reward);
        for(size_t i=0;i< busy_operators.size();i++)//
        {   int unlucky_task_index;
            int who = busy_operators[i]; 
            auto task_it=std::find(matching_result.begin(), matching_result.end(), who);   
            if(task_it!=matching_result.end())
            {
                unlucky_task_index = task_indices[std::distance(matching_result.begin(), task_it)];//改动
            }
            task_lock.lock();
            global_task_sequence[unlucky_task_index].first[3+who]-=5;
            task_lock.unlock();
        }
        // 分配任务，只给空闲的操作员分配任务，并将任务标记为已处理
        for (size_t i = 0; i < idle_operators.size(); ++i)
        {
            size_t selected_operator_index = idle_operators[i];            // 获取空闲的操作员索引
            size_t selected_task_index;
            auto it=std::find(matching_result.begin(), matching_result.end(), int(selected_operator_index));
            if(it!=matching_result.end())
            {
                selected_task_index = task_indices[std::distance(matching_result.begin(), it)];//改动
                RCLCPP_INFO(this->get_logger(), "find here1");
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "problem:bug1");
                std::this_thread::sleep_for(std::chrono::seconds(5));
                continue;
            }
            //size_t selected_task_index = task_indices[matching_result[i]]; // 从匹配结果中获取任务索引


            //std::unique_lock<std::mutex> task_lock(global_task_sequence_mutex); 改动
            task_lock.lock();
            auto best_task_data = global_task_sequence[selected_task_index].first;///bugtest 改动
            task_lock.unlock();
            int best_task_value = best_task_data[1];
            int best_task_time = best_task_data[2];
            double best_success_rate = best_task_data[3 + selected_operator_index] / 100.0;

            // 重新计算时间间隔
            auto task_arrival_time = global_task_sequence[selected_task_index].second;  // 获取任务到达时间
            auto current_time = std::chrono::steady_clock::now();                      // 当前时间
            std::chrono::duration<double> time_interval = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - task_arrival_time);  // 计算时间间隔
            
            // 显示最终选择的任务和相关信息
            //RCLCPP_INFO(this->get_logger(), "最终选择任务 %d 由空闲操作员 %d 执行, 任务时间: %d, 收益: %.2f",
              //          selected_task_index, selected_operator_index, best_task_time, reward_matrix[i][std::distance(matching_result.begin(), it)]);//改动
            //RCLCPP_INFO(this->get_logger(), "最终选择任务%zu",selected_task_index);//改动

            // 分配任务给空闲操作员
            manager.addNewTaskColumn();
            RCLCPP_INFO(this->get_logger(), "here add new task column");
            manager.assignTask(selected_operator_index, selected_task_index, best_task_time, best_success_rate, best_task_value, time_interval.count());
            manager.completeTask(); // 标记新添任务为完成
            task_lock.lock();
            // 使用互斥锁更新全局任务序列，将选定的任务标记为已处理
            
            //std::lock_guard<std::mutex> task_lock(global_task_sequence_mutex);
            global_task_sequence[selected_task_index].second = std::chrono::steady_clock::time_point();  // 将任务标记为已处理
            task_lock.unlock();

            //RCLCPP_INFO(this->get_logger(), "任务 %zu 标记为已处理。", selected_task_index);改动
            std::cout << "任务 " << selected_task_index << " 标记为已处理。" << std::endl;
            // 启动新线程，模拟任务执行
            std::thread([this, selected_operator_index, best_task_time, response] {
                std::this_thread::sleep_for(std::chrono::seconds(best_task_time));
                {
                    //std::lock_guard<std::mutex> lock(cv_mtx);
                    this->manager.setOperatorIdle(selected_operator_index);
                }
                //cv.notify_all();
                //RCLCPP_INFO(this->get_logger(), "操作员 %zu 完成任务，设置为空闲状态。", selected_operator_index);改动
                std::cout << "操作员" << selected_operator_index << " 完成任务，设置成空闲状态" << std::endl;

                //assignTasks(response); // 继续检查是否有空闲的操作员需要分配任务 改动，有可能创建局部变量allTasksAssigned
            }).detach();
        }

        auto task_index_record = manager.getTaskIndexRecord();
        std::stringstream row_str;
        for (const auto &value : task_index_record)
        {
            row_str << value << " ";
        }
        //std::string vec_str = row_str.str();
        //vec_str.pop_back(); // 移除最后一个空格
        RCLCPP_INFO(this->get_logger(), "分配的任务%s", row_str.str().c_str());
        // 显示实时更新的任务分配矩阵
        RCLCPP_INFO(this->get_logger(), "实时更新任务分配矩阵:");
        auto task_assignment_matrix = manager.getTaskAssignment();
        for (size_t i = 0; i < task_assignment_matrix.size(); ++i)
        {
            std::stringstream row_str;
            for (size_t j = 0; j < task_assignment_matrix[i].size(); ++j)
            {
                row_str << task_assignment_matrix[i][j] << " ";
            }
            RCLCPP_INFO(this->get_logger(), "[%s]", row_str.str().c_str());
        }

        // 显示实时更新的任务价值矩阵
        RCLCPP_INFO(this->get_logger(), "实时更新任务价值矩阵:");
        auto task_value_matrix = manager.getTaskValueMatrix();
        for (size_t i = 0; i < task_value_matrix.size(); ++i)
        {
            std::stringstream row_str;
            for (size_t j = 0; j < task_value_matrix[i].size(); ++j)
            {
                row_str << task_value_matrix[i][j] << " ";
            }
            RCLCPP_INFO(this->get_logger(), "[%s]", row_str.str().c_str());
        }
        // 打印更新后的全局任务序列状态
        RCLCPP_INFO(this->get_logger(), "更新后的全局任务序列：");
        task_lock.lock();
        for (const auto &task_pair : global_task_sequence)
        {
            std::stringstream ss;
            for (const auto &value : task_pair.first)
            {
                ss << value << "\t";
            }
            ss << (task_pair.second == std::chrono::steady_clock::time_point() ? "已处理" : "未处理");
            RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
        }
        task_lock.unlock();
        // 如果所有任务都已分配，结束循环
        if (allTasksAssigned)
        {
            RCLCPP_INFO(this->get_logger(), "所有任务都已分配，结束循环。");
            break;
        }
    }

    if(!tt)
    {
        goto loop;
    }

    RCLCPP_INFO(this->get_logger(), "任务执行总时间：%d", manager.getTotalTime());
    RCLCPP_INFO(this->get_logger(), "任务执行总收益：%.2f", manager.getTotalReward());

    std::vector<int32_t> task_result_one_dimensional;
    for (const auto &row : manager.getTaskAssignment())
    {
        std::copy(row.begin(), row.end(), std::back_inserter(task_result_one_dimensional));
    }
    response->task_result = task_result_one_dimensional;

    RCLCPP_INFO(this->get_logger(), "任务分配完成，将结果返回给客户端。");
}

    //从任务序列中移除已分配的任务逻辑，暂时用不上了，因为没有移除任务，只是把任务标记为已处理，后面可以用
    //放在这里也不会报错
    /*void removeCompletedTaskFromGlobalSequence(std::vector<int32_t>::const_iterator start, std::vector<int32_t>::const_iterator end)
    {
        std::vector<int32_t> task_to_remove(start, end);
        std::lock_guard<std::mutex> task_lock(global_task_sequence_mutex); // 加锁保护全局任务序列

        auto it = std::find_if(global_task_sequence.begin(), global_task_sequence.end(),
                               [&task_to_remove](const std::pair<std::vector<int32_t>, std::chrono::steady_clock::time_point> &task_pair) {
                                   return std::equal(task_pair.first.begin(), task_pair.first.end(), task_to_remove.begin());
                               });

        if (it != global_task_sequence.end())
        {
            global_task_sequence.erase(it);
            RCLCPP_INFO(this->get_logger(), "任务已从全局序列中移除。");
        }
        else
        {
            RCLCPP_WARN(this->get_logger(), "未找到要移除的任务，可能已被重复处理。");
        }
    }*/
};

/*主函数*/
int main(int argc, char **argv)
{
    // 20240821新增：获取程序开始时间点
    auto start_time = std::chrono::steady_clock::now();

    rclcpp::init(argc, argv);                                                  // 初始化ROS2 节点
    auto update_node = std::make_shared<TaskUpdateNode>("task_update_node");   // 创建任务更新服务端节点，不传递任何参数，创建任务更新服务端节点
    auto assign_node = std::make_shared<TaskAssignServer>("task_assign_node"); // 创建任务分配服务端节点，不传递任何参数，创建任务分配服务端节点

    // 让每个节点都在自己的线程里面运行，避免线程堵塞
    // update_node
    std::thread update_thread([update_node]()
                              { rclcpp::spin(update_node); });
    // assign_node
    std::thread assign_thread([assign_node]()
                              { rclcpp::spin(assign_node); });

    // 等待线程结束
    update_thread.join();
    assign_thread.join();

    // 20240821新增：计算程序运行时间
    auto end_time = std::chrono::steady_clock::now();
    auto duration = end_time - start_time;
    // 20240821新增：打印程序运行时间
    RCLCPP_INFO(rclcpp::get_logger("main"), "任务分配总计耗时：%ld 秒",
               std::chrono::duration_cast<std::chrono::seconds>(duration).count());
    
    rclcpp::shutdown();
    return 0;
}
/*---Secretary Matching with Free-Disposal for Display ads---*/