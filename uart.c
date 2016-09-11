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
#include "uart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdarg.h>
#include <stdlib.h>

volatile char rxDataBuffer[256];
volatile unsigned char rxDataBufferCount;

ISR(USART_RXC_vect)
{
    if(rxDataBufferCount < 255)
        rxDataBuffer[rxDataBufferCount] = UDR;
    else
        rxDataBuffer[rxDataBufferCount] = '\0';

    if(rxDataBuffer[rxDataBufferCount] == '\0' ||
       rxDataBuffer[rxDataBufferCount] == '\n')
    {
        STATE |= DATA_RECIVED;
        rxDataBuffer[rxDataBufferCount] == '\0';
    }

    ++rxDataBufferCount;
}

void UART_init(unsigned short baud, unsigned char interrupt)
{
    unsigned short baudRate;
    interrupt &= 0x03;
    rxDataBufferCount = 0;

    SREG &= ~0x80;
    baudRate = F_CPU / 16 / baud - 1;
    UBRRH = (unsigned char) (baudRate >> 8);
    UBRRL = (unsigned char) baudRate;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
    UCSRB |= (interrupt << 6);
    SREG |= 0x80;
}

void UART_transmit(char data)
{
    while(!(UCSRA & (1 << UDRE)));
    UDR = data;
}

char UART_recive(char *data)
{
    if(!(UCSRB & (1 << RXCIE)))
    {
        while(!(UCSRA & (1 << RXC)));
        *data = UDR;
        return 0;
    } else
    {
        if(STATE & DATA_RECIVED)
        {
            STATE &= ~DATA_RECIVED;
            SREG &= ~0x80;
            int i;
            for(i = 0; i < rxDataBufferCount; i++)
                data[i] = rxDataBuffer[i];
            data[i] = '\0';
            rxDataBufferCount = 0;
            SREG |= 0x80;
            return 0;
        }
    }

    return -1;
}

