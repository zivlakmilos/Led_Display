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

static volatile char rxData = UART_NODATA;

ISR(USART_RXC_vect)
{
    //while(!(UCSR0A & (1 << RXC0)));
    rxData = UDR;
}

void UART_init(unsigned short baud, unsigned char interrupt)
{
    unsigned short baudRate;
    interrupt &= 0x03;

    baudRate = F_CPU / 12 / baud - 1;
    UBRRH = (unsigned char) (baudRate >> 8);
    UBRRL = (unsigned char) baudRate;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
    UCSRB |= (interrupt << 5);
    SREG |= 80;
}

void UART_transmit(char data)
{
    while(!(UCSRA & (1 << UDRE)));
    UDR = data;
}

void UART_transmitInt(int data)
{
    unsigned char n = 1;
    unsigned char i;
    char *zaSlanje;

    int tmp = data;
    while((tmp /= 10) > 0)
        n++;

    zaSlanje = (char *)malloc(n * sizeof(int));
    //char zaSlanje[n];
    for(i = 0; i < n; i++, data /= 10)
        zaSlanje[n - i - 1] = data % 10 + 0x30;
    for(i = 0; i < n; i++)
        UART_transmit(zaSlanje[i]);
    free(zaSlanje);
}

void UART_printf(char *data, ...)
{
    va_list args;
    va_start(args, data);

    do
    {
        if(*data == '%')
        {
            switch(*++data)
            {
                case 'd':
                    UART_transmitInt(va_arg(args, int));
                    break;
                case 'c':
                    UART_transmit((char)(va_arg(args, int)));
                    break;
                case 's':
                    /*
                     * TODO:
                     *  uraditi UART_transmitString(char *);
                     *  i ovde je pozvati
                     */
                    break;
                default:
                    UART_transmit((char)(*data));
                    break;
            }
        } else
        {
            UART_transmit(*data);
        }
    } while(*(++data) != '\0');

    va_end(args);
}

void UART_recive(char *data)
{
    if(!(UCSRB & (1 << RXCIE)))
    {
        while(!(UCSRA & (1 << RXC)));
        *data = UDR;
    } else
    {
        SREG &= ~0x80;
        *data = rxData;
        if(rxData != UART_NODATA)
            rxData = UART_NODATA;
        SREG |= 0x80;
    }
}

void UART_scanf(char *data, ...)
{
    va_list args;
    va_start(args, data);

    do
    {
        if(*data == '%')
        {
            switch(*++data)
            {
                case 'c':
                    UART_recive(va_arg(args, char *));
                    break;
                case 's':
                    /*
                     * TODO:
                     *  Uraditi UART_reciveString(char *data);
                     *  i onda i ovde kod koji to poziva
                     */
                    break;
                default:
                    UART_transmit(*data);
                    break;
            }
        } else
            UART_transmit(*data);
    } while(*(++data) != '\0');

    va_end(args);
}

