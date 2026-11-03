/**
 * @file cpp_minimal_publisher.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-11-01
 * @copyright Copyright (c) 2026
 * 
 */

#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals; // handles time literals like 1s, 500ms, etc.

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher() : Node("minimal_cpp_publisher"), counter_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("/cpp_example_topic", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Publishing at 2Hz");
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(counter_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  size_t counter_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}