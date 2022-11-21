#include "ros/ros.h"
#include "tp_msgs/Sinus.h"
#include "nav_msgs/Odometry.h"

nav_msgs::Odometry odom_msg;
ros::Publisher pub_odom;

void sinus_callback(const tp_msgs::Sinus & str){
  ROS_INFO("hello world");
  odom_msg.pose.pose.position.x = str.x;
  odom_msg.pose.pose.position.y = str.y;
  odom_msg.header = str.header;
  
  pub_odom.publish(odom_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  
  ros::Subscriber sinus_sub = n.subscribe("sinus", 1000, sinus_callback);
  pub_odom = n.advertise<nav_msgs::Odometry>("odom", 1000);

  ros::spin();

  return 0;
}