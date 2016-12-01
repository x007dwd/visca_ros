#!/bin/bash
export ROS_MASTER_URI="http://bobin-HP-Pro-2080-Microtower-PC:11311"
export ROS_HOSTNAME=bobin-HP-Pro-2080-Microtower-PC
export ROSLAUNCH_SSH_UNKNOWN=1
#export ROS_IP="192.168.1.30"
. ~/catkin_ws/devel/setup.sh
#rostopic list &&
#rosrun image_view image_view image:=/camera/markedImage

#rostopic echo /dji_sdk/attitude_quadternion >> $(rospack find uav_pose)/output/dji_sdk_quadternion.txt
#rostopic echo /dji_sdk/global_position >> $(rospack find uav_pose)/output/dji_sdk_gpos.txt
#rostopic echo /dji_sdk/local_position >> $(rospack find uav_pose)/output/dji_sdk_lpos.txt
#roscore
