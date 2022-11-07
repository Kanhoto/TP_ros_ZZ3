#include <iostream>
#include <vector>
#include <string>

// ROS INCLUDE
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/static_transform_broadcaster.h>

#include <tf/tf.h>
#include <nav_msgs/Odometry.h>

using namespace std;

class Converter
{
    public:
        Converter(ros::NodeHandle node, ros::NodeHandle private_nh);
        ~Converter();

        void processOdom(const nav_msgs::Odometry::ConstPtr& msg_odom);

    private:
        // ROS Subscriber
        ros::Subscriber odom_sub_;
};
