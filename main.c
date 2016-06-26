#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

#define POMERI          0x01
#define START           0x02

unsigned char STATE = 0x00;

void timer_pomeranje(void)
{
    STATE |= POMERI;
}

int main(void)
{
    unsigned char i, j, k, n;
    char *str;
    unsigned char status[32];
    char *ptrStatus;

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

    TIMER1_register(250, timer_pomeranje);

    setRed(0x00);
    for(i = 0; i < 32; i++)
    {
        shiftKolona(0);
        status[i] = 0;
    }

    j = 0;

    str = "KO JE OVDE GENIJE";
    k = strlen(str) - 1;

    while(1)
    {
        STATE |= START;

        if(STATE & POMERI)
        {
            STATE &= ~POMERI;
            for(i = 31; i > 0; i--)
            {
                status[i] = status[i - 1];
            }

            if(str[k] == ' ')
            {
                status[0] = 0x00;
            } else
            {
                status[0] = abeceda[str[k] - 'A'][4 - j];
            }
            if(++j > 4)
            {
                j = 0;
                if(--k <= 0)
                {
                    k = strlen(str) - 1;
                }
            }
        }

        ptrStatus = status;
        for(n = 0; n < 4; n++)
        {
            for(i = 0; i < 8; i++)
            {
                setRed(0x00);

                if(STATE & START)
                {
                    STATE &= ~START;
                    shiftKolona(1);
                } else
                {
                    shiftKolona(0);
                }

                setRed(ptrStatus[7 - i]);

                _delay_us(500);
            }
            ptrStatus += 8;
        }
    }

    while(1);

    return 0;
}
