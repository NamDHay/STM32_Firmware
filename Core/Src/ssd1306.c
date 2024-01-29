/*
 * ssd1306.c
 *
 *  Created on: Jan 27, 2024
 *      Author: namdhay
 */

#include "ssd1306.h"

void SSD1306_AssignedPin(SSD1306 *ssd1306, GPIO_TypeDef *port, uint16_t pin, pinName name){
	switch(name){
	case SSD1306_D0_PIN:
		ssd1306->pin.d0.port = port;
		ssd1306->pin.d0.pin = pin;
	break;
	case SSD1306_D1_PIN:
		ssd1306->pin.d1.port = port;
		ssd1306->pin.d1.pin = pin;
	break;
#if defined(SSD1306_SPI)
	case SSD1306_RES_PIN:
		ssd1306->pin.res.port = port;
		ssd1306->pin.res.pin = pin;
	break;
	case SSD1306_DC_PIN:
		ssd1306->pin.dc.port = port;
		ssd1306->pin.dc.pin = pin;
	break;
	case SSD1306_CS_PIN:
		ssd1306->pin.cs.port = port;
		ssd1306->pin.cs.pin = pin;
	break;
#endif
	}
}

void SSD1306_Write(SSD1306 *ssd1306, uint8_t data, size_t lengh, SSD1306Mode mode){
	if(mode == SSD1306_DATA){
		HAL_GPIO_WritePin(ssd1306->pin.dc.port, ssd1306->pin.dc.pin, 1);

		HAL_SPI_Transmit(&ssd1306->spi, &data, lengh, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(ssd1306->pin.cs.port, ssd1306->pin.cs.pin, 0);
		HAL_GPIO_WritePin(ssd1306->pin.cs.port, ssd1306->pin.cs.pin, 1);
	}else{
		HAL_GPIO_WritePin(ssd1306->pin.dc.port, ssd1306->pin.dc.pin, 0);

		HAL_SPI_Transmit(&ssd1306->spi, &data, 1, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(ssd1306->pin.cs.port, ssd1306->pin.cs.pin, 0);
		HAL_GPIO_WritePin(ssd1306->pin.cs.port, ssd1306->pin.cs.pin, 1);
	}
}
void SSD1306_Init(SSD1306 *ssd1306){
	SSD1306_Write(ssd1306, SSD1306_DISPLAYOFF, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x20, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x10, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xB0, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xC8, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x10, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x40, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x81, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xFF, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xA1, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xA6, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xA8, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x3F, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xA4, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xD3, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xD5, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xF0, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xD9, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x22, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xDA, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x12, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xDB, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x20, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x8D, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0x14, 1, SSD1306_COMMAND);
	SSD1306_Write(ssd1306, 0xAF, 1, SSD1306_COMMAND);
}
