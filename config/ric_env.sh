#!/bin/sh
export ROS_MASTER_URI=http://bobin-HP-Pro-2080-Microtower-PC:11311
export ROS_HOSTNAME=tegra-ubuntu
. /opt/ros/indigo/setup.sh
. ~/catkin_ws/devel/setup.sh
exec "$@"
