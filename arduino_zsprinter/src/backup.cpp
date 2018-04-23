#include "xparameters.h"
#include "xil_io.h"
#include "SeeedOLED.h"
#include "circular_buffer.h"
#include "timer.h"
#include "gpio.h"
#include "i2c.h"

#define CLEAR_DISPLAY       0x1
#define PRINT_STRING        0x3
#define DRAW_LINE           0x5
#define DRAW_RECT           0x7

/*
 *  Passed parameters in MAILBOX_DATA
 *      String mode =>      length (number of characters to be printed)
                            x_position, y_position
 *      Line mode =>        startx_position, starty_position, 
                            endx_position, endy_position
 *      Rectangle mode =>   startx_position, starty_position, 
                            endx_position, endy_position
 */


// constants used to write to GPIO pins
void print_string(void) {
    int x_position, y_position, length;
    char ch[64];
    int i;

    length=MAILBOX_DATA(0);
    x_position=MAILBOX_DATA(1);
    y_position=MAILBOX_DATA(2);
    for(i=0; i<length; i++){
        ch[i] = MAILBOX_DATA(3+i);
    }
    ch[i]='\0'; // make sure it is null terminated string
    
    SeeedOled.setTextXY(x_position,y_position);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString(ch); //Print the String
}

int main (void) {

    u32 cmd;

    SeeedOled.init();  //initialze SEEED OLED display
    SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();           //Set addressing mode to Page Mode
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Hello World!"); //Print the String

    while(1){
        while(MAILBOX_CMD_ADDR==0);
        cmd = MAILBOX_CMD_ADDR;
        
        char charbuf[1];
        int length;
        switch(cmd){
            case PRINT_STRING:
                print_string();
                MAILBOX_CMD_ADDR = 0x0;
                break;
            
            default:
                MAILBOX_CMD_ADDR = 0x0;
                break;
            }
    }
    return 0;
}

