/*
 * counter.c
 *
 *  Created on: Oct 11, 2024
 *      Author: deremos
 */
#include "io.h"
#include <stdio.h>
#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_timer_regs.h>
#include <priv/alt_legacy_irq.h>
#define SIZEOF32INT 4
int counter = 0;

static void timer_interrupt(void *context, alt_u32 id){
    counter++; // increase counter
    IOWR_32DIRECT(LEDS_CONTROLLER_0_BASE,SIZEOF32INT*2,counter); // writing the counter to register for the LEDs
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

    //test = alt_irq_enabled();TIMER_0_BASE
    while(1)
    {
        printf("counter = %d \n",counter);
        //printf("test = %d \n",test);
    }
    return 1;
}


