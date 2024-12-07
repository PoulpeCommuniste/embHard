/*
 * main.c
 *
 *  Created on: Oct 25, 2024
 *      Author: deremos
 */

#include "io.h"
#include <stdio.h>
#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_timer_regs.h>
#include <priv/alt_legacy_irq.h>
#include "sys/alt_sys_init.h"
#include "image1.h"

#define SIZEOF32INT 4


#define LCD_WIDTH 240
#define LCD_HEIGHT 320
enum GPIO_REG {
	GPIO_DIR = 0,
	GPIO_PORT = 8,
	GPIO_PORT_SET = 12,
	GPIO_PORT_CLR = 16,
};
enum LCD_GPIO{
	LCD_GPIO_Reset_n = 0x1,
	LCD_GPIO_CS_n = 0x2,
	LCD_GPIO_RD_n = 0x4,
	LCD_GPIO_IM0 = 0x8,

};
enum DMA_REG {
	LCD_COMMAND = 0,
	LCD_DATA = 4,
	DMA_POINTER = 8,
	DMA_SIZE = 12,
	DMA_CONTROL = 16,
};
enum DMA_CONTROL {
	DMA_CONTROL_START = 0x1,
	DMA_CONTROL_ACK = 0x4,
};
int counter = 0;
int dma_flag_end = 0;
void DMA_interrupt(void){
	dma_flag_end = 1;
	DMA_ACK_IRQ();
}
void init_DMA_IRQ(){
	//alt_ic_isr_register(LCD_DMA_CTRL_0_IRQ_INTERRUPT_CONTROLLER_ID,LCD_DMA_CTRL_0_IRQ,(void*)DMA_interrupt,NULL,0x0);
	alt_irq_register(0x2001040, NULL, (alt_isr_func)DMA_interrupt);

}

void init_LCD() {

	  //IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT,LCD_GPIO_Reset_n);
	  IOWR_32DIRECT(0x2001020,GPIO_PORT,LCD_GPIO_CS_n);  // GPIO 0 is resetn  set reset on and the 16 bits mod is already write in VHDL
	  IOWR_32DIRECT(0x2001020,GPIO_PORT_CLR,LCD_GPIO_Reset_n);
      while (counter<120){}   // include delay of at least 120 ms use your timer or a loop
      //IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT_CLR,LCD_GPIO_CS_n);  // set CS to 0 for activate it
      //IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT_SET,LCD_GPIO_Reset_n);
      IOWR_32DIRECT(0x2001020,GPIO_PORT_CLR,LCD_GPIO_CS_n|LCD_GPIO_IM0);  // set CS to 0 for activate it and IM0
      IOWR_32DIRECT(0x2001020,GPIO_PORT_SET,LCD_GPIO_Reset_n|LCD_GPIO_RD_n); // set RESET and RD_n to 1 for desactivate it
      while (counter<240){}   // include delay of at least 120 ms use your timer or a loop

      LCD_Write_Command(0x0028);     //display OFF
      LCD_Write_Command(0x0011);     //exit SLEEP mode
      LCD_Write_Data(0x0000);

      LCD_Write_Command(0x00CB);     //Power Control A
      LCD_Write_Data(0x0039);     //always 0x39
      LCD_Write_Data(0x002C);     //always 0x2C
      LCD_Write_Data(0x0000);     //always 0x00
      LCD_Write_Data(0x0034);     //Vcore = 1.6V
      LCD_Write_Data(0x0002);     //DDVDH = 5.6V

      LCD_Write_Command(0x00CF);     //Power Control B
      LCD_Write_Data(0x0000);     //always 0x00
      LCD_Write_Data(0x0081);     //PCEQ off
      LCD_Write_Data(0x0030);     //ESD protection

      LCD_Write_Command(0x00E8);     //Driver timing control A
      LCD_Write_Data(0x0085);     //non - overlap
      LCD_Write_Data(0x0001);     //EQ timing
      LCD_Write_Data(0x0079);     //Pre-charge timing


      LCD_Write_Command(0x00EA);     //Driver timing control B
      LCD_Write_Data(0x0000);        //Gate driver timing
      LCD_Write_Data(0x0000);        //always 0x00

      LCD_Write_Command(0x00ED); //Power‐On sequence control
      LCD_Write_Data(0x0064);        //soft start
      LCD_Write_Data(0x0003);        //power on sequence
      LCD_Write_Data(0x0012);        //power on sequence
      LCD_Write_Data(0x0081);        //DDVDH enhance on

      LCD_Write_Command(0x00F7);     //Pump ratio control
      LCD_Write_Data(0x0020);     //DDVDH=2xVCI

      LCD_Write_Command(0x00C0);    //power control 1
      LCD_Write_Data(0x0026);
      LCD_Write_Data(0x0004);     //second parameter for ILI9340 (ignored by ILI9341)

      LCD_Write_Command(0x00C1);     //power control 2
      LCD_Write_Data(0x0011);

      LCD_Write_Command(0x00C5);     //VCOM control 1
      LCD_Write_Data(0x0035);
      LCD_Write_Data(0x003E);

      LCD_Write_Command(0x00C7);     //VCOM control 2
      LCD_Write_Data(0x00BE);

      LCD_Write_Command(0x00B1);     //frame rate control
      LCD_Write_Data(0x0000);
      LCD_Write_Data(0x0010);

      LCD_Write_Command(0x003A);    //pixel format = 16 bit per pixel
      LCD_Write_Data(0x0055);

      LCD_Write_Command(0x00B6);     //display function control
      LCD_Write_Data(0x000A);
      LCD_Write_Data(0x00A2);

      LCD_Write_Command(0x00F2);     //3G Gamma control
      LCD_Write_Data(0x0002);         //off

      LCD_Write_Command(0x0026);     //Gamma curve 3
      LCD_Write_Data(0x0001);

      LCD_Write_Command(0x0036);     //memory access control = BGR
      LCD_Write_Data(0x0000);

      LCD_Write_Command(0x002A);     //column address set
      LCD_Write_Data(0x0000);
      LCD_Write_Data(0x0000);        //start 0x0000
      LCD_Write_Data(0x0000);
      LCD_Write_Data(0x00EF);        //end 0x00EF

      LCD_Write_Command(0x002B);    //page address set
      LCD_Write_Data(0x0000);
      LCD_Write_Data(0x0000);        //start 0x0000
      LCD_Write_Data(0x0001);
      LCD_Write_Data(0x003F);        //end 0x013F

      LCD_Write_Command(0x0029);

  }

  void LCD_Write_Command(int command) {
      IOWR_32DIRECT(0x2001040,LCD_COMMAND,command); // Adapt this line
  }

  void LCD_Write_Data(int data) {
      IOWR_32DIRECT(0x2001040,LCD_DATA,data); // Adapt this line
  }
  void DMA_Write_Data_Size(int data_size) {
	  IOWR_32DIRECT(0x2001040,DMA_SIZE,data_size);// Adapt this line
   }
  void DMA_Start(void) {
	  IOWR_32DIRECT(0x2001040,DMA_CONTROL,DMA_CONTROL_START);  // Adapt this line
   }
  void DMA_ACK_IRQ(void) {
	  IOWR_32DIRECT(0x2001040,DMA_CONTROL,DMA_CONTROL_ACK);  // Adapt this line
  }
  void DMA_Write_Data_Address(void * data_address) {
      IOWR_32DIRECT(0x2001040,DMA_POINTER,(int)data_address); // Adapt this line
  }
  void DMA_Write(int data_size,void * data_address){
	  DMA_Write_Data_Size(data_size);
	  DMA_Write_Data_Address(data_address);
	  LCD_Write_Command(0x002C);
	  DMA_Start();
	  while(!dma_flag_end);
	  dma_flag_end = 0;
  }
static void timer_interrupt(void *context, alt_u32 id){
    counter++; // increase counter
    IOWR_32DIRECT(0x2001020,SIZEOF32INT*2,counter); // writing the counter to register for the LEDs
    IOWR_ALTERA_AVALON_TIMER_STATUS(0x2001000,0); // ack to timer
}
void initLEDs(void){
    IOWR_32DIRECT(0x2001020,0,0xFFFFFFFF);
}
void initIRQ(void){
    alt_ic_isr_register(0,2,(void*)timer_interrupt,NULL,0x0); // init of interupt handler
    IOWR_ALTERA_AVALON_TIMER_CONTROL(0x2001000,								// init of timer
                                     ALTERA_AVALON_TIMER_CONTROL_CONT_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_START_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

}
int main()
{
    printf("Lets start counting \n");
    initLEDs();
    initIRQ();
    init_DMA_IRQ();
    init_LCD();
    //test = alt_irq_enabled();TIMER_0_BASE
    while(1)
    {
        printf("counter = %d \n",counter);
        //printf("test = %d \n",test);

        LCD_Write_Command(0x002C);
        /*
        for(int i = 0; i< LCD_WIDTH*LCD_HEIGHT; i++){
        	LCD_Write_Data(i&0xFFFF);//LCD_Write_Data(images[i]&0xFFFF);
        }*/
        DMA_Write(240*320*2,images);
    }
    return 1;
}






