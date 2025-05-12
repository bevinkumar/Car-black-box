/*
 * File:   clear_log.c
 * Author: User
 *
 * Created on 16 February, 2025, 12:07 PM
 */


#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"
#include "eeprom.h"
extern unsigned int event_count;
extern unsigned char write_add; 
void clear_log(void){
       static unsigned int wait=0; 
    clcd_print("All Logs are", LINE1(0));
    clcd_print("Cleared", LINE2(0));
    
    
    if (wait++ == 3000) 
    {
        wait = 0;
        state = e_main_menu;
        event_count = 0;
        write_add=0x00;
        CLEAR_DISP_SCREEN;
    }
}

