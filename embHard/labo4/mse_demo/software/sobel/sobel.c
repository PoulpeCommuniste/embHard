/*
 * sobel.c
 *
 *  Created on: Sep 12, 2015
 *      Author: theo
 */

#include <stdlib.h>
#include <stdio.h>
#include "io.h"

const char gx_array[3][3] = {{-1,0,1},
                             {-2,0,2},
                             {-1,0,1}};
const char gy_array[3][3] = { {1, 2, 1},
                              {0, 0, 0},
                             {-1,-2,-1}};

short *sobel_x_result;
short *sobel_y_result;
unsigned short *sobel_rgb565;
unsigned char *sobel_result;
int sobel_width;
int sobel_height;
void sobel_complete( unsigned char * source )
{
	int x,y;
	int index_array[4]= {0,0,0,0};
	int index_array_x_0[3]= {0,0,0};
	int index_array_x_2[3]= {0,0,0};
	index_array[1] = sobel_width;
	index_array[2] = sobel_width<<1;

	   for (y = 1 ; y < (sobel_height-1) ; y++) { // TODO calcule des indices une fois additionner sur la ligne
		  index_array_x_0[0] = index_array[1]-1;
		  index_array_x_2[0] = index_array[2]-1;
		  index_array_x_0[1] = index_array[1];
		  index_array_x_2[1] = index_array[2];
		  index_array_x_0[2] = index_array[1]+1;
		  index_array_x_2[2] = index_array[2]+1;
	      for (x = 1 ; x < (sobel_width-1) ; x++) {
	    	  	index_array[4] = index_array[1]+ x;

	    	  	sobel_x_result[index_array[4]] = (source[index_array_x_0[1]])-(source[index_array_x_0[0]])-(source[index_array_x_0[2]] << 1)+(source[index_array_x_2[0]]<<2)-(source[index_array_x_2[1]]) + (source[index_array_x_2[2]]);
	    	  	sobel_y_result[index_array[4]] = (source[index_array_x_0[0]])+(source[index_array_x_0[1]]<<1)+(source[index_array_x_0[2]])-(source[index_array_x_2[0]])-(source[index_array_x_2[1]]<<2) - (source[index_array_x_2[2]]);
				//sobel_x_result[index] = (gx_array[0][0]*source[index-sobel_width-1])+(gx_array[0][2]*source[index-sobel_width])+(gx_array[1][0]*source[index-sobel_width+1])+(gx_array[1][2]*source[index+sobel_width-1])+(gx_array[2][0]*source[index+sobel_width]) + (gx_array[2][2]*source[index+sobel_width+1]) ;
				//sobel_y_result[index] = (gy_array[0][0]*source[index-sobel_width-1])+(gy_array[0][1]*source[index-sobel_width])+(gy_array[0][2]*source[index-sobel_width+1])+(gy_array[2][0]*source[index+sobel_width-1])+(gy_array[2][1]*source[index+sobel_width]) + (gy_array[2][2]*source[index+sobel_width+1]) ;
				index_array_x_0[0] = index_array_x_0[1];
				index_array_x_2[0] = index_array_x_2[1];
				index_array_x_0[1] = index_array_x_0[2];
				index_array_x_2[1] = index_array_x_2[2];
				index_array_x_0[2] = index_array_x_0[1]+1;
				index_array_x_2[2] = index_array_x_2[1]+1;
	      }
	      index_array[0] = index_array[1];
		  index_array[1] = index_array[2];
		  index_array[2] = index_array[1]+sobel_width;
	   }

}
void init_sobel_arrays(int width , int height) {
	int loop;
	sobel_width = width;
	sobel_height = height;
	if (sobel_x_result != NULL)
		free(sobel_x_result);
	sobel_x_result = (short *)malloc(width*height*sizeof(short));
	if (sobel_y_result != NULL)
		free(sobel_y_result);
	sobel_y_result = (short *)malloc(width*height*sizeof(short));
	if (sobel_result != NULL)
		free(sobel_result);
	sobel_result = (unsigned char *)malloc(width*height*sizeof(unsigned char));
	if (sobel_rgb565 != NULL)
		free(sobel_rgb565);
	sobel_rgb565 = (unsigned short *)malloc(width*height*sizeof(unsigned short));
	for (loop = 0 ; loop < width*height ; loop++) {
		sobel_x_result[loop] = 0;
		sobel_y_result[loop] = 0;
		sobel_result[loop] = 0;
		sobel_rgb565[loop] = 0;
	}
}

short sobel_mac( unsigned char *pixels,
                 int x,
                 int y,
                 const char *filter,
                 unsigned int width ) {
   short dy,dx;
   short result = 0;

   for (dy = -1 ; dy < 2 ; dy++) {
      for (dx = -1 ; dx < 2 ; dx++) {
         result += filter[(dy+1)*3+(dx+1)]*
                   pixels[(y+dy)*width+(x+dx)];
      }
   }

   return result;
}

void sobel_x( unsigned char *source ) {
   int x,y;
   short result = 0;
   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	    result = 0;
			result += gx_array[0][0]*source[(y-1)*sobel_width+(x-1)];
			result += gx_array[0][1]*source[(y-1)*sobel_width+(x)];
			result += gx_array[0][2]*source[(y-1)*sobel_width+(x+1)];
			result += gx_array[1][0]*source[(y)*sobel_width+(x-1)];
			result += gx_array[1][1]*source[(y)*sobel_width+(x)];
			result += gx_array[1][2]*source[(y)*sobel_width+(x+1)];
			result += gx_array[2][0]*source[(y+1)*sobel_width+(x-1)];
			result += gx_array[2][1]*source[(y+1)*sobel_width+(x)];
			result += gx_array[2][2]*source[(y+1)*sobel_width+(x+1)];

			sobel_x_result[y*sobel_width+x] = result;//sobel_mac(source,x,y,gx_array,sobel_width);
      }
   }
}

void sobel_x_with_rgb( unsigned char *source ) {
   int x,y;
   short result;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	  result = sobel_mac(source,x,y,gx_array,sobel_width);
          sobel_x_result[y*sobel_width+x] = result;
          if (result < 0) {
        	  sobel_rgb565[y*sobel_width+x] = ((-result)>>2)<<5;
          } else {
        	  sobel_rgb565[y*sobel_width+x] = ((result>>3)&0x1F)<<11;
          }
      }
   }
}

void sobel_y( unsigned char *source ) {
   int x,y;
   short result = 0;
   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	   result = 0;
    	    result += gy_array[0][0]*source[(y-1)*sobel_width+(x-1)];
    	    result += gy_array[0][1]*source[(y-1)*sobel_width+(x)];
    	    result += gy_array[0][2]*source[(y-1)*sobel_width+(x+1)];
    	    result += gy_array[1][0]*source[(y)*sobel_width+(x-1)];
    	    result += gy_array[1][1]*source[(y)*sobel_width+(x)];
    	    result += gy_array[1][2]*source[(y)*sobel_width+(x+1)];
    	    result += gy_array[2][0]*source[(y+1)*sobel_width+(x-1)];
			result += gy_array[2][1]*source[(y+1)*sobel_width+(x)];
			result += gy_array[2][2]*source[(y+1)*sobel_width+(x+1)];

			sobel_y_result[y*sobel_width+x] = result ;// sobel_mac(source,x,y,gy_array,sobel_width);
      }
   }
}

void sobel_y_with_rgb( unsigned char *source ) {
   int x,y;
   short result;

   for (y = 1 ; y < (sobel_height-1) ; y++) {
      for (x = 1 ; x < (sobel_width-1) ; x++) {
    	  result = sobel_mac(source,x,y,gy_array,sobel_width);
         sobel_y_result[y*sobel_width+x] = result;
         if (result < 0) {
       	  sobel_rgb565[y*sobel_width+x] = ((-result)>>2)<<5;
         } else {
       	  sobel_rgb565[y*sobel_width+x] = ((result>>3)&0x1F)<<11;
         }
      }
   }
}

void sobel_threshold(short threshold) {
	int x,y,arrayindex;
	short sum,value;
	for (y = 1 ; y < (sobel_height-1) ; y++) {
		for (x = 1 ; x < (sobel_width-1) ; x++) {
			arrayindex = (y*sobel_width)+x;
			value = sobel_x_result[arrayindex];
			sum = (value < 0) ? -value : value;
			value = sobel_y_result[arrayindex];
			sum += (value < 0) ? -value : value;
			sobel_result[arrayindex] = (sum > threshold) ? 0xFF : 0;
		}
	}
}

unsigned short *GetSobel_rgb() {
	return sobel_rgb565;
}

unsigned char *GetSobelResult() {
	return sobel_result;
}
