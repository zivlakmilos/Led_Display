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
#include "eprom.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

void EPROM_writeString(unsigned int address, char *data)
{
    do
    {
        EPROM_write(address++, *data);
    } while(*data++ != '\0');
}

void EPROM_readString(unsigned int address, char *data)
{
    do
    {
        *data = EPROM_read(address++);
    } while(*data++ != '\0');
}

void EPROM_readBlock(unsigned int address, char *data, unsigned char size)
{
    int i;
    for(i = 0; i < size; i++, data)
        *data++ = EPROM_read(address++);
}

void EPROM_writeBlock(unsigned int address, char *data, unsigned char size)
{
    int i;
    for(i = 0; i < size; i++)
        EPROM_write(address++, *data++);
}

