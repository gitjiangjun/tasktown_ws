// ROS 2 C++头文件
#include "rclcpp/rclcpp.hpp"
#include <cstdlib>   // 标准库头文件
#include <ctime>     // 时间头文件
#include <vector>    // 向量头文件
#include <algorithm> // 算法头文件
#include <chrono>    // 时间头文件
#include <memory>    // 内存管理头文件

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
    TaskRequestNode(const std::string &name) : Node(name), is_first_request(true) {
        // 打印一句开头
        RCLCPP_INFO(this->get_logger(), "准备发送任务");

        // 20240818修改：声明并创建客户端
        task_update_client = this->create_client<village_interfaces::srv::TaskUpdate>("task_update");

        // 20240818修改：初始化随机数种子
        std::srand(std::time(nullptr));

        // 20240818修改：设置定时器，每3秒发送一次任务
        timer = this->create_wall_timer(
            std::chrono::seconds(3),
            std::bind(&TaskRequestNode::send_tasks_request, this)
        );
    }

    void send_tasks_request() {
        // 5.1等待服务端上线
        if (!task_update_client->wait_for_service(std::chrono::seconds(2))) {
            RCLCPP_WARN(this->get_logger(), "等待任务更新和分配服务上线");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "准备发送任务分配请求");

        // 20240818修改：生成任务列向量
        vector<int> task_row(6); // 1行6列的任务列向量

        // 20240818修改：定义随机序列参数
        if (is_first_request) {
            task_row[0] = 0; // 第一次发送任务类型为"0"
            task_row[1] = 2; // "0"类型任务的价值固定为2
            task_row[2] = 19; // "0"类型任务的执行时间固定为900秒  改动
            is_first_request = false;
        } else {
            task_row[0] = rand() % 3 + 1; // 任务类型为"1", "2", "3"中的一个
            switch (task_row[0]) {
                case 1:
                    task_row[1] = rand() % 5 + 4; // 任务价值在4-8之间
                    task_row[2] = rand() % 11 + 10; // 执行时间10-20秒
                    break;
                case 2:
                    task_row[1] = rand() % 10 + 9; // 任务价值在9-18之间
                    task_row[2] = rand() % 6 + 10; // 执行时间10-15秒
                    break;
                case 3:
                    task_row[1] = rand() % 15 + 10; // 任务价值在10-24之间
                    task_row[2] = rand() % 11 + 10; // 执行时间10-20秒
                    break;
            }
        }

        // 20240818修改：生成操作员成功率
        for (int i = 3; i < 6; ++i) {
            task_row[i] = rand() % 31 + 60; // 成功率在60%-90%之间
        }

        // 20240818修改：将当前生成的任务序列横向扩展到累积任务序列右侧
        accumulated_tasks.push_back(task_row);

        // 20240818修改：按列对齐打印累积的任务序列
        RCLCPP_INFO(this->get_logger(), "生成的任务为：");
        for (size_t i = 0; i < accumulated_tasks[0].size(); ++i) {
            std::stringstream ss;
            for (size_t j = 0; j < accumulated_tasks.size(); ++j) {
                ss << accumulated_tasks[j][i] << "\t"; // 每个任务值之间用TAB分隔
            }
            RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
        }

        // 20240818修改：构造异步请求数据，只发送当前生成的任务
        auto request = std::make_shared<village_interfaces::srv::TaskUpdate_Request>();
        request->tasks = task_row; // 只发送当前生成的任务

        // 5.3发送异步请求
        task_update_client->async_send_request(
            request,
            std::bind(&TaskRequestNode::tasks_callback, this, _1)
        );
    }

private:
    // 创建任务更新客户端
    rclcpp::Client<village_interfaces::srv::TaskUpdate>::SharedPtr task_update_client;
    // 创建定时器
    rclcpp::TimerBase::SharedPtr timer; // 定时器
    // 检查是否第一次发送任务请求
    bool is_first_request; // 标志是否是第一次发送任务请求
    std::vector<std::vector<int>> accumulated_tasks; // 20240818修改：累积任务序列

    // 2.创建请求结果接收回调函数
    void tasks_callback(rclcpp::Client<village_interfaces::srv::TaskUpdate>::SharedFuture response) {
        
        // 4.填写结果接收逻辑，接收服务端结果
        auto result = response.get();

        // 20240818修改：打印已经发送的任务总数
        RCLCPP_INFO(this->get_logger(), "发送了 %zu 个任务，任务已成功发送并更新", accumulated_tasks.size());     

    }
};

/*主函数*/
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TaskRequestNode>("task_request_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}