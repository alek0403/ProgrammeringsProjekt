#ifndef _ANSI_H_
#define _ANSI_H_
/* Includes -------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <Lut1.h>
/* Exported types -------------------------------------------------------*/
/* Exported constants ---------------------------------------------------*/
/* Exported macro -------------------------------------------------------*/
//#define
/* Exported functions -------------------------------------------------- */
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void tegn();
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char *str, uint8_t type);
void printFix(int32_t i);
int32_t expand(int32_t i);
int32_t SINUS(int32_t a);
int32_t COSINUS(int32_t a);
void window2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t type);
#endif /* _ANSI_H_ */
