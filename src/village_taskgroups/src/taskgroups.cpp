// ROS2 C++头文件
#include "rclcpp/rclcpp.hpp"
#include <cstdlib>   // 标准库头文件
#include <ctime>     // 时间头文件
#include <vector>    // 向量头文件
#include <algorithm> // 算法头文件
#include <chrono>    // 时间头文件
#include <memory>    // 内存管理头文件

// 1.导入服务接口类型
#include"village_interfaces/srv/task_assign.hpp"

// 提前声明的占位符，留着创建客户端的时候用
using std::placeholders::_1;

// 使用标准命名空间
using namespace std;


class TaskRequestNode : public rclcpp::Node {
public:
    /* 构造函数 */
    TaskRequestNode(const std::string &name) : Node(name) {
        RCLCPP_INFO(this->get_logger(), "准备生成随机任务序列....");

        // 声明并创建客户端
        task_client = this->create_client<village_interfaces::srv::TaskAssign>("assign_task");

        // 设置定时器，定时检查服务端是否上线
        timer = this->create_wall_timer(
            std::chrono::seconds(5), // 每5秒检查一次
            std::bind(&TaskRequestNode::check_and_send_tasks_request, this)
        );
    }

    void check_and_send_tasks_request() {
        // 等待服务端上线
        if (task_client->wait_for_service(std::chrono::seconds(2))) {
            RCLCPP_INFO(this->get_logger(), "服务端已上线，正在生成随机任务序列...");

            // 初始化随机数种子
            std::srand(std::time(nullptr));

            // 生成随机任务序列
            generateRandomTaskgroups();

            // 发送任务请求
            send_tasks_request();

            // 发送任务后，取消定时器
            timer->cancel();
        } else {
            // 服务端不在线，打印服务端不在线信息，
            RCLCPP_WARN(this->get_logger(), "服务端不在线，等待服务端上线...");
        }
    }

    void generateRandomTaskgroups() {
        // 定义可能出现的随机任务组
        vector<vector<int>> Possible_taskgroups = { {1}, {1, 2}, {1, 3}, {1, 2, 3} };

        // 随机选择一个可能出现的任务组
        size_t sequenceIndex = rand() % Possible_taskgroups.size();
        randomTaskArray = Possible_taskgroups[sequenceIndex];

        // 打印随机生成的任务组
        RCLCPP_INFO(this->get_logger(), "生成的随机任务序列：");
        for (int32_t task : randomTaskArray) {
            RCLCPP_INFO(this->get_logger(), "%d ", task);
        }
    }

    void send_tasks_request() {
        // 构造异步请求数据
        auto request = std::make_shared<village_interfaces::srv::TaskAssign::Request>();
        request->tasks = randomTaskArray;

        // 发送异步请求
        task_client->async_send_request(
            request,
            std::bind(&TaskRequestNode::tasks_callback, this, _1)
        );
    }

private:
    vector<int32_t> randomTaskArray; // 随机任务序列
    rclcpp::Client<village_interfaces::srv::TaskAssign>::SharedPtr task_client; // 声明并创建客户端
    rclcpp::TimerBase::SharedPtr timer; // 定时器

    // 创建请求结果接收回调函数
    void tasks_callback(rclcpp::Client<village_interfaces::srv::TaskAssign>::SharedFuture response) {
        auto result = response.get();
        RCLCPP_INFO(this->get_logger(), "收到%ld 个任务分配结果", result->task_result.size());
        RCLCPP_INFO(this->get_logger(), "客户端已经接收到任务分配结果了,并且输出了任务分配数组");
        RCLCPP_INFO(this->get_logger(), "Mission Success");
    }
};

/* 主函数 */
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TaskRequestNode>("taskgroups");
    rclcpp::spin(node); // 使用spin让程序保持运行，直到任务发送完毕后自动停止
    rclcpp::shutdown();
    return 0;
}


