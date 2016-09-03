#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

void timerShift(void)
{
    STATE |= SHIFT;
}

int main(void)
{
    initSystem();

    TIMER1_register(100, timerShift);

    setStringToDisplay("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789    ");

    while(1)
    {
        if(STATE & SHIFT)
        {
            STATE &= ~SHIFT;
            shiftDisplayBuffer();
        }
        refreshDisplay();
    }

    return 0;
}

