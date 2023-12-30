/*
 * lcdi2c.h
 *
 *  Created on: Dec 30, 2023
 *      Author: NamDHay
 */

#ifndef INC_LCDI2C_H_
#define INC_LCDI2C_H_

#include "main.h"
#include "string.h"

#define LCD_EN 							0x04  // Enable bit
#define LCD_RW 							0x02  // Read/Write bit
#define LCD_RS 							0x01  // Register select bit

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

#define LCD_BACKLIGHT 					0x08
#define LCD_NOBACKLIGHT 				0x00

#define LCD_Delay(time)	HAL_Delay(time)

typedef enum{
	LCD_COMMAND,
	LCD_DATA,
}LCDmode;

typedef enum{
	OFF,
	ON,
}State;

class LCD{
private:
	typedef struct{
		uint8_t entrymode;
		uint8_t displayctrl;
		uint8_t cursorshift;
		uint8_t functionset;
		uint8_t backlight;
	}LCDCmd;
	typedef struct{
		I2C_HandleTypeDef* i2c;
		uint8_t row;
		uint8_t column;
		uint8_t addr;
		LCDCmd cmd;
	}LCD_I2C;
	LCD_I2C lcd;
	void Write(uint8_t data, LCDmode mode);
public:
	void Init(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t column, uint8_t row);
};

#endif /* INC_LCDI2C_H_ */
