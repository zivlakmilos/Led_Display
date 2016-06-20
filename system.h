#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifndef F_CPU
#define F_CPU 12000000UL
#endif // F_CPU

#define KOLONA_PORT     PORTC
#define KOLONA_DDR      DDRC
#define KOLONA_SHCP     PC0
#define KOLONA_STCP     PC1
#define KOLONA_DS       PC2

#define RED_PORT        PORTC
#define RED_DDR         DDRC
#define RED_SHCP        PC5
#define RED_STCP        PC4
#define RED_DS          PC3

extern unsigned char abeceda[26][5];
extern unsigned char zvezda[1][8];
extern unsigned char smajli[1][8];

void shiftRed(unsigned char value);
void shiftKolona(unsigned char value);
void setRed(unsigned char value);

/*
 * SHCP - shift
 * STCP - klok za ulaz
 * DS - ulaz
 */

#endif // _SYSTEM_H_
