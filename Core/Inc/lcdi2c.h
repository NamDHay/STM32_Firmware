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

#define LCD_Delay(time)	HAL_Delay(time)

class LCD{
private:
	typedef struct{
		I2C_HandleTypeDef* i2c;
		uint8_t row;
		uint8_t column;
		uint8_t addr;
		uint8_t entrymode;
		uint8_t displayctrl;
		uint8_t cursorshift;
		uint8_t functionset;
		uint8_t backlight;
	}LCD_I2C;
	LCD_I2C lcd;
public:
	void Init(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t column, uint8_t row);
};

#endif /* INC_LCDI2C_H_ */
