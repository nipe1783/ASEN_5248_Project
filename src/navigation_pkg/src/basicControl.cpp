#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;


class basicControl : public rclcpp::Node
{
    public:
        basicControl()
        : Node("basicControl")
        {
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
            timer_ = this->create_wall_timer(
                500ms, std::bind(&basicControl::timer_callback, this));
        }

    private:
        void timer_callback()
        {
            auto message = geometry_msgs::msg::Twist();
            message.linear.x = 2.0; 
            message.angular.z = 1.0;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.linear.x);
            publisher_->publish(message);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<basicControl>());
    rclcpp::shutdown();
    return 0;
}