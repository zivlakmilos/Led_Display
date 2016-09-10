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
    /*
     * Initialization
     */
    initSystem();
    TIMER1_register(100, timerShift);
    UART_init(9600, UART_INTERRUPT_RX);

    /*
     * String for displaying
     */
    char str[256];
    setStringToDisplay(str);

    /*
     * Read data from approm
     */
    EPROM_readString(str);

    while(1)
    {
        if(UART_recive(str) == 0)
        {
            /*
             * Set data to eprom and reset system to default
             */
            EPROM_writeString(str);
            initSystem();
        }

        /*
         * Shift display and refrash it
         */
        shiftDisplayBuffer();
        refreshDisplay();
    }

    return 0;
}

