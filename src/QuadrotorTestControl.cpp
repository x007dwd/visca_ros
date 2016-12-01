#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "mavros_msgs/AttitudeTarget.h"
#include "mavros_msgs/GlobalPositionTarget.h"
#include "mavros_msgs/PositionTarget.h"
int main(int argc, char **argv)
{
   ros::init(argc, argv, "comun");
   ros::NodeHandle n;

   ros::Publisher chatter_pub = n.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/target_local",100);
   ros::Rate loop_rate(10);

   //geometry_msgs::TwistStamped msg;
   mavros_msgs::PositionTarget msg;

   while(ros::ok()){
       msg.header.stamp = ros::Time::now();
       msg.header.seq=1;
       msg.velocity.x = 1;
       msg.velocity.y = 1;

       chatter_pub.publish(msg);
       ros::spinOnce();
       loop_rate.sleep();
   }    
   return 0;
}