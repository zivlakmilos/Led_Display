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
    unsigned char i, j, k;
    char *str;
    unsigned char status[32];
    char *ptrStatus;
    unsigned char max;

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

    TIMER1_register(100, timer_pomeranje);

    setRed(0x00);
    for(i = 0; i < 32; i++)
    {
        shiftKolona(0);
        status[i] = 0;
    }

    j = 0;
    k = 0;

    str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789    ";

    while(1)
    {
        STATE |= START;

        if(STATE & POMERI)
        {
            STATE &= ~POMERI;
            for(i = 0; i < 31; i++)
            {
                status[i] = status[i + 1];
            }

            if(str[k] == ' ')
            {
                status[31] = 0x00;
                max = 4;
            } else if(str[k] >= 'A' && str[k] <= 'Z')
            {
                status[31] = abeceda_velika[str[k] - 'A'][4 - j];
                max = 4;
            } else if(str[k] >= 'a' && str[k] <= 'z')
            {
                status[31] = abeceda_mala[str[k] - 'a'][4 - j];
                max = 4;
            } else if(str[k] >= '0' && str[k] <= '9')
            {
                status[31] = brojevi[str[k] - '0'][4 - j];
                max = 4;
            } else
            {
                unsigned char tmp;
                max = 7;
                switch(str[k])
                {
                    case ':':
                        tmp = 0;
                        break;
                    case ';':
                        tmp = 1;
                        break;
                    case '!':
                        tmp = 2;
                        break;
                    case '#':
                        tmp = 3;
                        break;
                    case '$':
                        tmp = 4;
                        break;
                    case '^':
                        tmp = 5;
                        break;
                    case '*':
                        tmp = 6;
                        break;
                    case '"':
                        tmp = 7;
                        break;
                    case '+':
                        tmp = 8;
                        break;
                    case ';':
                        tmp = 9;
                        break;
                    case '(':
                        tmp = 10;
                        break;
                    case ')':
                        tmp = 11;
                        break;
                    case '[':
                        tmp = 12;
                        break;
                    case ']':
                        tmp = 13;
                        break;
                    case '*':
                        tmp = 14;
                        break;
                    case '?':
                        tmp = 15;
                        break;
                    case '_':
                        tmp = 16;
                        break;
                    case '/':
                        tmp = 17;
                        break;
                    case '>':
                        tmp = 18;
                        break;
                    case '-':
                        tmp = 19;
                        break;
                    default:
                        tmp = 0;
                }
                status[31] = znakovi[tmp][7 - j];
            }
            if(++j > max)
            {
                j = 0;
                if(++k > strlen(str) - 1)
                {
                    k = 0;
                }
            }
        }

        for(ptrStatus = status;
                ptrStatus < status + 32;
                ptrStatus += 8)
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
        }
    }

    while(1);

    return 0;
}
