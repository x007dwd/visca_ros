/*
 * VISCA(tm) Camera Control Library Test Program
 * Copyright (C) 2002 Damien Douxchamps
 *
 * Written by Damien Douxchamps <douxchamps@ieee.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "visca/libvisca.h"



#include <stdlib.h>

#include <stdio.h>


#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */

#define EVI_D30

int main(int argc, char **argv)
{

  VISCAInterface_t iface;
  VISCACamera_t camera;


  int camera_num;
  uint8_t value;
  uint16_t zoom;
  int pan_pos, tilt_pos;

  uint16_t focus_value; 
  uint16_t set_focus_value;
  uint8_t focus_auto;

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

  iface.broadcast=0;
  VISCA_set_address(&iface, &camera_num);
  camera.address=1;
  VISCA_clear(&iface, &camera);

  VISCA_get_camera_info(&iface, &camera);
  fprintf(stderr,"Some camera info:\n------------------\n");
  fprintf(stderr,"vendor: 0x%04x\n model: 0x%04x\n ROM version: 0x%04x\n socket number: 0x%02x\n",
	  camera.vendor, camera.model, camera.rom_version, camera.socket_num);

 /* VISCA_usleep(500000);

  if (VISCA_set_zoom_value(&iface, &camera, 0x0000)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting zoom\n");

  VISCA_usleep(500000);

  VISCA_get_focus_value(&iface,&camera,&focus_value);
  printf("focus value is %x\n",focus_value);


  if (VISCA_set_zoom_value(&iface, &camera, 0x4000)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting zoom\n");

  VISCA_usleep(500000);

  if (VISCA_set_zoom_value(&iface, &camera, 0x1234)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting zoom\n");

  VISCA_usleep(500000);
  VISCA_get_focus_value(&iface,&camera,&focus_value);
  printf("focus value is %x\n",focus_value);


  if (VISCA_get_zoom_value(&iface, &camera, &zoom)!=VISCA_SUCCESS)
    fprintf(stderr,"error getting zoom\n");
  else
    fprintf(stderr,"Zoom value: 0x%04x\n",zoom);

  VISCA_usleep(500000);

  VISCA_get_focus_value(&iface,&camera,&focus_value);
  printf("focus value is %x\n",focus_value);


  if (VISCA_set_zoom_value(&iface, &camera, 0x0000)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting zoom\n");

  VISCA_get_focus_value(&iface,&camera,&focus_value);
  printf("focus value is %x\n",focus_value);



  if (VISCA_get_power(&iface, &camera, &value)!=VISCA_SUCCESS)
    fprintf(stderr,"error getting power\n");
  else
    fprintf(stderr,"power status: 0x%02x\n",value);


#ifdef EVI_D30
  if (VISCA_set_pantilt_reset(&iface, &camera)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting pan tilt home\n");
  else
    fprintf(stderr,"Setting pan tilt home\n");

  if (VISCA_set_pantilt_absolute_position(&iface, &camera,5,5,-500,-200)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting pan tilt absolute position with negative position\n");
  else
    fprintf(stderr,"Setting pan tilt absolute position\n");


  if (VISCA_get_pantilt_position(&iface, &camera, &pan_pos, &tilt_pos)!=VISCA_SUCCESS)
    fprintf(stderr,"error getting pan tilt absolute position\n");
  else
    fprintf(stderr,"Absolute position, Pan value: %d, Tilt value: %d\n",pan_pos,tilt_pos);


  if (VISCA_set_pantilt_absolute_position(&iface, &camera,18,14,500,200)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting pan tilt absolute position with positive position\n");
  else
    fprintf(stderr,"Setting pan tilt absolute position\n");

  if (VISCA_get_pantilt_position(&iface, &camera, &pan_pos, &tilt_pos)!=VISCA_SUCCESS)
    fprintf(stderr,"error getting pan tilt absolute position\n");
  else
    fprintf(stderr,"Absolute position, Pan value: %d, Tilt value: %d\n",pan_pos,tilt_pos);


  if (VISCA_set_pantilt_home(&iface, &camera)!=VISCA_SUCCESS)
    fprintf(stderr,"error setting pan tilt home\n");
  else
    fprintf(stderr,"Setting pan tilt home\n");

#endif

  //if (VISCA_set_power(&iface, &camera, VISCA_ON)!=VISCA_SUCCESS)
  //  fprintf(stderr,"error setting power\n");

  // read the rest of the data: (should be empty)
  //VISCA_get_focus_auto(&iface,&camera,&focus_auto);

  VISCA_set_focus_value(&iface,&camera,0x1010);
  VISCA_get_focus_value(&iface,&camera,&focus_value);
  printf("focus value is %x\n",focus_value);



  VISCA_set_zoom_value(&iface, &camera, 0x0D00);
  VISCA_set_shutter_value(&iface, &camera, 0x0D00);

  {
    unsigned char packet[3000];
    uint32_t buffer_size = 3000;
    if (VISCA_unread_bytes(&iface, packet, &buffer_size)!=VISCA_SUCCESS)
    {
      uint32_t i;
      fprintf(stderr, "ERROR: %u bytes not processed", buffer_size);
      for (i=0;i<buffer_size;i++)
        fprintf(stderr,"%2x ",packet[i]);
      fprintf(stderr,"\n");
    }
  }
  int temp;
  if(VISCA_get_zoom_value(&iface,&camera,&temp)!=VISCA_SUCCESS)
      fprintf(stderr,"error getting zoom value");
  else
      fprintf(stderr,"get zoom value %x",temp);

  if(VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_IRIS_PRIORITY))
  {
    fprintf(stderr,"error set auto exp mode");
  }*/
  while(1)
  {
    uint16_t zoom_value;
    char c=getchar();
    char tc,ttc;
    char  exp_mode='i';
    uint16_t iris_value;
    uint16_t shutter_value;
    uint16_t aperture_value;
    switch(c)
    {
        case 'z':
            tc =getchar();
            switch(tc)
            {
                case 's':
                scanf("%04x",&zoom_value);
                if(VISCA_set_zoom_value(&iface,&camera,zoom_value)!=VISCA_SUCCESS)
                    fprintf(stderr,"error setting zoom value");
                else
                    fprintf(stderr,"set zoom value %x",zoom_value);
                break;
                case 'g':
                if(VISCA_get_zoom_value(&iface,&camera,&zoom_value)!=VISCA_SUCCESS)
                    fprintf(stderr,"error getting zoom value");
                else
                    fprintf(stderr,"get zoom value %x",zoom_value);
                 break;

            }
            break;
        case 'f':
		tc =getchar();
		switch(tc)
		{
			case 'm':
				if(!VISCA_set_focus_mode_manual(&iface,&camera))
				fprintf(stderr,"setting focus maually!\n");
				break;
			case 'a':
				if(VISCA_set_focus_mode_auto(&iface,&camera))
				fprintf(stderr,"error setting focus maually!\n");
				break;
			case 'g':
			{
				VISCA_usleep(500000);
				if(VISCA_get_focus_value(&iface,&camera,&focus_value)!= VISCA_SUCCESS)
					printf("error getting focus value");
				else
					printf("focus value is %x\n",focus_value);
				    break;
			}	
			case 's':
			{
				scanf("%04x",&set_focus_value);
				if(VISCA_set_focus_value(&iface,&camera,set_focus_value)!= VISCA_SUCCESS)
					printf("error getting focus value");
				else
					printf("focus value is set as %x\n",set_focus_value);
				    break;
			}
			
		}
            
       case 'e':
            tc=getchar();
            switch(tc)
            {
                case 'm':
                ttc = getchar();
                switch(ttc)
                {
                    case 'i':
                    if(!VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_IRIS_PRIORITY))
                    {
                        fprintf(stderr,"set auto exp mode iris priority\n");
                    }
                    exp_mode = 'i';
                    break;
                    case 's':// shutter priority exp mode
                    if(!VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_SHUTTER_PRIORITY))
                    {
                        fprintf(stderr,"set auto exp mode shutter priority\n");
                    }
                    exp_mode = 's';
                    break;
                }
                break;
                case 'v':
                ttc=getchar();
                switch(ttc)
                {
                    case 'd':
                    switch(exp_mode)
                    {
                        case 'i':
                        if(!VISCA_set_iris_down(&iface,&camera))
                        {
                           fprintf(stderr,"error setting iris down\n");
                        }
                        break;
                        case 's':
                        if(!VISCA_set_shutter_down(&iface,&camera))
                        {
                           fprintf(stderr,"error setting shutter down\n");
                        }
                         break;
                   }
                    break;
                    case 'u':
                        switch(exp_mode)
                        {
                            case 'i':
                                 if(!VISCA_set_iris_up(&iface,&camera))
                                 {
                                     fprintf(stderr,"error setting iris up\n");
                                 }
                            break;
                            case 's':
                                  if(!VISCA_set_shutter_up(&iface,&camera))
                                 {
                                     fprintf(stderr,"error setting shutter up\n");
                                 }
                            break;
                         }
                    break;
                }
            }
        break;
        case 'm':
            if(!VISCA_set_auto_exp_mode(&iface,&camera,VISCA_AUTO_EXP_MANUAL))
            {
                fprintf(stderr,"set camera exp mode manual\n");
            }
            break;
        case 'i':
            tc=getchar();
            switch(tc)
            {
                case 'u':
                    if(!VISCA_set_iris_up(&iface,&camera))
                    {
                        fprintf(stderr,"error setting iris up\n");
                    }
                break;
                case 'd':
                if(!VISCA_set_iris_down(&iface,&camera))
                {
                    fprintf(stderr,"error setting iris down\n");
                }
                break;
            }
            if(!VISCA_get_iris_value(&iface,&camera,&iris_value))
            {
                fprintf(stderr,"iris value is %04x\n",iris_value);
            }
            break;
        case 's':
            tc=getchar();
            switch(tc)
            {
                case 'u':
                    if(!VISCA_set_shutter_up(&iface,&camera))
                    {
                        fprintf(stderr,"error setting shutter up\n");
                    }
                break;
                case 'd':
                if(!VISCA_set_shutter_down(&iface,&camera))
                {
                    fprintf(stderr,"error setting shutter down\n");
                }
                break;
            }
            if(!VISCA_get_shutter_value(&iface,&camera,&shutter_value))
            {
                fprintf(stderr,"shutter value is %04x\n",shutter_value);
            }
            break;
        case 'a':
            tc=getchar();
            switch(tc)
            {
                case 'u':
                    if(!VISCA_set_aperture_up(&iface,&camera))
                    {
                            fprintf(stderr,"set aperture value up\n");
                    }
                    break;
                case 'd':
                    if(VISCA_set_aperture_down(&iface,&camera))
                    {
                        fprintf(stderr,"seet aperture down\n");
                    }
                    break;
            }
            if(!VISCA_get_aperture_value(&iface,&camera,&aperture_value))
            {
                fprintf(stderr,"aperture value is %04x\n",aperture_value);
            }
            break;


    }
  }
  VISCA_close_serial(&iface);
  exit(0);
}
