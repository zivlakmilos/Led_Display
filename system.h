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

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifndef F_CPU
#define F_CPU 12000000UL
#endif // F_CPU

/*
 * Column shift register
 */
#define COLUMN_PORT     PORTC
#define COLUMN_DDR      DDRC
#define COLUMN_SHCP     PC0
#define COLUMN_STCP     PC1
#define COLUMN_DS       PC2

/*
 * Row shift register
 */
#define ROW_PORT        PORTC
#define ROW_DDR         DDRC
#define ROW_SHCP        PC5
#define ROW_STCP        PC4
#define ROW_DS          PC3

/*
 * State register data
 */
#define SHIFT           0x01
#define START           0x02
#define DATA_RECIVED    0x04

/*
 * User defined registers
 */
extern volatile unsigned char STATE;    // State - user defined status register

/*
 * Functions
 */

void initSystem(void);

void shiftRow(unsigned char value);
void shiftColumn(unsigned char value);
void setRow(unsigned char value);

unsigned int strlen(char *str);
void setStringToDisplay(char *str);
void shiftDisplayBuffer(void);
void refreshDisplay(void);

#endif // _SYSTEM_H_

