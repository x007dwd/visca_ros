#!/bin/sh
export ROS_HOSTNAME="192.168.1.30"
export ROS_IP="192.168.1.30"
. ~/Documents/ROS_WS/catkin_ws/devel/setup.sh
exec "$@"
