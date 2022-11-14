#ifndef SINUS_HPP
#define SINUS_HPP

#include <ros/ros.h>
#include <std_msgs/Header.h>

class Sinus{
    std_msgs::Header header;
    float x;
    float y;
};

#endif