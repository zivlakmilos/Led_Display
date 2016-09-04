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
#include <util/delay.h>
#include <stdlib.h>

const char abeceda_velika[26][5] = {
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

const char abeceda_mala[26][5] = {
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

const char brojevi[10][5] = {
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

/*
const char znakovi[32][8] = {
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

const char specijalni_znakovi[2][8] = {
    { 0b00010000,0b00011000,0b00010111,0b11100110,0b11100110,0b00010111,0b00011000,0b00010000},
    { 0b11100000,0b11100000,0b11111111,0b11111111,0b00000000,0b11100111,0b11100111,0b11100111}
};
*/

/*
const char ascii[][8] = {
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//space
    {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000100, 0b00000000},//!
    {0b00001010, 0b00001010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//"
    {0b00001010, 0b00001010, 0b00011111, 0b00001010, 0b00011111, 0b00001010, 0b00001010, 0b00000000},//#
    {0b00000100, 0b00001111, 0b00010100, 0b00001110, 0b00000101, 0b00011110, 0b00000100, 0b00000000},//$
    {0b00011000, 0b00011001, 0b00000010, 0b00000100, 0b00001000, 0b00010011, 0b00000011, 0b00000000},//%
    {0b00001000, 0b00010100, 0b00010100, 0b00001000, 0b00010101, 0b00010010, 0b00001101, 0b00000000},//&
    {0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//'
    {0b00000010, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000010, 0b00000000},//(
    {0b00001000, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00001000, 0b00000000},//)
    {0b00000000, 0b00010101, 0b00001110, 0b00011111, 0b00001110, 0b00010101, 0b00000000, 0b00000000},//*
    {0b00000000, 0b00000100, 0b00000100, 0b00011111, 0b00000100, 0b00000100, 0b00000000, 0b00000000},//+
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00010000, 0b00000000},//,
    {0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//-
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00000000},//.
    {0b00000000, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00000000, 0b00000000},// /
    {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},//0
    {0b00000000, 0b11111111, 0b01000000, 0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b01100001, 0b10010001, 0b10001001, 0b10000101, 0b01000011, 0b00000000, 0b00000000, 0b00000000},
    {0b01101110, 0b10010001, 0b10000001, 0b10000001, 0b01000010, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b10011111, 0b01001000, 0b00101000, 0b00011000, 0b00000000, 0b00000000, 0b00000000},
    {0b10001110, 0b10010001, 0b10010001, 0b10010001, 0b11110010, 0b00000000, 0b00000000, 0b00000000},
    {0b01000110, 0b10001001, 0b10001001, 0b10001001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11100000, 0b10001000, 0b10000100, 0b10000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000},
    {0b01100110, 0b10011001, 0b10010001, 0b10011001, 0b01100110, 0b00000000, 0b00000000, 0b00000000},
    {0b01111110, 0b10010001, 0b10010001, 0b10010001, 0b01100010, 0b00000000, 0b00000000, 0b00000000},//9
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00000100, 0b00000000, 0b00000000, 0b00000000},//:
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00000100, 0b00001000, 0b00000000, 0b00000000},//;
    {0b00000001, 0b00000010, 0b00000100, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000000},//<
    {0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b00000000},//=
    {0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00000000},//>
    {0b00001110, 0b00010001, 0b00000001, 0b00000010, 0b00000100, 0b00000000, 0b00000100, 0b00000000},//?
    {0b00001110, 0b00010001, 0b00010111, 0b00010101, 0b00010110, 0b00010000, 0b00001111, 0b00000000},//@
    {0b00111111, 0b01001000, 0b10001000, 0b01001000, 0b00111111, 0b00000000, 0b00000000, 0b00000000},//A
    {0b01101110, 0b10010001, 0b10010001, 0b10010001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01000010, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b10000001, 0b10001001, 0b10001001, 0b10001001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b10000000, 0b10001000, 0b10001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01001110, 0b10001001, 0b10001001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b10000001, 0b10000001, 0b10000001, 0b10000110, 0b00000000, 0b00000000, 0b00000000},
    {0b11000001, 0b00100010, 0b00010100, 0b00001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b01000000, 0b00100000, 0b01000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b00001000, 0b00010000, 0b00100000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b01100000, 0b10010000, 0b10010000, 0b10010000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01111111, 0b10000011, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b01110001, 0b10001010, 0b10001100, 0b10001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01000110, 0b10001001, 0b10001001, 0b10010001, 0b01100010, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b10000000, 0b11111111, 0b10000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b00000001, 0b00000001, 0b00000001, 0b11111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11111100, 0b00000010, 0b00000001, 0b00000010, 0b11111100, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b00000001, 0b00001110, 0b00000001, 0b11111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b11100011, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b01000000, 0b00111111, 0b01000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11000001, 0b10100001, 0b10010001, 0b10001001, 0b10000111, 0b00000000, 0b00000000, 0b00000000},//Z
    {0b00000110, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000110, 0b00000000},//[
    {0b00000000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000000, 0b00000000},//backsalsh
    {0b00001100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00001100, 0b00000000},//]
    {0b00000100, 0b00001010, 0b00010001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//^
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000000},//_
    {0b00001000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},//`
    {0b00111111, 0b01001000, 0b10001000, 0b01001000, 0b00111111, 0b00000000, 0b00000000, 0b00000000},//a
    {0b01101110, 0b10010001, 0b10010001, 0b10010001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01000010, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b10000001, 0b10001001, 0b10001001, 0b10001001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b10000000, 0b10001000, 0b10001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01001110, 0b10001001, 0b10001001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b00000000, 0b00000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b10000001, 0b10000001, 0b10000001, 0b10000110, 0b00000000, 0b00000000, 0b00000000},
    {0b11000001, 0b00100010, 0b00010100, 0b00001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b01000000, 0b00100000, 0b01000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b11111111, 0b00001000, 0b00010000, 0b00100000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b01100000, 0b10010000, 0b10010000, 0b10010000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01111111, 0b10000011, 0b10000001, 0b10000001, 0b01111110, 0b00000000, 0b00000000, 0b00000000},
    {0b01110001, 0b10001010, 0b10001100, 0b10001000, 0b11111111, 0b00000000, 0b00000000, 0b00000000},
    {0b01000110, 0b10001001, 0b10001001, 0b10010001, 0b01100010, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b10000000, 0b11111111, 0b10000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b00000001, 0b00000001, 0b00000001, 0b11111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11111100, 0b00000010, 0b00000001, 0b00000010, 0b11111100, 0b00000000, 0b00000000, 0b00000000},
    {0b11111110, 0b00000001, 0b00001110, 0b00000001, 0b11111110, 0b00000000, 0b00000000, 0b00000000},
    {0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b11100011, 0b00000000, 0b00000000, 0b00000000},
    {0b10000000, 0b01000000, 0b00111111, 0b01000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
    {0b11000001, 0b10100001, 0b10010001, 0b10001001, 0b10000111, 0b00000000, 0b00000000, 0b00000000},//z
    {0b00000010, 0b00000100, 0b00000100, 0b00001000, 0b00000100, 0b00000100, 0b00000010, 0b00000000},//{
    {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000000},//|
    {0b00001000, 0b00000100, 0b00000100, 0b00000010, 0b00000100, 0b00000100, 0b00001000, 0b00000000},//}
    {0b00000000, 0b00000000, 0b00001000, 0b00010101, 0b00000010, 0b00000000, 0b00000000, 0b00000000},//~
};
*/

/*
 * Registers (special variables)
 */
volatile unsigned char STATE = 0x00;     // State - user defined status register

/*
 * Variables
 */
char displayBuffer[32];
char *stringToDisplay = NULL;
unsigned char currentCharacter;
unsigned char currentCharacterColumn;

/*
 * Functions
 */

void initSystem(void)
{
    int i;

    /*
     * Initialize GPIO
     */
    COLUMN_DDR = 0x00;
    ROW_DDR = 0x00;
    STATE = 0x00;

    COLUMN_DDR |= (1 << COLUMN_SHCP) |
                  (1 << COLUMN_STCP) |
                  (1 << COLUMN_DS);
    ROW_DDR |= (1 << ROW_SHCP) |
               (1 << ROW_STCP) |
               (1 << ROW_DS);

    COLUMN_PORT = 0x00;
    ROW_PORT = 0x00;

    /*
     * Initialize display buffer to display nothing
     */
    setRow(0x00);
    for(i = 0; i < 32; i++)
    {
        shiftColumn(0);
        displayBuffer[i] = 0;
    }
}

void shiftRow(unsigned char value)
{
    ROW_PORT &= ~(1 << ROW_SHCP);
    if(value > 0)
        ROW_PORT |= (1 << ROW_DS);
    else
        ROW_PORT &= ~(1 << ROW_DS);
    ROW_PORT |= (1 << ROW_SHCP);
    ROW_PORT &= ~(1 << ROW_DS);
    ROW_PORT &= ~(1 << ROW_SHCP);
    ROW_PORT |= (1 << ROW_STCP);
    ROW_PORT &= ~(1 << ROW_STCP);
}

void shiftColumn(unsigned char value)
{
    COLUMN_PORT &= ~(1 << COLUMN_SHCP);
    if(value > 0)
        COLUMN_PORT |= (1 << COLUMN_DS);
    else
        COLUMN_PORT &= ~(1 << COLUMN_DS);
    COLUMN_PORT |= (1 << COLUMN_SHCP);
    COLUMN_PORT &= ~(1 << COLUMN_DS);
    COLUMN_PORT &= ~(1 << COLUMN_SHCP);
    COLUMN_PORT |= (1 << COLUMN_STCP);
    COLUMN_PORT &= ~(1 << COLUMN_STCP);
}

void setRow(unsigned char value)
{
    int i;
    for(i = 0; i < 8; i ++)
    {
        ROW_PORT &= ~(1 << ROW_SHCP);
        if(value % 2 > 0)
            ROW_PORT |= (1 << ROW_DS);
        else
            ROW_PORT &= ~(1 << ROW_DS);
        ROW_PORT |= (1 << ROW_SHCP);
        ROW_PORT &= ~(1 << ROW_DS);
        ROW_PORT &= ~(1 << ROW_SHCP);
        value /= 2;
    }
    ROW_PORT |= (1 << ROW_STCP);
    ROW_PORT &= ~(1 << ROW_STCP);
}

void shiftDisplayBuffer(void)
{
    if(!(STATE & SHIFT))
        return;
    STATE &= ~SHIFT;

    int i, j;
    int charWidth = 5;  // Default width is 5
    char tmpChar;

    for(i = 0; i < 31; i++)
    {
        displayBuffer[i] = displayBuffer[i + 1];
    }

    if(!stringToDisplay)
        return;

    tmpChar = stringToDisplay[currentCharacter];

    if(tmpChar >= 'A' &&
       tmpChar <= 'Z')
    {
        displayBuffer[i] = abeceda_velika[tmpChar - 'A'][charWidth - currentCharacterColumn - 1];
    } else if(tmpChar >= 'a' &&
              tmpChar <= 'z')
    {
        displayBuffer[i] = abeceda_mala[tmpChar - 'a'][charWidth - currentCharacterColumn - 1];
    } else if(tmpChar == ' ')
    {
        displayBuffer[i] = 0x00;    // White space
    }

    if(++currentCharacterColumn >= charWidth)
    {
        currentCharacterColumn = 0;
        if(++currentCharacter >= strlen(stringToDisplay))
            currentCharacter = 0;
    }
}

void refreshDisplay(void)
{
    char *pDisplayBuffer;
    int i;

    STATE |= START;

    for(pDisplayBuffer = displayBuffer;
        pDisplayBuffer < displayBuffer + 32;
        pDisplayBuffer += 8)
    {
        for(i = 0; i < 8; i++)
        {
            setRow(0x00);

            if(STATE & START)
            {
                STATE &= ~START;
                shiftColumn(1);
            } else
            {
                shiftColumn(0);
            }

            setRow(pDisplayBuffer[7 - i]);

            _delay_us(500); // Small delay for wait refrash
        }
    }
}

void setStringToDisplay(char *str)
{
    stringToDisplay = str;
    currentCharacter = 0;
    currentCharacterColumn = 0;
    int i;
    for(i = 0; i < 32; i++)
        displayBuffer[i] = 0;
}

unsigned int strlen(char *str)
{
    unsigned int i;
    for(i = 0; *str != '\0'; str++, i++);
    return i;
}

