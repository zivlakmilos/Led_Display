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

#ifndef _UART_H_
#define _UART_H_

#define UART_INTERRUPT_DISABLE      0x00
#define UART_INTERRUPT_TX           0x01    // Not ussing for now
#define UART_INTERRUPT_RX           0x02

#define UART_NODATA                 0x00

void UART_init(unsigned short baud, unsigned char interrupt);
void UART_transmit(char data);
void UART_transmitInt(int data);
void UART_printf(char *data, ...);

char UART_recive(char *data);
void UART_scanf(char *data, ...);

#endif  // _UART_H_

