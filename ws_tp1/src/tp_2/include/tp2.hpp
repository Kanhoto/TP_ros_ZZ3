#ifndef TP2_HPP
#define TP2_HPP

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string_view>
#include <cmath>
#include <chrono>
#include <map>

// ROS INCLUDE
#include <ros/ros.h>
#include <gps_nmea/GpsPlanar.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <sensor_msgs/MagneticField.h>

class TP2
{
    public:
        TP2(ros::NodeHandle node, ros::NodeHandle private_nh);
        ~TP2();
        void processOdometry(const nav_msgs::Odometry::ConstPtr& msg);
        void processGpsRTK(const gps_nmea::GpsPlanar::ConstPtr& msg);
        void processGpsNatural(const gps_nmea::GpsPlanar::ConstPtr& msg);
        void processMag(const sensor_msgs::MagneticField::ConstPtr& msg);

    private:
        // Suscriber
        ros::Subscriber odometry_sub_;
        ros::Subscriber imu_sub_;
        ros::Subscriber gps_rtk_sub_;
        ros::Subscriber gps_nat_sub_;
        ros::Subscriber mag_sub_;
        
        // Publisher
        ros::Publisher pose_pub_;
        ros::Publisher path_pub_;
        ros::Publisher path_odom_pub_;
        ros::Publisher path_gps_pub_;
        ros::Publisher path_gps_natural_pub_;

        ros::Timer timer;
        
        float start_gps_x;
        float start_gps_y;
        float start_gps_z;
        float start_gps_natural_z;
        float odom_x, odom_y;
        float theta_odom_to_gps;

        bool init_gps;
        bool init_gps_natural;
        bool init_theta;
        bool init_odom;

        nav_msgs::Path path_odom;
        nav_msgs::Path path_gps;
        nav_msgs::Path path_gps_natural;

        float offset_east;
        float offset_north;
};


#endif