#include "ros/ros.h"
#include "tp_msgs/Sinus.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher sinus_pub = n.advertise<tp_msgs::Sinus>("sinus", 1000);

  float current_x = 0;
  float speed = 1.0; // m.s^-1
  float frequence = 10; // Hz

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    tp_msgs::Sinus msg;

    msg.header.frame_id = "mon_capteur";
    msg.header.stamp = ros::Time::now();
    
    current_x += speed/frequence;
    msg.x = current_x;
    msg.y = sin(msg.x);

    sinus_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}