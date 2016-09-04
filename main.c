#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "uart.h"

void timerShift(void)
{
    STATE |= SHIFT;
}

int main(void)
{
    initSystem();

    TIMER1_register(100, timerShift);
    UART_init(9600, UART_INTERRUPT_RX);

    /*
     * String for displaying
     */
    char str[256] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz   ";
    //setStringToDisplay("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789    ");
    setStringToDisplay(str);

    while(1)
    {
        UART_recive(str);
        if(STATE & SHIFT)
        {
            STATE &= ~SHIFT;
            shiftDisplayBuffer();
        }
        refreshDisplay();
    }

    return 0;
}

