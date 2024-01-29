/*
 * ssd1306.h
 *
 *  Created on: Jan 27, 2024
 *      Author: namdhay
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include "main.h"
#include "stdint.h"

#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64

#define SSD1306_DISPLAYOFF	0xAE
#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range

#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7

typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

typedef enum{
	SSD1306_DATA,
	SSD1306_COMMAND
}SSD1306Mode;

typedef	struct{
	GPIO_TypeDef *port;
	uint16_t pin;
}pinConfig;

typedef enum{
	SSD1306_D0_PIN,
	SSD1306_D1_PIN,
#if defined(SSD1306_SPI)
	SSD1306_RES_PIN,
	SSD1306_DC_PIN,
	SSD1306_CS_PIN,
#endif
}pinName;

typedef struct{
	pinConfig d0;
	pinConfig d1;
#if defined(SSD1306_SPI)
	pinConfig res;
	pinConfig dc;
	pinConfig cs;
#endif
}SSD1306Pin;

typedef struct{

}SSD1306Cmd;

typedef struct{
	uint8_t row;
	uint8_t column;
	SSD1306Pin pin;
	SSD1306Cmd cmd;
//	I2C_HandleTypeDef i2c;
#if defined(SSD1306_SPI)
	SPI_HandleTypeDef spi;
#endif
}SSD1306;

void SSD1306_AssignedPin(SSD1306 *ssd1306, GPIO_TypeDef *port, uint16_t pin, pinName name);
void SSD1306_Write(SSD1306 *ssd1306, uint8_t data, size_t lengh, SSD1306Mode mode);
void SSD1306_Init(SSD1306 *ssd1306);
void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);
void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);

#endif /* INC_SSD1306_H_ */
