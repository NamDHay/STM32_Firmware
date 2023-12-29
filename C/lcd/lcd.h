/*
 * lcd.h
 *
 *  Created on: Dec 27, 2023
 *      Author: NamDHay
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#ifdef CONFIG_USE_LCD
#include "string.h"
#include "stdio.h"

#define LCD_CLEARDISPLAY 				0x01
#define LCD_RETURNHOME 					0x02

#define LCD_ENTRYMODESET 				0x04
#define LCD_DISPLAYCONTROL 				0x08
#define LCD_CURSORSHIFT 				0x10
#define LCD_FUNCTIONSET 				0x20
#define LCD_SETCGRAMADDR 				0x40
#define LCD_SETDDRAMADDR	 			0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 					0x00
#define LCD_ENTRYLEFT 					0x02
#define LCD_ENTRYSHIFTINCREMENT 		0x01
#define LCD_ENTRYSHIFTDECREMENT 		0x00

// bits for display on/off control
#define LCD_DISPLAY						2
#define LCD_CURSOR						1
#define LCD_BLINK 						0
// flags for display/cursor shift
#define LCD_DISPLAYMOVE 				0x08
#define LCD_CURSORMOVE 					0x00

#define LCD_MOVERIGHT 					0x04
#define LCD_MOVELEFT 					0x00

// flags for function set
#define LCD_8BITMODE 					0x10
#define LCD_4BITMODE 					0x00
#define LCD_2LINE 						0x08
#define LCD_1LINE 						0x00
#define LCD_5x10DOTS 					0x04
#define LCD_5x8DOTS 					0x00

#define LCD_Delay(time)	HAL_Delay(time)

typedef enum{
	LCD_COMMAND,
	LCD_DATA,
}LCDmode;

typedef enum{
	OFF,
	ON,
}State;

typedef enum{
	LCD_ENABLE_PIN,
	LCD_RS_PIN,
	LCD_RW_PIN,
	LCD_DATA7_PIN,
	LCD_DATA6_PIN,
	LCD_DATA5_PIN,
	LCD_DATA4_PIN,
	LCD_DATA3_PIN,
	LCD_DATA2_PIN,
	LCD_DATA1_PIN,
	LCD_DATA0_PIN,
}pinName;

typedef	struct{
	GPIO_TypeDef *port;
	uint16_t pin;
}pinConfig;

typedef struct{
	pinConfig enable;
	pinConfig rs;
	pinConfig rw;
	pinConfig data7;
	pinConfig data6;
	pinConfig data5;
	pinConfig data4;
	pinConfig data3;
	pinConfig data2;
	pinConfig data1;
	pinConfig data0;
}lcdPin;

typedef struct{
	uint8_t entrymode;
	uint8_t displayctrl;
	uint8_t cursorshift;
	uint8_t functionset;
}lcdCmd;

typedef struct{
    uint8_t row;
	uint8_t column;
    lcdPin lcdpin;
    lcdCmd cmd;
}LCD;

void LCD_AssignedPin(LCD *lcd, GPIO_TypeDef *port, uint16_t pin, pinName name);
void LCD_Write(LCD *lcd, LCDmode mode, uint8_t data);
void LCD_Init(LCD *lcd, uint8_t column, uint8_t row);
HAL_StatusTypeDef LCD_Gotoxy(uint8_t x, uint8_t y);
void LCD_WriteString(uint8_t* string);
void LCD_Clear();
void LCD_ReturnHome();
void LCD_Display(State state);
void LCD_Cursor(State state);
void LCD_Blink(State state);

#endif
#endif /* INC_LCD_H_ */