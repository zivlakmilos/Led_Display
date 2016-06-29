#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

char abeceda[26][5] = {
    {31, 36, 68, 36, 31},
    {127, 73, 73, 73, 54},
    {62, 65, 65, 65, 34},
    {127, 65, 65, 34, 28},
    {127, 73, 73, 65, 65},
    {127, 72, 72, 72, 64},
    {62, 65, 65, 69, 38},
    {127, 8, 8, 8, 127},
    {0, 65, 127, 65, 0},
    {2, 1, 1, 1, 126},
    {127, 8, 20, 34, 65},
    {127, 1, 1, 1, 1},
    {127, 32, 16, 32, 127},
    {127, 32, 16, 8, 127},
    {62, 65, 65, 65, 62},
    {127, 72, 72, 72, 48},
    {62, 65, 69, 66, 61},
    {127, 72, 76, 74, 49},
    {50, 73, 73, 73, 38},
    {64, 64, 127, 64, 64},
    {126, 1, 1, 1, 126},
    {124, 2, 1, 2, 124},
    {126, 1, 6, 1, 126},
    {99, 20, 8, 20, 99},
    {96, 16, 15, 16, 96},
    {67, 69, 73, 81, 97},
};

char abeceda_velika[26][5] = {
    {0b00111111,0b01001000,0b10001000,0b01001000,0b00111111},
    {0b01101110,0b10010001,0b10010001,0b10010001,0b11111111},
    {0b01000010,0b10000001,0b10000001,0b10000001,0b01111110},
    {0b00111100,0b01000010,0b10000001,0b10000001,0b11111111},
    {0b10000001,0b10001001,0b10001001,0b10001001,0b11111111},
    {0b10000000,0b10000000,0b10001000,0b10001000,0b11111111},
    {0b01001110,0b10001001,0b10001001,0b10000001,0b01111110},
    {0b11111111,0b00001000,0b00001000,0b00001000,0b11111111},
    {0b00000000,0b00000000,0b11111111,0b00000000,0b00000000},
    {0b11111110,0b10000001,0b10000001,0b10000001,0b10000110},
    {0b11000001,0b00100010,0b00010100,0b00001000,0b11111111},
    {0b00000001,0b00000001,0b00000001,0b00000001,0b11111111},
    {0b11111111,0b01000000,0b00100000,0b01000000,0b11111111},
    {0b11111111,0b00001000,0b00010000,0b00100000,0b11111111},
    {0b01111110,0b10000001,0b10000001,0b10000001,0b01111110},
    {0b01100000,0b10010000,0b10010000,0b10010000,0b11111111},
    {0b01111111,0b10000011,0b10000001,0b10000001,0b01111110},
    {0b01110001,0b10001010,0b10001100,0b10001000,0b11111111},
    {0b01000110,0b10001001,0b10001001,0b10010001,0b01100010},
    {0b10000000,0b10000000,0b11111111,0b10000000,0b10000000},
    {0b11111110,0b00000001,0b00000001,0b00000001,0b11111110},
    {0b11111100,0b00000010,0b00000001,0b00000010,0b11111100},
    {0b11111110,0b00000001,0b00001110,0b00000001,0b11111110},
    {0b11100011,0b00010100,0b00001000,0b00010100,0b11100011},
    {0b10000000,0b01000000,0b00111111,0b01000000,0b10000000},
    {0b11000001,0b10100001,0b10010001,0b10001001,0b10000111}
};

char abeceda_mala[26][5] = {
    {0b00011111,0b00100100,0b01000100,0b00100100,0b00011111},
    {0b00110110,0b01001001,0b01001001,0b01001001,0b01111111},
    {0b00100010,0b01000001,0b01000001,0b01000001,0b00111110},
    {0b00011100,0b00100010,0b01000001,0b01000001,0b01111111},
    {0b01000001,0b01001001,0b01001001,0b01001001,0b01111111},
    {0b01000000,0b01000000,0b01001000,0b01001000,0b01111111},
    {0b00100110,0b01000101,0b01000101,0b01000001,0b00111110},
    {0b01111111,0b00001000,0b00001000,0b00001000,0b01111111},
    {0b00000000,0b00000000,0b10111111,0b00000000,0b00000000},
    {0b10111110,0b00000001,0b00000001,0b00000001,0b00000110},
    {0b01000001,0b00100010,0b00010100,0b00001000,0b01111111},
    {0b00000001,0b00000001,0b00000001,0b00000001,0b01111111},
    {0b01111111,0b00100000,0b00010000,0b00100000,0b01111111},
    {0b01111111,0b00000100,0b00001000,0b00010000,0b01111111},
    {0b00111110,0b01000001,0b01000001,0b01000001,0b00111110},
    {0b00110000,0b01001000,0b01001000,0b01001000,0b01111111},
    {0b00111111,0b01000011,0b01000001,0b01000001,0b00111110},
    {0b00110001,0b01001010,0b01001100,0b01001000,0b01111111},
    {0b00100110,0b01001001,0b01001001,0b01001001,0b00110010},
    {0b01000000,0b01000000,0b01111111,0b01000000,0b01000000},
    {0b01111110,0b00000001,0b00000001,0b00000001,0b01111110},
    {0b01111100,0b00000010,0b00000001,0b00000010,0b01111100},
    {0b01111110,0b00000001,0b00001110,0b00000001,0b01111110},
    {0b01100011,0b00010100,0b00001000,0b00010100,0b01100011},
    {0b01000000,0b00100000,0b00011111,0b00100000,0b01000000},
    {0b01100001,0b01010001,0b01001001,0b01000101,0b01000011}
};

char brojevi[10][5] = {
    {0b01111110,0b10000001,0b10000001,0b10000001,0b01111110},
    {0b00000000,0b11111111,0b01000000,0b00100000,0b00000000},
    {0b01100001,0b10010001,0b10001001,0b10000101,0b01000011},
    {0b01101110,0b10010001,0b10000001,0b10000001,0b01000010},
    {0b00000000,0b10011111,0b01001000,0b00101000,0b00011000},
    {0b10001110,0b10010001,0b10010001,0b10010001,0b11110010},
    {0b01000110,0b10001001,0b10001001,0b10001001,0b01111110},
    {0b11100000,0b10001000,0b10000100,0b10000010,0b10000001},
    {0b01100110,0b10011001,0b10010001,0b10011001,0b01100110},
    {0b01111110,0b10010001,0b10010001,0b10010001,0b01100010}
};

char znakovi[32][8] = {
    {0b00000000,0b00000000,0b00000000,0b01000010,0b11100111,0b01000010,0b00000000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b00000000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00100100,0b11111111,0b00000000,0b11111111,0b00100100},
    {0b00000000,0b00000000,0b00000000,0b01000110,0b10001001,0b11111111,0b10010001,0b01100010},
    {0b00000000,0b00000000,0b00100000,0b01000000,0b10000000,0b01000000,0b00100000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b10100000,0b01000000,0b10100000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b11100000,0b00000000,0b11100000,0b00000000},
    {0b00000000,0b10000001,0b01000010,0b00111100,0b00000000,0b00000000,0b00000000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b00111100,0b01000010,0b10000001,0b00000000},
    {0b00000000,0b10000001,0b10000001,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b10000001,0b10000001,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000001,0b00000000},
    {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000010,0b00000001,0b00000000},
    {0b00000000,0b00000000,0b01100000,0b10010000,0b10001101,0b10000000,0b01100000,0b00000000},
    {0b00000000,0b00000000,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,0b00000000},
    {0b10000000,0b01000000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000010,0b00000001},
    {0b00000000,0b00000000,0b00010000,0b00101000,0b01000100,0b10000010,0b00000000,0b00000000},
    {0b00000000,0b00000000,0b10000010,0b01000100,0b00101000,0b00010000,0b00000000,0b00000000},
    {0b00000000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000,0b00000000},
    {0b00000000,0b00001000,0b00001000,0b00111110,0b00001000,0b00001000,0b00000000,0b00000000},
    {0b00000000,0b00001000,0b00001000,0b00101010,0b00001000,0b00001000,0b00000000,0b00000000},
    {0b00000000,0b00100010,0b00010100,0b00001000,0b00010100,0b00100010,0b00000000,0b00000000},
    {0b00000000,0b00010100,0b00010100,0b00010100,0b00010100,0b00010100,0b00000000,0b00000000},
    {0b00001000,0b00000100,0b00000100,0b00001000,0b00010000,0b00010000,0b00001000,0b00000000},
    {0b00000100,0b00000110,0b00100111,0b01010111,0b11111111,0b00000111,0b00000110,0b00000100},
    {0b00011000,0b00111100,0b01111110,0b11011011,0b10011001,0b00011000,0b00011000,0b00011000},
    {0b00011000,0b00011000,0b00011000,0b10011001,0b11011011,0b01111110,0b00111100,0b00011000},
    {0b00010000,0b00110000,0b01100000,0b11111111,0b11111111,0b01100000,0b00110000,0b00010000},
    {0b00001000,0b00001100,0b00000110,0b11111111,0b11111111,0b00000110,0b00001100,0b00001000},
    {0b11111100,0b11111110,0b11110000,0b11011000,0b11001100,0b11000110,0b01000011,0b00000001},
    {0b10000000,0b11000010,0b01100011,0b00110011,0b00011011,0b00001111,0b01111111,0b00111111},
};

char specijalni_znakovi[2][8] = {
    { 0b00010000,0b00011000,0b00010111,0b11100110,0b11100110,0b00010111,0b00011000,0b00010000},
    { 0b11100000,0b11100000,0b11111111,0b11111111,0b00000000,0b11100111,0b11100111,0b11100111}
};

void shiftRed(unsigned char value)
{
    RED_PORT &= ~(1 << RED_SHCP);
    if(value > 0)
        RED_PORT |= (1 << RED_DS);
    else
        RED_PORT &= ~(1 << RED_DS);
    RED_PORT |= (1 << RED_SHCP);
    RED_PORT &= ~(1 << RED_DS);
    RED_PORT &= ~(1 << RED_SHCP);
    RED_PORT |= (1 << RED_STCP);
    RED_PORT &= ~(1 << RED_STCP);
}

void shiftKolona(unsigned char value)
{
    KOLONA_PORT &= ~(1 << KOLONA_SHCP);
    if(value > 0)
        KOLONA_PORT |= (1 << KOLONA_DS);
    else
        KOLONA_PORT &= ~(1 << KOLONA_DS);
    KOLONA_PORT |= (1 << KOLONA_SHCP);
    KOLONA_PORT &= ~(1 << KOLONA_DS);
    KOLONA_PORT &= ~(1 << KOLONA_SHCP);
    KOLONA_PORT |= (1 << KOLONA_STCP);
    KOLONA_PORT &= ~(1 << KOLONA_STCP);
}

/*
void setRed(unsigned char value)
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        shiftRed(value % 2);
        value /= 2;
    }
}
*/

void setRed(unsigned char value)
{
    int i;
    for(i = 0; i < 8; i ++)
    {
        RED_PORT &= ~(1 << RED_SHCP);
        if(value % 2 > 0)
            RED_PORT |= (1 << RED_DS);
        else
            RED_PORT &= ~(1 << RED_DS);
        RED_PORT |= (1 << RED_SHCP);
        RED_PORT &= ~(1 << RED_DS);
        RED_PORT &= ~(1 << RED_SHCP);
        value /= 2;
    }
    RED_PORT |= (1 << RED_STCP);
    RED_PORT &= ~(1 << RED_STCP);
}

int strlen(char *str)
{
    int i;

    for(i = 0; *str != '\0'; str++, i++);

    return i;
}
