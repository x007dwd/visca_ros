#include "visca/viscaControl.h"
#include "iostream"
using namespace std;

viscaControl::viscaControl()
	:zoom_value(0)
	,zoom_step(0x800)
{

}

void viscaControl::openDev(int argc, char **argv)
{
	  if (argc<2)
	{
		fprintf(stderr,"%s usage: %s <serial port device>\n",argv[0],argv[0]);
		exit(1);
	}

	if (VISCA_open_serial(&iface, argv[1])!=VISCA_SUCCESS)
	{
		fprintf(stderr,"%s: unable to open serial device %s\n",argv[0],argv[1]);
		exit(1);
	}

}
void viscaControl::InitDev()
{
	iface.broadcast=0;
	VISCA_set_address(&iface, &camera_num);
	camera.address=1;
	VISCA_clear(&iface, &camera);

	VISCA_get_camera_info(&iface, &camera);
	fprintf(stderr,"Some camera info:\n------------------\n");
	fprintf(stderr,"vendor: 0x%04x\n model: 0x%04x\n ROM version: 0x%04x\n socket number: 0x%02x\n", camera.vendor, camera.model, camera.rom_version, camera.socket_num);
}

void viscaControl::print_usage()
{
	cerr << "Usage: test_serial {-e|<serial port address>} ";
	cerr << "<baudrate> [test string]" << endl;
	cerr << endl;
	cerr << "==============================================================================="  << endl;
	cerr << "	W 		" << endl;
	cerr <<"A 	S 	D 	" <<endl;
	cerr <<"	Z 		" << endl;
	cerr << "Here  these keys are used for :" <<endl;
	cerr << "	W 	exp Inc" << endl;
	cerr << "	Z 	exp Dec" <<endl;
	cerr << "	j 	iris Inc" <<endl;
	cerr << "	k 	iris Dec" <<endl;
	cerr << endl;
	cerr << "	x  [step] 	set the value for zoom" <<endl;
	cerr << "==============================================================================="  << endl;
	cerr << "	d	zoom in" <<endl;
	cerr << " 	a 	zoom out " << endl;
	cerr << " 	3 	exp auto mode " << endl;
	cerr << " 	4	exp manual mode " << endl;
}

void viscaControl::setZoomValue(int val)
{

	if(VISCA_set_zoom_value(&iface,&camera,zoom_value)!=VISCA_SUCCESS)
                    fprintf(stderr,"error setting zoom value");
                else
                    fprintf(stderr,"set zoom value %x",zoom_value);
}

bool viscaControl::zoom_service_calbak( visca::gs_zv::Request &req, 
				   visca::gs_zv::Response &res)
{
	if (req.set_zv >= 0 )
	{
		setZoomValue(req.set_zv);
	}
	ros::Duration(0.1).sleep();
	if(VISCA_get_zoom_value(&iface,&camera,&zoom_value)!=VISCA_SUCCESS)
                    fprintf(stderr,"error getting zoom value");
                else
                    fprintf(stderr,"get zoom value %x",zoom_value);
                res.get_zv = zoom_value;
}
void viscaControl::on_ZoomIn()
{
	zoom_value += zoom_step;
	if (zoom_value > maxZoom)
	{
		zoom_value = maxZoom;
	}
	setZoomValue(zoom_value);
}
void viscaControl::on_ZoomOut()
{
	zoom_value -= zoom_step;
	if (zoom_value < minZoom)
	{
		zoom_value = minZoom;
	}
	setZoomValue(zoom_value);
}
void viscaControl::on_Exp_Auto()
{
	if(!VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_IRIS_PRIORITY))
	{
		fprintf(stderr,"set auto exp mode iris priority\n");
	}	
}
void viscaControl::on_Exp_Maunal()
{
	if(!VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_MANUAL))
	{
		fprintf(stderr,"set camera exp mode manual\n");
	}
}

void viscaControl::on_EXP_Shutter_Inc()
{
	if(!VISCA_set_shutter_up(&iface,&camera))
	{
		fprintf(stderr,"error setting shutter up\n");
	}
}

void viscaControl::on_EXP_Shutter_Dec()
{
	if(!VISCA_set_shutter_down(&iface,&camera))
	{
		fprintf(stderr,"error setting shutter down\n");
	}

}

void viscaControl::on_EXP_Iris_Dec()
{
	if(!VISCA_set_iris_down(&iface,&camera))
	{
		fprintf(stderr,"error setting iris down\n");
	}

}

void viscaControl::on_EXP_Iris_Inc()
{
	if(!VISCA_set_iris_up(&iface,&camera))
	{
		fprintf(stderr,"error setting iris up\n");
	}
}
void viscaControl::on_Cmd_run()
{
	int val;
	while(1){
		char key =getchar(); //delay N millis, usually long enough to display and capture input
		switch (key) {
		case 'd': on_ZoomIn();break;
		case 'a': on_ZoomOut();break;
		case 'x':
			  scanf("%d",&val);
			  setZoomValue(val);
			  break;
		case '3': on_Exp_Auto();break;
		case '4': on_Exp_Maunal();break;
		case 'w': on_EXP_Shutter_Dec();break;
		case 'z': on_EXP_Shutter_Inc();break;
		case 'j': on_EXP_Iris_Dec();break;
		case 'k': on_EXP_Iris_Inc();break;
		case 'u': print_usage();break;
		default :;
		}
		usleep(10000);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "viscaControl");
	ros::NodeHandle nh;
	viscaControl m_VSCtrl;
	m_VSCtrl.openDev(argc,argv);
	m_VSCtrl.InitDev();
	ros::ServiceServer visca_service = nh.advertiseService("zoom_service_calbak", &viscaControl::zoom_service_calbak,&m_VSCtrl);
	while(ros::ok())
	{
		ros::spinOnce();
		m_VSCtrl.on_Cmd_run();
	}
}