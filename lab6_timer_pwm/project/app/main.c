/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 lab - Timer PWM
 * -- Description : Main program and interrupt service routine
 * --
 * --               Task 1: - Setup timer TIM4 to 1s.
 * --                       - Setup interrupt to toggle LED
 * --               Task 2: - Setup timer TIM3 to PWM mode
 * --                       - Read DIP switches to set duty cycles of channels
 * --               Task 3: - Use interrupt of TIM4 to create a transition
 * --                         from one colour to another
 * --
 * -- $Id: main.c 5605 2023-01-05 15:52:42Z frtt $
 * ------------------------------------------------------------------------- */

/* standard includes */
#include <stdint.h>
#include <reg_stm32f4xx.h>
#include <reg_ctboard.h>

/* user includes */
#include "timer.h"


/* -- Macros used as by student code
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

/// END: To be programmed

/* -- Function prototypes
 * ------------------------------------------------------------------------- */
 void TIM4_IRQHandler(void);
 

/* -- global variables visible only within this module
 * ------------------------------------------------------------------------- */

/* cyclic counter value between 0 and 0xF */
static uint16_t cycle_counter_4bit = 0;

/* -- M A I N
 * ------------------------------------------------------------------------- */

int main(void)
{
    /// STUDENTS: To be programmed

		tim4_init();
		tim3_init();
		
	

	
		while(1){
			
			
			uint8_t ch1 = CT_DIPSW->BYTE.S7_0 & 0xf;
			uint8_t ch2 = CT_DIPSW->BYTE.S15_8 & 0xf;
			uint8_t ch3 = CT_DIPSW->BYTE.S23_16 & 0xf;
			
			

      tim3_set_compare_register(PWM_CH1, 4000 * ch1);
      tim3_set_compare_register(PWM_CH2, 4000 * ch2);
      tim3_set_compare_register(PWM_CH3, 4000 * ch3);
		}



    /// END: To be programmed
}


/* -- Interrupt service routine
 * ------------------------------------------------------------------------- */

void TIM4_IRQHandler(void)
{
    /// STUDENTS: To be programmed

		tim4_reset_uif();
		
		
		//toggle LEDs
		CT_LED->BYTE.LED7_0 = ~CT_LED->BYTE.LED7_0;


    /// END: To be programmed
}
