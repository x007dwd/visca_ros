#include "ros/ros.h"
#include "visca/gs_zv.h"
int main(int argc, char **argv)
{
	ros::init(argc, argv, "testViscaControl");
	ros::NodeHandle nh;
	ros::ServiceClient visca_client = nh.serviceClient<visca::gs_zv>("zoom_service_calbak");
	visca::gs_zv gs_zv_srv;
	int zoom = 0;
	ros::Rate r(10);
	while(ros::ok())
	{
		gs_zv_srv.request.set_zv = zoom;
		zoom += 100;
		if (zoom > 0x4000)
		{
			zoom = 0;
		}
		ros::spinOnce();
		r.sleep();
		if (visca_client.call( gs_zv_srv))
		{
			ROS_INFO("zoom value is set%d", gs_zv_srv.response.get_zv);
		}
	}
}