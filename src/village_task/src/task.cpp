// ROS 2 C++头文件
#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/int32.hpp>
#include <cstdlib>   // 标准库头文件
#include <ctime>     // 时间头文件
#include <vector>    // 向量头文件
#include <algorithm> // 算法头文件
#include <chrono>    // 时间头文件
#include <memory>    // 内存管理头文件
#include<signal.h>
#include <unistd.h>  // 包含 sleep 函数
#include <iomanip>
// 1.导入服务接口类型
// 任务更新的服务接口 [创建完srv文件要记得编译才会出现"update_task.hpp"!!!]
#include "village_interfaces/srv/task_update.hpp"

// 提前声明的占位符，留着创建客户端的时候用
using std::placeholders::_1;

// 使用标准命名空间
using namespace std;

/*
    创建一个类节点，名字叫做TaskRequestNode,继承自Node.
*/
class TaskRequestNode : public rclcpp::Node {
public:
    /* 构造函数 */
    TaskRequestNode(const std::string &name,int time_window_probability) : Node(name), is_first_request(true), time_window_probability_(time_window_probability){
        // 打印一句开头
        RCLCPP_INFO(this->get_logger(), "准备发送任务");

        // 20240818修改：声明并创建客户端
        task_update_client = this->create_client<village_interfaces::srv::TaskUpdate>("task_update");

        // 20240818修改：初始化随机数种子
        std::srand(std::time(nullptr));


        // 初始创建定时器
        reset_timer();
        

        signal(SIGINT,signal_handler);
            // 创建消息订阅者
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "task_status", 10, std::bind(&TaskRequestNode::message_callback, this, std::placeholders::_1));
        
    }

    void send_over()
    {
        vector<int>task_row(7,0);
        //task_row[1] = 0;
        // 20240818修改：构造异步请求数据，只发送当前生成的任务
        auto request = std::make_shared<village_interfaces::srv::TaskUpdate_Request>();
        request->tasks = task_row; // 只发送当前生成的任务

        // 5.3发送异步请求
        task_update_client->async_send_request(request);
    }
    void send_tasks_request() {
        // 5.1等待服务端上线
        if (!task_update_client->wait_for_service(std::chrono::seconds(2))) {
            RCLCPP_WARN(this->get_logger(), "等待任务更新和分配服务上线");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "准备发送任务分配请求");

        // 20240818修改：生成任务列向量
        vector<int> task_row(7); // 1行7列的任务列向量
 
        // 20240818修改：定义随机序列参数
        if (is_first_request) {
            task_row[0] = 0; // 第一次发送任务类型为"0"
            task_row[1] = 2; // "0"类型任务的价值固定为2
            task_row[2] = 100; // "0"类型任务的执行时间固定为900秒
            task_row[3] = 100;//操作员成功率
            task_row[4] = 100;
            task_row[5] = 100;
            task_row[6] = 0;//无时间约束
            // 打印任务0的信息（列向量）
            RCLCPP_INFO(this->get_logger(), "经指挥人员判断，生成的0任务[飞行任务任]信息、各操作员适配度以及时间窗口信息如下：");
            print_task_vector(task_row);
            is_first_request = false;
        } else {
            int time_window_length = generate_time_window();  /*---1022修改---（使用总的时间窗口概率）---*/
            task_row[0] = rand() % 3 + 1; // 任务类型为"1", "2", "3"中的一个
            switch (task_row[0]) {
                case 1:
                    task_row[1] = rand() % 5 + 4; // 任务价值在4-8之间
                    task_row[2] = rand() % 11 + 10; // 执行时间10-20秒
                    task_row[6] = time_window_length;//无时间约束
                    break;
                case 2:
                    task_row[1] = rand() % 10 + 9; // 任务价值在9-18之间
                    task_row[2] = rand() % 6 + 10; // 执行时间10-15秒
                    task_row[6] = time_window_length;//无时间约束
                    break;
                case 3:
                    task_row[1] = rand() % 15 + 10 ; // 任务价值在10-24之间
                    task_row[2] = rand() % 11 + 10; // 执行时间10-20秒
                    task_row[6] = time_window_length;//有时间约束，10秒内需要处理
                    break;
            }
            // 20240818修改：生成操作员成功率
            for (int i = 3; i < 7; ++i) {
                task_row[i] = rand() % 31 + 60; // 成功率在60%-90%之间
            }
        }


        // 20240818修改：将当前生成的任务序列横向扩展到累积任务序列右侧
        accumulated_tasks.push_back(task_row);

        // 20240818修改：按列对齐打印累积的任务序列
        RCLCPP_INFO(this->get_logger(), "生成的任务为：");
        print_task_vector(task_row);

                // 打印累积任务矩阵
        RCLCPP_INFO(this->get_logger(), "当前累积的任务矩阵：");
        print_accumulated_tasks_matrix();


        // 20240818修改：构造异步请求数据，只发送当前生成的任务
        auto request = std::make_shared<village_interfaces::srv::TaskUpdate_Request>();
        request->tasks = task_row; // 只发送当前生成的任务

        // 5.3发送异步请求
        task_update_client->async_send_request(
            request,
            std::bind(&TaskRequestNode::tasks_callback, this, _1)
        );
        reset_timer();
    }

private:
    std::mutex client_mutex; // 定义互斥锁
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    // 创建任务更新客户端
    rclcpp::Client<village_interfaces::srv::TaskUpdate>::SharedPtr task_update_client;
    // 创建定时器
    rclcpp::TimerBase::SharedPtr timer; // 定时器
    // 检查是否第一次发送任务请求
    bool is_first_request; // 标志是否是第一次发送任务请求
    std::vector<std::vector<int>> accumulated_tasks; // 20240818修改：累积任务序列
    /*---1022修改---（定义总的时间窗口出现概率）---*/
    int time_window_probability_;                      // 总的时间窗口出现概率
    // 2.创建请求结果接收回调函数
    void tasks_callback(rclcpp::Client<village_interfaces::srv::TaskUpdate>::SharedFuture response) {
        
        // 4.填写结果接收逻辑，接收服务端结果
        auto result = response.get();

        // 20240818修改：打印已经发送的任务总数
        RCLCPP_INFO(this->get_logger(), "发送了 %zu 个任务，任务已成功发送并更新", accumulated_tasks.size());     

    }
    /*void signal_callback(rclcpp::Client<village_interfaces::srv::TaskUpdate>::SharedFuture response) {
        auto result = response.get();
            // 打印结果
        std::cout << "Result: " << result << std::endl;
        std::cout << "**********任务已结束" << std::endl;
    }*/
    void message_callback(const std_msgs::msg::Int32::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "接收到一个完成任务，类型%d", msg->data);
        if(msg->data == 2){
            RCLCPP_INFO(this->get_logger(), "随机发送一个子任务，然后关闭");
            {
                std::lock_guard<std::mutex> lock(client_mutex);
                send_tasks_request();
                timer->cancel();
                timer.reset();
                //RCLCPP_INFO(this->get_logger(), "发送了 %zu 个任务，任务已成功发送并更新", accumulated_tasks.size());     
            }
            sleep(2);
            {
                std::lock_guard<std::mutex> lock(client_mutex);
                if(timer){
                    timer->cancel();
                    timer.reset();
                }
                send_over();
                subscription_.reset();
            }
            //sleep(2);
            //exit(0);
        }
    }
    void reset_timer() {
        // 20241014修改：任务发送时间间隔为随机数3-6秒
        int random_seconds = std::rand() % 4 + 3; // 随机生成3-6秒的间隔 1022修改

        if(timer)
        {
            timer->cancel();
            timer.reset();
        }

        // 20240818修改：设置定时器，每3秒发送一次任务
        timer = this->create_wall_timer(
            std::chrono::seconds(random_seconds),
            std::bind(&TaskRequestNode::send_tasks_request, this)
        );

        RCLCPP_INFO(this->get_logger(), "新任务 %d 秒后到达", random_seconds);
    }
        /*---1022修改---（生成时间窗口的函数，使用统一的概率）---*/
    int generate_time_window() {
        // 以给定总的概率生成任务时间窗口
        if (is_event_triggered(time_window_probability_)) {

        /*---1022修改---（设置时间窗口阈值）---*/    
            return (rand() % 9 + 10);          // 暂定返回10-18之间的随机秒数
        }
        return 0;                            // 没有时间窗口限制时为0
    }
    /*---1022修改---[判断事件是否触发（根据概率）]---*/
    bool is_event_triggered(int probability) {
        return ((rand() % 100) < probability);
    }
        // 打印任务向量的函数（以列向量形式）
    void print_task_vector(const std::vector<int>& task) {
        
        RCLCPP_INFO(this->get_logger(), "[任务类型]: %d", task[0]);
        RCLCPP_INFO(this->get_logger(), "[任务价值]: %d", task[1]);
        RCLCPP_INFO(this->get_logger(), "[任务时间]: %d", task[2]);
        RCLCPP_INFO(this->get_logger(), "[适配度_1]: %d", task[3]);
        RCLCPP_INFO(this->get_logger(), "[适配度_2]: %d", task[4]);
        RCLCPP_INFO(this->get_logger(), "[适配度_3]: %d", task[5]);
        RCLCPP_INFO(this->get_logger(), "[时间窗口]: %d", task[6]);  // 打印时间窗口约束
    }
    void print_accumulated_tasks_matrix(){
        // 打印标题行
        RCLCPP_INFO(this->get_logger(), "        [任务类型] [任务价值] [任务时间] [适配度_1] [适配度_2] [适配度_3] [时间窗口]");
        for (size_t i = 0; i < accumulated_tasks.size(); ++i) {
            const auto& task = accumulated_tasks[i];
            std::stringstream ss;
            ss << "[任务" << (i+1) << "]   ";
            for (size_t j = 0; j < task.size(); ++j) {
                int width;
                switch (j)
                {
                    case 0:width=3;break;
                    case 1:width=4;break;
                    case 2:width=8;break;
                    case 3:width=2;break;
                    case 4:width=5;break;
                    case 5:width=8;break;
                    case 6:width=5;break;
                }
                ss << std::setw(width) << accumulated_tasks[i][j] << "\t"; // 每个任务值之间用TAB分隔
            }
            RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
        }
    }
    static void signal_handler(int sig) {
        if (sig == SIGINT) {
            TaskRequestNode *instance = new TaskRequestNode("signal",0);
            instance->timer->cancel();
            instance->send_over();
            std::cout<<"接收到 Ctrl+C，发送结束信号"<<std::endl;
            sleep(2);
            delete instance;
            exit(0);
        }
    }

};



/*主函数*/
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    // 使用多线程执行器
    rclcpp::executors::MultiThreadedExecutor executor;
    auto node = std::make_shared<TaskRequestNode>("task_request_node",20);
    
    executor.add_node(node);
    executor.spin();
    //rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}