#include <stdio.h>
#include <system.h>
#include <stdlib.h>
#include <io.h>
#include "lcd_simple.h"
#include "grayscale.h"
#include "i2c.h"
#include "camera.h"
#include "vga.h"
#include "dipswitch.h"
#include "sobel.h"
#include "sys/alt_timestamp.h"
#include "alt_types.h"
alt_u32 sobel_x_start;
alt_u32 sobel_x_end;
alt_u32 sobel_x_diff;
alt_u32 sobel_y_start;
alt_u32 sobel_y_end;
alt_u32 sobel_y_diff;
alt_u32 conv_grayscale_start;
alt_u32 conv_grayscale_end;
alt_u32 conv_grayscale_diff;
alt_u32 sobel_threshold_start;
alt_u32 sobel_threshold_end;
alt_u32 sobel_threshold_diff;
int main()
{
  void *buffer1,*buffer2,*buffer3,*buffer4;
  unsigned short *image;
  unsigned char *grayscale;
  unsigned char current_mode;
  unsigned char mode;
  init_LCD();
  init_camera();
  alt_timestamp_start();
  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
  printf("Hello from Nios II!\n");
  cam_get_profiling();
  buffer1 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer2 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer3 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  buffer4 = (void *) malloc(cam_get_xsize()*cam_get_ysize());
  cam_set_image_pointer(0,buffer1);
  cam_set_image_pointer(1,buffer2);
  cam_set_image_pointer(2,buffer3);
  cam_set_image_pointer(3,buffer4);
  enable_continues_mode();
  init_sobel_arrays(cam_get_xsize()>>1,cam_get_ysize());
  do {
	  if (new_image_available() != 0) {
		  if (current_image_valid()!=0) {
			  current_mode = DIPSW_get_value();
			  mode = current_mode&(DIPSW_SW1_MASK|DIPSW_SW3_MASK|DIPSW_SW2_MASK);
			  image = (unsigned short*)current_image_pointer();
		      switch (mode) {
		      case 0 : transfer_LCD_with_dma(&image[16520],
		                	cam_get_xsize()>>1,
		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      case 1 : conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		               grayscale = get_grayscale_picture();
		               transfer_LCD_with_dma(&grayscale[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),1);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
		      	  		  vga_set_pointer(grayscale);
		      	  	   }
		      	  	   break;
		      case 2 : conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		               grayscale = get_grayscale_picture();
		               sobel_x_with_rgb(grayscale);
		               image = GetSobel_rgb();
		               transfer_LCD_with_dma(&image[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      case 3 : conv_grayscale((void *)image,
		    		                  cam_get_xsize()>>1,
		    		                  cam_get_ysize());
		               grayscale = get_grayscale_picture();
		               sobel_x(grayscale);
		               sobel_y_with_rgb(grayscale);
		               image = GetSobel_rgb();
		               transfer_LCD_with_dma(&image[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),0);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen);
		      	  		  vga_set_pointer(image);
		      	  	   }
		      	  	   break;
		      default: conv_grayscale((void *)image,
	                                  cam_get_xsize()>>1,
	                                  cam_get_ysize());
		      	  	   conv_grayscale_start = alt_timestamp();
                       grayscale = get_grayscale_picture();
                       conv_grayscale_end = alt_timestamp();
                       //sobel_x_start = alt_timestamp();
                       //sobel_x(grayscale);
                       //sobel_x_end = alt_timestamp();
                       sobel_y_start = alt_timestamp();
                       sobel_complete(grayscale);
                       //sobel_y(grayscale);
                       sobel_y_end = alt_timestamp();
                       sobel_threshold_start = alt_timestamp();
                       sobel_threshold(128);
                       sobel_threshold_end = alt_timestamp();
                       grayscale=GetSobelResult();
		               transfer_LCD_with_dma(&grayscale[16520],
		      		                	cam_get_xsize()>>1,
		      		                	cam_get_ysize(),1);
		      	  	   if ((current_mode&DIPSW_SW8_MASK)!=0) {
		      	  		  vga_set_swap(VGA_QuarterScreen|VGA_Grayscale);
		      	  		  vga_set_pointer(grayscale);
		      	  	   }
		      	  	   break;
		      }
		  }
	  }
	  printf("hallo");
	  conv_grayscale_diff = conv_grayscale_end - conv_grayscale_start;
	  printf("time convolution grayscale: %d \n",(int)conv_grayscale_diff);
	  //sobel_x_diff = sobel_x_end - sobel_x_start;
	  //printf("time sobel x: %d \n",(int)sobel_x_diff);
	  sobel_y_diff = sobel_y_end - sobel_y_start;
	  printf("time sobel: %d \n",(int)sobel_y_diff);
	  sobel_threshold_diff = sobel_threshold_end - sobel_threshold_start;
	  printf("time sobel threshold : %d \n",(int)sobel_threshold_diff);

  } while (1);
  return 0;
}
