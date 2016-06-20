#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

int main(void)
{
    unsigned char i, j;
    char *str;

    KOLONA_DDR = 0x00;
    RED_DDR = 0x00;

    KOLONA_DDR |= (1 << KOLONA_SHCP) |
                  (1 << KOLONA_STCP) |
                  (1 << KOLONA_DS);
    RED_DDR |= (1 << RED_SHCP) |
               (1 << RED_STCP) |
               (1 << RED_DS);

    KOLONA_PORT = 0x00;
    RED_PORT = 0x00;

    for(i = 0; i < 8; i++)
    {
        shiftRed(0);
    }
    for(i = 0; i < 32; i++)
    {
        shiftKolona(0);
    }

    str =",ERA";

    while(1)
    {
        for(i = 0, j = 0; i < 32; i++)
        {
            setRed(0x00);
            if(i == 0)
                shiftKolona(1);
            else
                shiftKolona(0);
            if(i < 8)
            {
                setRed(0xFF);
                if(str[0] == '.')
                    setRed(zvezda[0][i]);
                else
                    setRed(0xFF);
                if(str[0] == ',')
                    setRed(smajli[0][i]);
                else
                    setRed(abeceda[str[j] - 'A'][4 - i]);
                if(i == 4)
                    j++;
            } else if(i >= 9 && i < 14)
            {
                setRed(0xFF);
                setRed(abeceda[str[j] - 'A'][4 - i + 9]);
                if(i == 13)
                    j++;
            } else if(i >= 16 && i < 21)
            {
                setRed(0xFF);
                setRed(abeceda[str[j] - 'A'][4 - i + 16]);
                if(i == 20)
                    j++;
            } else if(i >= 24 && i < 29)
            {
                setRed(0xFF);
                setRed(abeceda[str[j] - 'A'][4 - i + 24]);
                if(i == 27)
                    j++;
            } else
            {
                setRed(0xFF);
                setRed(0x00);
            }

            _delay_us(500);
        }
    }

    while(1);

    return 0;
}
