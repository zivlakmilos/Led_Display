/*
 * Code for Led Display.
 * Copyright (C) 2016 Milos Zivlak <zivlakmilos@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "system.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stddef.h>

#include "timer.h"

void (*timer1)(void) = NULL;
volatile unsigned int intervalG;
volatile unsigned int tick;

char TIMER1_register(unsigned int interval, void (*callback)(void))
{
    if(timer1 != NULL)
        return -1;

    timer1 = callback;
    intervalG = interval;
    tick = 0;

    SREG &= ~0x80;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    //OCR1AH = 0x3E;
    //OCR1AL = 0x7F;
    OCR1AH = 0x3A;
    OCR1AL = 0x98;
    TIMSK = (1 << OCIE1A);
    SREG |= 0x80;

    return 0;
}

void TIMER1_unregister()
{
    timer1 = NULL;

    SREG &= ~0x80;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    SREG |= 0x80;
}

ISR(TIMER1_COMPA_vect)
{
    if(timer1 != NULL)
    {
        if(++tick == intervalG)
        {
            tick = 0;
            timer1();
        }
    }
}
