/*
 * lcdi2c.cpp
 *
 *  Created on: Dec 30, 2023
 *      Author: NamDHays
 */

#include "lcdi2c.h"

void LCD::Init(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t column, uint8_t row){
	lcd.i2c = hi2c;
	lcd.addr = address;
	lcd.row = row;
	lcd.column = column;
}
