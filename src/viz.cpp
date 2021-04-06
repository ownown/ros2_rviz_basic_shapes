#include <chrono>

#include "rclcpp/rclcpp.hpp"

#include "visualization_msgs/msg/marker.hpp"

using namespace std::chrono_literals;
using Marker = visualization_msgs::msg::Marker;

class VizPub : public rclcpp::Node
{
private:
    rclcpp::Publisher<Marker>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Clock clock;
    void timerCallback();
    Marker marker;
    Marker createCylinder();
public:
    VizPub();
};

VizPub::VizPub() : Node("visualization_publisher"), clock(RCL_ROS_TIME)
{
    this->marker = this->createCylinder();
    this->publisher = this->create_publisher<Marker>("my_marker", 10);
    this->timer = this->create_wall_timer(500ms, 
        [this](){ this->timerCallback(); }
        // std::bind(&VizPub::timerCallback, this)
    );
}

void VizPub::timerCallback()
{
    this->publisher->publish(this->marker);
}

Marker VizPub::createCylinder()
{
    const uint32_t shape = Marker::CYLINDER;
    Marker marker;
    marker.header.frame_id = "/my_frame";
    marker.header.stamp = this->clock.now();
    marker.ns = "test_shape";
    marker.id = 0;

    marker.type = shape;
    marker.action = Marker::ADD;

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;

    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    marker.color.a = 1.0;

    marker.lifetime = rclcpp::Duration(1s);

    return marker;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VizPub>());
    rclcpp::shutdown();

    return 0;
}
