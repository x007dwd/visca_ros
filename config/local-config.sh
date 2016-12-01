#!/bin/bash
remote_time="$(ssh bobin@192.168.1.31 date)" && sudo date --set="$remote_time"
export ROS_MASTER_URI="http://192.168.1.30:11311"
export ROS_HOSTNAME="192.168.1.30"
. ~/Documents/ROS_WS/catkin_ws/devel/setup.sh
#roslaunch uav_pose pose_image.launch
