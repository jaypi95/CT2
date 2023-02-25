/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module lcd
 * --               Performs all the interactions with the lcd
 * --
 * -- $Id: lcd.c 5144 2020-09-01 06:17:21Z ruan $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdio.h>
#include <string.h>

/* user includes */
#include "lcd.h"
#include "reg_ctboard.h"

/* macros */
#define LCD_ADDR_LINE1      0u
#define LCD_ADDR_LINE2      20u

#define NR_OF_CHAR_PER_LINE 20u

#define LCD_CLEAR           "                    "
#define EXPLAIN							"total throws:"

/// STUDENTS: To be programmed

void lcd_write_text(uint8_t slot, char string[]){
	uint8_t i;
	for(i = 0; i<strlen(string); i++){
		CT_LCD->ASCII[slot + i] = string[i];
	}
}

void lcd_write_value(uint8_t slot_nr, uint8_t value){
	char buffer[5];
	snprintf(buffer, 5, "%d", value);
	lcd_write_text(--slot_nr * 3u, buffer);
}

void lcd_write_total(uint8_t total_value){
	char buffer[5];
	
	lcd_write_text(LCD_ADDR_LINE2, EXPLAIN);
	snprintf(buffer, 5, "%d", total_value);
	lcd_write_text(LCD_ADDR_LINE2 + 15u, buffer);
}

void hal_ct_lcd_clear(void){
	CT_LCD->ASCII[LCD_ADDR_LINE1] = *LCD_CLEAR;
	CT_LCD->ASCII[LCD_ADDR_LINE2] = *LCD_CLEAR;
	CT_LCD->BG.GREEN = 65535;
	CT_LCD->BG.RED = 0;
	CT_LCD->BG.BLUE = 0;
}



/// END: To be programmed
