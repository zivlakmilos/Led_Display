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
    setStringToDisplay(str);

    while(1)
    {
        if(UART_recive(str) == 0)
            initSystem();
        shiftDisplayBuffer();
        refreshDisplay();
    }

    return 0;
}

