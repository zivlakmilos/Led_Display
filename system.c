#include "system.h"

#include <avr/io.h>
#include <util/delay.h>

unsigned char abeceda[26][5] = {
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

unsigned char zvezda [1] [8]={
    { 0b00010000,0b00011000,0b00010111,0b11100110,0b11100110,0b00010111,0b00011000,0b00010000}};
unsigned char smajli [1] [8]={
    { 0b11100000,0b11100000,0b11111111,0b11111111,0b00000000,0b11100111,0b11100111,0b11100111}};
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
