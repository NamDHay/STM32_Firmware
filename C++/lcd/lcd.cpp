/*
 * lcd.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: NamDHay
 */

#include "lcd.h"

lcdPin lcdpin;
lcdCmd cmd;

void LCD::AssignPin(GPIO_TypeDef *port, uint16_t pin, pinName name){
	switch(name){
	case LCD_ENABLE_PIN:
		lcdpin.enable.port = port;
		lcdpin.enable.pin = pin;
		break;
	case LCD_RW_PIN:
		lcdpin.rw.port = port;
		lcdpin.rw.pin = pin;
		break;
	case LCD_RS_PIN:
		lcdpin.rs.port = port;
		lcdpin.rs.pin = pin;
		break;
	case LCD_DATA7_PIN:
		lcdpin.data7.port = port;
		lcdpin.data7.pin = pin;
		break;
	case LCD_DATA6_PIN:
		lcdpin.data6.port = port;
		lcdpin.data6.pin = pin;
		break;
	case LCD_DATA5_PIN:
		lcdpin.data5.port = port;
		lcdpin.data5.pin = pin;
		break;
	case LCD_DATA4_PIN:
		lcdpin.data4.port = port;
		lcdpin.data4.pin = pin;
		break;
	case LCD_DATA3_PIN:
		lcdpin.data3.port = port;
		lcdpin.data3.pin = pin;
		break;
	case LCD_DATA2_PIN:
		lcdpin.data2.port = port;
		lcdpin.data2.pin = pin;
		break;
	case LCD_DATA1_PIN:
		lcdpin.data1.port = port;
		lcdpin.data1.pin = pin;
		break;
	case LCD_DATA0_PIN:
		lcdpin.data0.port = port;
		lcdpin.data0.pin = pin;
		break;
	}
}

void LCD::mode8::Write(LCDmode mode, uint8_t data){
	if(mode == LCD_COMMAND){
		HAL_GPIO_WritePin(lcdpin.rs.port, lcdpin.rs.pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(lcdpin.rs.port, lcdpin.rs.pin, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(lcdpin.data0.port, lcdpin.data0.pin, data&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data1.port, lcdpin.data1.pin, data>>1&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data2.port, lcdpin.data2.pin, data>>2&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data3.port, lcdpin.data3.pin, data>>3&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data4.port, lcdpin.data4.pin, data>>4&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data5.port, lcdpin.data5.pin, data>>5&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data6.port, lcdpin.data6.pin, data>>6&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data7.port, lcdpin.data7.pin, data>>7&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_SET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);
}

void LCD::mode4::Write(LCDmode mode, uint8_t data){
	if(mode == LCD_COMMAND){
		HAL_GPIO_WritePin(lcdpin.rs.port, lcdpin.rs.pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(lcdpin.rs.port, lcdpin.rs.pin, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(lcdpin.data4.port, lcdpin.data4.pin, data>>4&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data5.port, lcdpin.data5.pin, data>>5&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data6.port, lcdpin.data6.pin, data>>6&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data7.port, lcdpin.data7.pin, data>>7&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_SET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);

	HAL_GPIO_WritePin(lcdpin.data4.port, lcdpin.data4.pin, data>>0&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data5.port, lcdpin.data5.pin, data>>1&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data6.port, lcdpin.data6.pin, data>>2&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcdpin.data7.port, lcdpin.data7.pin, data>>3&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_SET);
	LCD_Delay(1);
	HAL_GPIO_WritePin(lcdpin.enable.port, lcdpin.enable.pin, GPIO_PIN_RESET);
	LCD_Delay(1);
}

void LCD::mode8::Clear(){
	LCD::mode8::Write(LCD_COMMAND, LCD_CLEARDISPLAY);
}

void LCD::mode4::Clear(){
	LCD::mode4::Write(LCD_COMMAND, LCD_CLEARDISPLAY);
}

void LCD::mode8::Display(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_DISPLAY;
	else
		cmd.displayctrl &= ~(state<<LCD_DISPLAY);
	LCD::mode8::Write(LCD_COMMAND, cmd.displayctrl);
}

void LCD::mode4::Display(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_DISPLAY;
	else
		cmd.displayctrl &= ~(state<<LCD_DISPLAY);
	LCD::mode4::Write(LCD_COMMAND, cmd.displayctrl);
}

void LCD::mode8::Cursor(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_CURSOR;
	else
		cmd.displayctrl &= ~(state<<LCD_CURSOR);
	LCD::mode8::Write(LCD_COMMAND, cmd.displayctrl);
}

void LCD::mode4::Cursor(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_CURSOR;
	else
		cmd.displayctrl &= ~(state<<LCD_CURSOR);
	LCD::mode4::Write(LCD_COMMAND, cmd.displayctrl);
}

void LCD::mode8::Blink(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_BLINK;
	else
		cmd.displayctrl &= ~(state<<LCD_BLINK);
	LCD::mode8::Write(LCD_COMMAND, cmd.displayctrl);
}

void LCD::mode4::Blink(State state){
	if(state == ON)
		cmd.displayctrl |= state<<LCD_BLINK;
	else
		cmd.displayctrl &= ~(state<<LCD_BLINK);
	LCD::mode4::Write(LCD_COMMAND, cmd.displayctrl);
}

HAL_StatusTypeDef LCD::mode8::Gotoxy(uint8_t x, uint8_t y){
	uint8_t DRAM_ADDRESS = 0x00;
	uint8_t DRAM_OFFSET[4] = {0x00, 0x40, 0x14, 0x54};
	if(x >(cmd.column - 1)){
		return HAL_ERROR;
	}
	if(x >(cmd.row - 1)){
		return HAL_ERROR;
	}
	DRAM_ADDRESS = DRAM_OFFSET[y] + x;
	LCD::mode8::Write(LCD_COMMAND,LCD_SETDDRAMADDR|DRAM_ADDRESS);
	return HAL_OK;
}

HAL_StatusTypeDef LCD::mode4::Gotoxy(uint8_t x, uint8_t y){
	uint8_t DRAM_ADDRESS = 0x00;
	uint8_t DRAM_OFFSET[4] = {0x00, 0x40, 0x14, 0x54};
	if(x >(cmd.column - 1)){
		return HAL_ERROR;
	}
	if(x >(cmd.row - 1)){
		return HAL_ERROR;
	}
	DRAM_ADDRESS = DRAM_OFFSET[y] + x;
	LCD::mode4::Write(LCD_COMMAND,LCD_SETDDRAMADDR|DRAM_ADDRESS);
	return HAL_OK;
}

void LCD::mode8::ReturnHome(){
	LCD::mode8::Write(LCD_COMMAND, LCD_RETURNHOME);
}

void LCD::mode4::ReturnHome(){
	LCD::mode4::Write(LCD_COMMAND, LCD_RETURNHOME);
}

void LCD::mode8::WriteChar(uint8_t c){
	LCD::mode8::Write(LCD_DATA, c);
}

void LCD::mode4::WriteChar(char c){
	LCD::mode4::Write(LCD_DATA, c);
}

void LCD::mode8::WriteString(uint8_t* string){
	while(*string)	LCD::mode8::Write(LCD_DATA, *string++);
}

void LCD::mode4::WriteString(char* string){
	while(*string)	LCD::mode4::Write(LCD_DATA, *string++);
}

void LCD::mode8::Init(uint8_t column, uint8_t row){
	cmd.row = row;
	cmd.column = column;
	LCD_Delay(50);
	cmd.functionset = LCD_FUNCTIONSET|LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS;
	cmd.entrymode = LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;
	cmd.displayctrl = LCD_DISPLAYCONTROL|(1<<LCD_DISPLAY)|(0<<LCD_CURSOR)|(0<<LCD_BLINK);
	cmd.cursorshift = LCD_CURSORSHIFT|LCD_CURSORMOVE|LCD_MOVERIGHT;

	LCD::mode8::Write(LCD_COMMAND, cmd.entrymode);
	LCD::mode8::Write(LCD_COMMAND, cmd.displayctrl);
	LCD::mode8::Write(LCD_COMMAND, cmd.cursorshift);
	LCD::mode8::Write(LCD_COMMAND, cmd.functionset);

	LCD::mode8::Write(LCD_COMMAND, LCD_CLEARDISPLAY);
	LCD::mode8::Write(LCD_COMMAND, LCD_RETURNHOME);
}

void LCD::mode4::Init(uint8_t column, uint8_t row){
	cmd.row = row;
	cmd.column = column;
	cmd.functionset = LCD_FUNCTIONSET|LCD_4BITMODE|LCD_2LINE|LCD_5x8DOTS;
	cmd.entrymode = LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;
	cmd.displayctrl = LCD_DISPLAYCONTROL|(1<<LCD_DISPLAY)|(0<<LCD_CURSOR)|(0<<LCD_BLINK);
	cmd.cursorshift = LCD_CURSORSHIFT|LCD_CURSORMOVE|LCD_MOVERIGHT;

	LCD_Delay(50);
	LCD::mode4::Write(LCD_COMMAND, 0x33);
	LCD_Delay(5);
	LCD::mode4::Write(LCD_COMMAND, 0x33);
	LCD_Delay(5);
	LCD::mode4::Write(LCD_COMMAND, 0x32);
	LCD_Delay(5);


	LCD::mode4::Write(LCD_COMMAND, cmd.entrymode);
	LCD::mode4::Write(LCD_COMMAND, cmd.displayctrl);
	LCD::mode4::Write(LCD_COMMAND, cmd.cursorshift);
	LCD::mode4::Write(LCD_COMMAND, cmd.functionset);

	LCD::mode4::Write(LCD_COMMAND, LCD_CLEARDISPLAY);
	LCD::mode4::Write(LCD_COMMAND, LCD_RETURNHOME);
}
