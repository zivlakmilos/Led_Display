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

#ifndef _EPROM_H_
#define _EPROM_H_

#define ADR_DISPLAY_STRING      0x00    // Addres of string to display

void EPROM_write(unsigned int address, char data);
void EPROM_writeString(unsigned int address, char *data);

void EPROM_read(unsigned int address, char *data);
void EPROM_readString(unsigned int address, char *data);

#endif  // _EPROM_H_

