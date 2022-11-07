#include <ros/ros.h>
#include "tp2.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TP2");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    TP2 tp2(node, private_nh);
    ros::spin();
}
