#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"
#include "uart.h"
#include "ds1307.h"
#include "ext_eeprom.h"
extern State_t state;
extern unsigned char time[9];
void set_time(void)
{
    static int once = 1;
    static int hr;
    static int min;
    static int sec;
    static int count = 2;
    static unsigned long int delay = 0;
    unsigned char key;

    clcd_print("HH : MM : SEC", LINE1(2));

    if (once == 1) {
        hr = ((time[0] - '0') * 10) + (time[1] - '0');
        min = ((time[3] - '0') * 10) + (time[4] - '0');
        sec = ((time[6] - '0') * 10) + (time[7] - '0');
        once = 0;
    }
     key = read_switches(STATE_CHANGE);
    if (key == MK_SW2) 
    { 
        if (count == 2) 
            count = 7;
        else if (count == 7) 
            count = 12;
        else 
            count = 2; 
        delay = 0; 
    }

    if (key == MK_SW1) 
    { 
        if (count == 2) 
        {
            hr++;
            if (hr > 23) hr = 0;
        } 
        else if (count == 7) 
        { 
            min++;
            if (min > 59) min = 0;
        } else if (count == 12) 
        { 
            sec++;
            if (sec > 59) sec = 0;
        }
        delay = 0;  
    }

    if (key == MK_SW11) 
    { 
        write_ds1307(HOUR_ADDR, (((hr / 10) << 4) | (hr % 10)));
        write_ds1307(MIN_ADDR, (((min / 10) << 4) | (min % 10)));
        write_ds1307(SEC_ADDR, (((sec / 10) << 4) | (sec % 10)));
        state = e_dashboard;
        CLEAR_DISP_SCREEN;
        return;
    }

    if (key == MK_SW12) { 
        state = e_dashboard;
        CLEAR_DISP_SCREEN;
        return;
    }

    
    if (delay++ < 300) {
        clcd_putch(hr / 10 + '0', LINE2(2));
        clcd_putch(hr % 10 + '0', LINE2(3));
        clcd_putch(min / 10 + '0', LINE2(7));
        clcd_putch(min % 10 + '0', LINE2(8));
        clcd_putch(sec / 10 + '0', LINE2(12));
        clcd_putch(sec % 10 + '0', LINE2(13));
    } 
    else if (delay < 600) 
    {
        clcd_putch(0xFF, LINE2(count));
        clcd_putch(0xFF, LINE2(count + 1));
    } 
    else 
    {
        delay = 0;
    }
}
