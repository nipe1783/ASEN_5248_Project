#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class RobotController : public rclcpp::Node {
public:
    RobotController() : Node("robot_controller") {
        // Position control publisher
        position_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/forward_position_controller/commands", 10);

        // Velocity control publisher
        velocity_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/forward_velocity_controller/commands", 10);

        // Example: set up a timer to periodically send commands
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&RobotController::send_commands, this));
    }

private:
    void send_commands() {
        std_msgs::msg::Float64MultiArray position_msg;
        std_msgs::msg::Float64MultiArray velocity_msg;
        position_msg.data = {1.0, 1.0, 1.0, 1.0};
        velocity_msg.data = {1.0, 1.0, 1.0, 1.0};
        position_publisher_->publish(position_msg);
        velocity_publisher_->publish(velocity_msg);
    }

    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr position_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr velocity_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}