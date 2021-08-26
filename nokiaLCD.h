/*
 * nokiaLCD.h
 *
 *  Created on: Aug 10, 2021
 *      Author: edgardo
 */

#ifndef NOKIALCD_H_
#define NOKIALCD_H_

#include "stdint.h"
#include "MK64F12.h"

#define NOKIA_LCD_RESET_PORT PORTC
#define NOKIA_LCD_RESET_GPIO GPIOC
#define NOKIA_LCD_RESET_PIN 4

#define NOKIA_LCD_DC_PORT PORTC
#define NOKIA_LCD_DC_GPIO GPIOC
#define NOKIA_LCD_DC_PIN 3

#define NOKIA_LCD_SCE_PORT PORTD
#define NOKIA_LCD_SCE_GPIO GPIOD
#define NOKIA_LCD_SCE_PIN 0

#define NOKIA_LCD_SDIN_PORT PORTD
#define NOKIA_LCD_SDIN_GPIO GPIOD
#define NOKIA_LCD_SDIN_PIN 2

#define NOKIA_LCD_SCLK_PORT PORTD
#define NOKIA_LCD_SCLK_GPIO GPIOD
#define NOKIA_LCD_SCLK_PIN 1

#define NOKIA_LCD_BL_PORT PORTC
#define NOKIA_LCD_BL_GPIO GPIOC
#define NOKIA_LCD_BL_PIN 12

#define NOKIA_LCD_X 84
#define NOKIA_LCD_Y 48

#define NOKIA_LCD_COMMAND 0
#define NOKIA_LCD_DATA 1

#define NOKIA_LCD_CMD_HORADDRS 0x00
#define NOKIA_LCD_CMD_VERADDRS 0x02


void nokiaLCD_backlight(uint8_t onoff);

void nokiaLCD_write(uint8_t dc, uint8_t data);

void nokiaLCD_initialise(void);

void nokiaLCD_updateDisplay (void);

void nokiaLCD_clearDisplay (uint8_t bw);

void nokiaLCD_setChar(char character, int x, int y, uint8_t bw);

void nokiaLCD_setStr(char * dString, int x, int y, uint8_t bw);

void nokiaLCD_invertDisplay(void);

void nokiaLCD_setLine(int x0, int y0, int x1, int y1, uint8_t bw);

void nokiaLCD_setRect(int x0, int y0, int x1, int y1, uint8_t fill, uint8_t bw);

void nokiaLCD_setCircle (int x0, int y0, int radius, uint8_t bw, int lineThickness);

void nokiaLCD_setBitmap(const char * bitArray);

#endif /* NOKIALCD_H_ */
