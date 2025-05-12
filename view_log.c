#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"
#include "ext_eeprom.h"
extern unsigned int event_count;
unsigned char read_add = 0x00;
void view_log(void) {
    unsigned char key;
    unsigned char read_add = 0x00;
    unsigned char time[9];          
    unsigned char gear[3];          

    static unsigned char event_index = 0; 
    read_add=event_index*10;
    key = read_switches(STATE_CHANGE);
    if(key== MK_SW12)
        {
            state=1;
            CLEAR_DISP_SCREEN;
            return;
        }
   
    
        

        
        for (int i = 0; i < 8; i++) {
            if(i!=2 && i!= 5)
            time[i] = read_ext_eeprom(read_add++);
           else
             time[i]=':';  
        }
        time[8] = '\0'; 

      
        gear[0] = read_ext_eeprom(read_add++);
        gear[1] = read_ext_eeprom(read_add++);
        gear[2] = '\0'; 

        
        unsigned char speed_tens = read_ext_eeprom(read_add++);
        unsigned char speed_units = read_ext_eeprom(read_add++);
       

        
        CLEAR_DISP_SCREEN;
       
        

        // Wait for key input
        
        
        if(event_count)
        {
                        clcd_print("# TIME     GR SP", LINE1(0));
                        clcd_putch((event_index+1) + 48,LINE2(0));
                        clcd_print(time, LINE2(2));
                        clcd_putch(gear[0], LINE2(11));
                        clcd_putch(gear[1],LINE2(12));
                        clcd_putch((speed_tens +'0') , LINE2(14));
                        clcd_putch((speed_units +'0'), LINE2(15));
            if (key == MK_SW2) 
            {  
                if (event_index < event_count - 1) 
                {
                     
                    event_index++;
                }
            } else if (key == MK_SW1) 
            {  
                if (event_index > 0) 
                {
                     
                    event_index--;
                }
            } 
            }
        
        else if(event_count==0)
        {
            clcd_print("NO LOGS ",LINE1(0));
            clcd_print("AVAILABLE",LINE2(7));
           
        }
}
 