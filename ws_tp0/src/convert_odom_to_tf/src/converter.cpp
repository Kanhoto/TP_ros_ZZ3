#include "converter.hpp"

Converter::Converter(ros::NodeHandle node, ros::NodeHandle private_nh)
{
    odom_sub_ = node.subscribe("/effibote4/odometry", 1, &Converter::processOdom, this);
}


Converter::~Converter()
{

}

void Converter::processOdom(const nav_msgs::Odometry::ConstPtr& msg_odom)
{
    static tf2_ros::StaticTransformBroadcaster static_broadcaster;

    geometry_msgs::TransformStamped static_transformStamped;
    static_transformStamped.header = msg_odom->header;
    static_transformStamped.header.frame_id = "odom";
    static_transformStamped.child_frame_id = "base_footprint";
    static_transformStamped.transform.translation.x = msg_odom->pose.pose.position.x;
    static_transformStamped.transform.translation.y = msg_odom->pose.pose.position.y;
    static_transformStamped.transform.translation.z = msg_odom->pose.pose.position.z;
    static_transformStamped.transform.rotation = msg_odom->pose.pose.orientation;
    static_broadcaster.sendTransform(static_transformStamped);
}