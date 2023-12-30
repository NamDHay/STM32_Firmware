/*
 * lcdi2c.cpp
 *
 *  Created on: Dec 30, 2023
 *      Author: NamDHays
 */

#include "lcdi2c.h"
void LCD::Write(uint8_t data, LCDmode mode){
	char Data_H;
	char Data_L;
	uint8_t Data_I2C[4];
	Data_H = data&0xF0;
	Data_L = (data<<4)&0xF0;
}
void LCD::Init(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t column, uint8_t row){
	lcd.i2c = hi2c;
	lcd.addr = address;
	lcd.row = row;
	lcd.column = column;

	lcd.cmd.functionset = LCD_FUNCTIONSET|LCD_4BITMODE|LCD_2LINE|LCD_5x8DOTS;
	lcd.cmd.entrymode = LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;
	lcd.cmd.displayctrl = LCD_DISPLAYCONTROL|(1<<LCD_DISPLAY)|(0<<LCD_CURSOR)|(0<<LCD_BLINK);
	lcd.cmd.cursorshift = LCD_CURSORSHIFT|LCD_CURSORMOVE|LCD_MOVERIGHT;
}
