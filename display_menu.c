
#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "black_box.h"
#include "adc.h"

extern State_t state;
static unsigned int count=0;
static unsigned int next=0;
const unsigned char* main_menu[4]={"VIEW LOG             ","CLEAR LOG             ","DOWMNLOAD LOG           ","SET TIME          "};
void display_main_menu(void)
{
     unsigned char key;

    key = read_switches(STATE_CHANGE);
    if(key==MK_SW2)
    {
        if(next==0)
        {
            next=1;
        }
        else if(count<2)
        {
            count++;
        }
    }
    else if(key==MK_SW1)
    {
        if(next==1)
        {
            next=0;
        }
        else if(count>0)
        {
            count--;
        }
    }
   
    if (next == 0)
    {
        clcd_putch('*', LINE1(1));
        clcd_putch(' ',LINE2(1));
        clcd_print(main_menu[count], LINE1(3));          
        clcd_print(main_menu[count + 1], LINE2(3));      
    }
    else
    {
        clcd_print(main_menu[count], LINE1(3));         
        clcd_putch('*', LINE2(1));
        clcd_putch(' ',LINE1(1));
        clcd_print(main_menu[count + 1], LINE2(3));     
    }
    if(key==MK_SW11)
    {
        
        state = count + next + 2;
        CLEAR_DISP_SCREEN;
        return;
    }
    if(key==MK_SW12)
    {
        state=e_dashboard;
        CLEAR_DISP_SCREEN;
        return;

    }
   }
