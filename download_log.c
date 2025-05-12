#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"
#include "uart.h"
#include "ext_eeprom.h"
extern unsigned int event_count;
extern State_t state;
void download_log(void)
{
    
    unsigned char read_add = 0x00;  
    unsigned char time[9];          
    unsigned char gear[3];          

    static int event_index = 0;  
    if(event_count)
    {
        
        clcd_print("LOGS DOWNLOADED ",LINE1(0));
        clcd_print("SUCCESSFULLY",LINE2(0));
        
        puts("  TIME       GEAR   SPD\n\r");
        while(event_index < event_count )
        {

            putch(event_index + '0');
            read_add = event_index * 10;

            puts("  ");
            for (int i = 0; i < 8; i++) 
            {
                if(i != 2 && i!= 5)
                time[i] = read_ext_eeprom(read_add++);
                else
                    time[i] = ':';
            }
            time[8] = '\0'; 

           
           
            gear[0] = read_ext_eeprom(read_add++);
            gear[1] = read_ext_eeprom(read_add++);
            gear[2] = '\0'; 
            

            puts(time);
            puts("  ");
            puts(gear);
            puts("   ");
            puts("  ");
            putch(read_ext_eeprom(read_add++) + '0');
            putch(read_ext_eeprom(read_add++) + '0');
            
           puts("\n\r");
         

            event_index++;
            

        }
        
    }
    else if(event_count==0)
        {
          CLEAR_DISP_SCREEN;
        clcd_print(" NO LOGS  ",LINE1(0));
        clcd_print("AVAILABLE",LINE2(0));
            puts("NO LOGS AVAILABLE TO DOWNLOAD\n\r");
        }
    
    for(long int count=0;count<200000;count++);
    state=e_main_menu;
    CLEAR_DISP_SCREEN;

}
