#include "system.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "timer.h"
#include "uart.h"
#include "eprom.h"

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
    char str[256] = "";
    setStringToDisplay(str);

    /*
     * Read data from approm
     */
    if(EPROM_read(ADR_STRING_SIZE) > 0)
        EPROM_readBlock(ADR_DISPLAY_STRING, str, EPROM_read(ADR_STRING_SIZE));

    while(1)
    {
        if(UART_recive(str) == 0)
        {
            /*
             * Set data to eprom and reset system to default
             */
            unsigned char length = strlen(str);
            EPROM_write(ADR_STRING_SIZE, length);
            EPROM_writeBlock(ADR_DISPLAY_STRING, str, length);
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

