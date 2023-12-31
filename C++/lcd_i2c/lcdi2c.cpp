/*
 * lcdi2c.cpp
 *
 *  Created on: Dec 30, 2023
 *      Author: NamDHays
 */

#include "lcdi2c.h"
void LCD::Write(uint8_t data, LCDmode mode){
	char data_H;
	char data_L;
	uint8_t data_i2c[4];
	data_H = data&0xF0;
	data_L = (data<<4)&0xF0;
	if(lcd.cmd.backlight){
		data_H |= LCD_BACKLIGHT;
		data_L |= LCD_BACKLIGHT;
	}
	if(mode == LCD_COMMAND){
		data_H |= LCD_RS;
		data_L |= LCD_RS;
	}
	if(mode == LCD_DATA){
		data_H &= ~LCD_RS;
		data_L &= ~LCD_RS;
	}
	data_i2c[0] = data_H|LCD_EN;
	LCD_Delay(1);
	data_i2c[1] = data_H;
	data_i2c[2] = data_L|LCD_EN;
	LCD_Delay(1);
	data_i2c[3] = data_L;
	HAL_I2C_Master_Transmit(lcd.i2c, lcd.addr, (uint8_t*)data_i2c, sizeof(data_i2c), 1000);
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

	LCD_Delay(50);
	LCD::Write(0x33, LCD_COMMAND);
	LCD::Write(0x33, LCD_COMMAND);
	LCD_Delay(5);
	LCD::Write(0x32, LCD_COMMAND);
	LCD_Delay(5);
	LCD::Write(0x20, LCD_COMMAND);
	LCD_Delay(5);

	LCD::Write(lcd.cmd.entrymode, LCD_COMMAND);
	LCD::Write(lcd.cmd.displayctrl, LCD_COMMAND);
	LCD::Write(lcd.cmd.cursorshift, LCD_COMMAND);
	LCD::Write(lcd.cmd.functionset, LCD_COMMAND);

	LCD::Write(LCD_CLEARDISPLAY, LCD_COMMAND);
	LCD::Write(LCD_RETURNHOME, LCD_COMMAND);
}

void LCD::Gotoxy(uint8_t x, uint8_t y){
	uint8_t DRAM_ADDR = 0x00;

}
