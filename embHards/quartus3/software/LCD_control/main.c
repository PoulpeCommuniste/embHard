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
	LCD_GPIO_CS_n = 0x2
};
enum LCD_REG {
	LCD_COMMAND = 0,
	LCD_DATA = 2,
};
int counter = 0;

void init_LCD() {
	  IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT,LCD_GPIO_Reset_n);  // GPIO 0 is resetn  set reset on and the 16 bits mod is already write in VHDL
      while (counter<100){}   // include delay of at least 120 ms use your timer or a loop
      IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT_CLR,LCD_GPIO_CS_n);  // set CS to 0 for activate it
      IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,GPIO_PORT_SET,LCD_GPIO_Reset_n); // set RESET to 1 for desactivate it
      while (counter<200){}   // include delay of at least 120 ms use your timer or a loop

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
      IOWR_16DIRECT(LCD_CONTROLLER_0_BASE,LCD_COMMAND,command); // Adapt this line
  }

  void LCD_Write_Data(int data) {
      IOWR_16DIRECT(LCD_CONTROLLER_0_BASE,LCD_DATA,data); // Adapt this line
  }
static void timer_interrupt(void *context, alt_u32 id){
    counter++; // increase counter
    //IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,SIZEOF32INT*2,counter); // writing the counter to register for the LEDs
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE,0); // ack to timer
}
void initLEDs(void){
    IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,0,0xFFFF);
}
void initIRQ(void){
    alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,TIMER_0_IRQ,(void*)timer_interrupt,NULL,0x0); // init of interupt handler
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,								// init of timer
                                     ALTERA_AVALON_TIMER_CONTROL_CONT_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_START_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

}
int main()
{
    printf("Lets start counting \n");
    initLEDs();
    initIRQ();
    init_LCD();
    //test = alt_irq_enabled();TIMER_0_BASE
    while(1)
    {
        printf("counter = %d \n",counter);
        //printf("test = %d \n",test);
        LCD_Write_Command(0x002C);
        for(int i = 0; i< LCD_WIDTH*LCD_HEIGHT; i++){
        	LCD_Write_Data(i&0xFFFF);
        }

    }
    return 1;
}






