#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "node_Sinus");

    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<tp_msgs::Sinus>("sinus", 1000);
    ros::Rate loop_rate(10);
}