#pragma once
#include "ros/ros.h"
#include "visca/libvisca.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#define EVI_D30
#include "visca/gs_zv.h"

class viscaControl
{
public:
	viscaControl();
	void on_Cmd_run();
	bool zoom_service_calbak( visca::gs_zv::Request &req, 
				   visca::gs_zv::Response &res);
	void setZoomValue(int val);

	void on_ZoomIn();
	void on_ZoomOut();
	void on_Exp_Auto();
	void on_Exp_Maunal();
	void on_EXP_Shutter_Inc();
	void on_EXP_Shutter_Dec();
	void on_EXP_Iris_Dec();
	void on_EXP_Iris_Inc();
	void print_usage();
	void InitDev();
	void openDev(int argc, char **argv);
	enum zoomLmt
	{	
		minZoom = 0,
		maxZoom = 0x4000
	};
private:

	VISCAInterface_t iface;
	VISCACamera_t camera;

	int zoom_step;
	int camera_num;
	uint8_t value;
	uint16_t zoom_value;
	int pan_pos, tilt_pos;

	uint16_t focus_value; 
	uint16_t set_focus_value;
	uint8_t focus_auto;	
};