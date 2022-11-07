#include <ros/ros.h>
#include "converter.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "converter");
    ros::NodeHandle node;
    ros::NodeHandle private_nh("~");

    Converter converter(node, private_nh);
    ros::spin();
}
