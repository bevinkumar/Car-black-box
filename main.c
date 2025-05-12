/*
 * File:   main.c
 * Author: Bevin Kumar
 *
 * Created on 14 February, 2024, 5:50 PM
 */


#include "black_box.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "uart.h"
#include "ds1307.h"
#include "i2c.h"
#include "ext_eeprom.h"

State_t state;
unsigned char time[9];
unsigned char clock_reg[3];
static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}
void init_config()
{
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_uart();
    init_i2c();
	init_ds1307();
    state = e_dashboard;//0
}

void main(void) 
{
    init_config();

    while(1)
    {
        // Detect key press
        get_time();
        
        
        switch (state)
        {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;
            
            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;
            
            case e_view_log:
                // Display dashboard
                view_log();
                break;
                 
            case e_download_log:
                download_log();
                break;
                
            case e_clear_log:
               clear_log();
                break;
                
                      
            case e_set_time:               
                set_time();
                break;
                
        }
        
    }
    
}
