#include "tp2.hpp"

TP2::TP2(ros::NodeHandle node, ros::NodeHandle private_nh)
{
    // Create the subscriber for the odometry and GPS topic
    odometry_sub_ = node.subscribe("/odometry_in", 1000, &TP2::processOdometry, this);
    gps_rtk_sub_ = node.subscribe("/gps_rtk_in", 1000, &TP2::processGpsRTK, this);
    gps_nat_sub_ = node.subscribe("/gps_nat_in", 1000, &TP2::processGpsNatural, this);
    mag_sub_ = node.subscribe("/ahrs_landmark/imu/mag", 1000, &TP2::processMag, this);

    // Create the publisher for both odom and gps path
    path_odom_pub_ = node.advertise<nav_msgs::Path>("/path_odom_robot",1);
    path_gps_pub_ = node.advertise<nav_msgs::Path>("/path_gps",1);
    path_gps_natural_pub_ = node.advertise<nav_msgs::Path>("/path_gps_natural",1);

    // Will use to get the inital values of the gps
    init_gps = false;
    init_theta = false;
    init_gps_natural = false;
    init_odom = false;

    // Offset of the projection
    offset_east = -67.55538937 - 0.3;
    offset_north = -81.88550075 - 0.4;
}

TP2::~TP2()
{
    
}

/*
*   Init the rotation of the robot in the world reference frame
*/
void TP2::processMag(const sensor_msgs::MagneticField::ConstPtr& msg)
{
    if(!init_theta)
    {
        theta_odom_to_gps = M_PI/2.0f + std::atan2(msg->magnetic_field.y,msg->magnetic_field.x);
        init_theta = true;
    }
    
}

/*
*   Callback function for the gps. We use here a custom msg
*/
void TP2::processGpsRTK(const gps_nmea::GpsPlanar::ConstPtr& msg)
{
    //GPS mode (ENU): East, North, Up
    if(!init_gps)
    {
        // Get the inital value of the z value
        start_gps_x = msg->east;
        start_gps_y = msg->north;
        start_gps_z = msg->up;
        init_gps = true;
    }

    // Publish the trajectory of the vehicle from the gps
    geometry_msgs::PoseStamped pose_gps;

    pose_gps.header.stamp = msg->header.stamp;
    pose_gps.header.frame_id = "map";

    // Get gps data into odometry frame
    float x_gps = msg->east - offset_east;
    float y_gps = msg->north - offset_north;

    pose_gps.pose.position.x = x_gps;
    pose_gps.pose.position.y = y_gps;
    pose_gps.pose.position.z = msg->up - start_gps_z;

    path_gps.header.stamp = ros::Time::now();
    path_gps.header.frame_id = "map";
    path_gps.poses.push_back(pose_gps);

    path_gps_pub_.publish(path_gps);
}

void TP2::processGpsNatural(const gps_nmea::GpsPlanar::ConstPtr& msg)
{
    //GPS mode (ENU): East, North, Up
    if(!init_gps_natural)
    {
        // Get the inital value of the z value
        start_gps_natural_z = msg->up;
        init_gps_natural = true;
    }

    // Publish the trajectory of the vehicle from the gps
    geometry_msgs::PoseStamped pose_gps;

    pose_gps.header.stamp = msg->header.stamp;
    pose_gps.header.frame_id = "map";

    // Get gps data into odometry frame
    float x_gps = msg->east - offset_east;
    float y_gps = msg->north - offset_north;

    pose_gps.pose.position.x = x_gps;
    pose_gps.pose.position.y = y_gps;
    pose_gps.pose.position.z = msg->up - start_gps_natural_z;

    path_gps_natural.header.stamp = ros::Time::now();
    path_gps_natural.header.frame_id = "map";
    path_gps_natural.poses.push_back(pose_gps);

    path_gps_natural_pub_.publish(path_gps_natural);
}

/*
*   Callback function for the wheel odometry
*/
void TP2::processOdometry(const nav_msgs::Odometry::ConstPtr& msg)
{
    if(init_gps)
    {
        if(!init_odom)
        {
            odom_x = msg->pose.pose.position.x;
            odom_y = msg->pose.pose.position.y;
            init_odom = true;
        }
        // Publish the trajectory of the vehicle from the odom
        geometry_msgs::PoseStamped pose_odom;

        pose_odom.header.stamp = ros::Time::now();
        pose_odom.header.frame_id = "map";

        float x = msg->pose.pose.position.x - odom_x;
        float y = msg->pose.pose.position.y - odom_y;

        pose_odom.pose.position.x = (x * cos(theta_odom_to_gps) - y * sin(theta_odom_to_gps)) + start_gps_x - offset_east;
        pose_odom.pose.position.y = (x * sin(theta_odom_to_gps) + y * cos(theta_odom_to_gps)) + start_gps_y - offset_north;
        pose_odom.pose.position.z = 0;

        pose_odom.pose.orientation.x = msg->pose.pose.orientation.x;
        pose_odom.pose.orientation.y = msg->pose.pose.orientation.y;
        pose_odom.pose.orientation.z = msg->pose.pose.orientation.z;
        pose_odom.pose.orientation.w = msg->pose.pose.orientation.w;

        path_odom.header.stamp = ros::Time::now();
        path_odom.header.frame_id = "map";
        path_odom.poses.push_back(pose_odom);

        path_odom_pub_.publish(path_odom);
    }

}
