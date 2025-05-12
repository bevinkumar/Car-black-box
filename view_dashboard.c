#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"

#include "ds1307.h"
#include "i2c.h"
#include "ext_eeprom.h"
unsigned char gears[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C "};
static unsigned int gearindex = 0;
static int flag=0;
unsigned char write_add=0x00;
unsigned int event_count;
extern unsigned char time[9];



void event_store(unsigned char * time,unsigned char  gear[],unsigned short speed)
{
    if(event_count > 10)
    {
        event_count = 10;
        char add = 10;
        write_add = 0x00; 
        for(int j =0 ; j <  9 ; j++)
        {    
            for(int k =0 ;k < 10 ; k++)
            {
                char ch = read_ext_eeprom(add++);
                write_ext_eeprom(write_add++, ch);
            }
        
    }
    }
    for(int i =0; i < 8 ;i++)
    {
        if(i != 2 && i != 5)
        write_ext_eeprom(write_add++,time[i]);
    }
     write_ext_eeprom(write_add++,gear[0]);
     write_ext_eeprom(write_add++,gear[1]);
     
     write_ext_eeprom(write_add++,speed/10);
     write_ext_eeprom(write_add++,speed%10);
}



void view_dashboard(void) {
    unsigned char key;
    
    key = read_switches(STATE_CHANGE);
    clcd_print("TIME", LINE1(0));
    clcd_print("EV", LINE1(9));
    clcd_print("SPD", LINE1(12));
    unsigned int adc_reg_val;
    adc_reg_val = read_adc(CHANNEL4);
    adc_reg_val = (adc_reg_val/10);
    adc_reg_val = adc_reg_val>99 ? adc_reg_val=99 : adc_reg_val;
     
    if (key == MK_SW1 && gearindex<7) {
        if(flag)
        {
            flag=0;
            gearindex=1;
        }
        else
        gearindex++;
        event_count++;
        event_store(time,gears[gearindex],adc_reg_val);
    }
    if (key == MK_SW2 && gearindex>1 ) {
       if(flag)
        {
            gearindex=1;
            flag=0;
        }
       else
        gearindex--;
       event_count++;
       event_store(time,gears[gearindex],adc_reg_val);
    }
    if(key == MK_SW4){
        flag=1;
        gearindex=8;
        event_store(time,gears[gearindex],adc_reg_val);
        event_count++;
    }
    if(key==MK_SW11)
    {
        state = e_main_menu;
         CLEAR_DISP_SCREEN;
        return;
    }
    clcd_print(time,LINE2(0));
    clcd_print(gears[gearindex], LINE2(9));
    clcd_putch((adc_reg_val / 10)+48 , LINE2(13));
    clcd_putch((adc_reg_val % 10) +48,LINE2(12));
   // clcd_print("km/h",LINE2(13));
    
   
}


