/*
 * ssd1306.c
 *
 *  Created on: Jan 27, 2024
 *      Author: namdhay
 */

#include "ssd1306.h"

extern SSD1306 ssd1306;
static char SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

void SSD1306_AssignedPin(GPIO_TypeDef *port, uint16_t pin, pinName name){
	switch(name){
	case SSD1306_D0_PIN:
		ssd1306.pin.d0.port = port;
		ssd1306.pin.d0.pin = pin;
	break;
	case SSD1306_D1_PIN:
		ssd1306.pin.d1.port = port;
		ssd1306.pin.d1.pin = pin;
	break;
#if defined(SSD1306_SPI)
	case SSD1306_RES_PIN:
		ssd1306.pin.res.port = port;
		ssd1306.pin.res.pin = pin;
	break;
	case SSD1306_DC_PIN:
		ssd1306.pin.dc.port = port;
		ssd1306.pin.dc.pin = pin;
	break;
	case SSD1306_CS_PIN:
		ssd1306.pin.cs.port = port;
		ssd1306.pin.cs.pin = pin;
	break;
#endif
	}
}

void SSD1306_Write(uint8_t data, size_t lengh, SSD1306Mode mode){
	if(mode == SSD1306_DATA){
		HAL_GPIO_WritePin(ssd1306.pin.dc.port, ssd1306.pin.dc.pin, 1);

		HAL_SPI_Transmit(&ssd1306.spi, &data, lengh, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(ssd1306.pin.cs.port, ssd1306.pin.cs.pin, 0);
		HAL_GPIO_WritePin(ssd1306.pin.cs.port, ssd1306.pin.cs.pin, 1);
	}else{
		HAL_GPIO_WritePin(ssd1306.pin.dc.port, ssd1306.pin.dc.pin, 0);

		HAL_SPI_Transmit(&ssd1306.spi, &data, 1, HAL_MAX_DELAY);

		HAL_GPIO_WritePin(ssd1306.pin.cs.port, ssd1306.pin.cs.pin, 0);
		HAL_GPIO_WritePin(ssd1306.pin.cs.port, ssd1306.pin.cs.pin, 1);
	}
}

void SSD1306_Init(){
	SSD1306_Write(SSD1306_DISPLAYOFF, 1, SSD1306_COMMAND);
	SSD1306_Write(0x20, 1, SSD1306_COMMAND);
	SSD1306_Write(0x10, 1, SSD1306_COMMAND);
	SSD1306_Write(0xB0, 1, SSD1306_COMMAND);
	SSD1306_Write(0xC8, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(0x10, 1, SSD1306_COMMAND);
	SSD1306_Write(0x40, 1, SSD1306_COMMAND);
	SSD1306_Write(0x81, 1, SSD1306_COMMAND);
	SSD1306_Write(0xFF, 1, SSD1306_COMMAND);
	SSD1306_Write(0xA1, 1, SSD1306_COMMAND);
	SSD1306_Write(0xA6, 1, SSD1306_COMMAND);
	SSD1306_Write(0xA8, 1, SSD1306_COMMAND);
	SSD1306_Write(0x3F, 1, SSD1306_COMMAND);
	SSD1306_Write(0xA4, 1, SSD1306_COMMAND);
	SSD1306_Write(0xD3, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(0xD5, 1, SSD1306_COMMAND);
	SSD1306_Write(0xF0, 1, SSD1306_COMMAND);
	SSD1306_Write(0xD9, 1, SSD1306_COMMAND);
	SSD1306_Write(0x22, 1, SSD1306_COMMAND);
	SSD1306_Write(0xDA, 1, SSD1306_COMMAND);
	SSD1306_Write(0x12, 1, SSD1306_COMMAND);
	SSD1306_Write(0xDB, 1, SSD1306_COMMAND);
	SSD1306_Write(0x20, 1, SSD1306_COMMAND);
	SSD1306_Write(0x8D, 1, SSD1306_COMMAND);
	SSD1306_Write(0x14, 1, SSD1306_COMMAND);
	SSD1306_Write(0xAF, 1, SSD1306_COMMAND);

//	SSD1306_Write(SSD1306_DEACTIVATE_SCROLL, 1, SSD1306_COMMAND);

//	ssd1306.row = 0;
//	ssd1306.column = 0;
}

void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row){
	SSD1306_Write(SSD1306_RIGHT_HORIZONTAL_SCROLL, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(start_row, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(end_row, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(0xFF, 1, SSD1306_COMMAND);
	SSD1306_Write(SSD1306_ACTIVATE_SCROLL, 1, SSD1306_COMMAND);
}

void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row){
	SSD1306_Write(SSD1306_LEFT_HORIZONTAL_SCROLL, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(start_row, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(end_row, 1, SSD1306_COMMAND);
	SSD1306_Write(0x00, 1, SSD1306_COMMAND);
	SSD1306_Write(0xFF, 1, SSD1306_COMMAND);
	SSD1306_Write(SSD1306_ACTIVATE_SCROLL, 1, SSD1306_COMMAND);
}

void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row)
{
  SSD1306_Write(SSD1306_SET_VERTICAL_SCROLL_AREA, 1, SSD1306_COMMAND);  // sect the area
  SSD1306_Write(0x00, 1, SSD1306_COMMAND);   // write dummy
  SSD1306_Write(SSD1306_HEIGHT, 1, SSD1306_COMMAND);

  SSD1306_Write(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL, 1, SSD1306_COMMAND);
  SSD1306_Write(0x00, 1, SSD1306_COMMAND);
  SSD1306_Write(start_row, 1, SSD1306_COMMAND);
  SSD1306_Write(0X00, 1, SSD1306_COMMAND);
  SSD1306_Write(end_row, 1, SSD1306_COMMAND);
  SSD1306_Write(0x01, 1, SSD1306_COMMAND);
  SSD1306_Write(SSD1306_ACTIVATE_SCROLL, 1, SSD1306_COMMAND);
}

void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_Write(SSD1306_SET_VERTICAL_SCROLL_AREA, 1, SSD1306_COMMAND);  // sect the area
  SSD1306_Write(0x00, 1, SSD1306_COMMAND);   // write dummy
  SSD1306_Write(SSD1306_HEIGHT, 1, SSD1306_COMMAND);

  SSD1306_Write(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL, 1, SSD1306_COMMAND);
  SSD1306_Write(0x00, 1, SSD1306_COMMAND);
  SSD1306_Write(start_row, 1, SSD1306_COMMAND);
  SSD1306_Write(0X00, 1, SSD1306_COMMAND);
  SSD1306_Write(end_row, 1, SSD1306_COMMAND);
  SSD1306_Write(0x01, 1, SSD1306_COMMAND);
  SSD1306_Write(SSD1306_ACTIVATE_SCROLL, 1, SSD1306_COMMAND);
}

void SSD1306_Stopscroll(){
	SSD1306_Write(SSD1306_DEACTIVATE_SCROLL, 1, SSD1306_COMMAND);
}

void SSD1306_InvertDisplay(bool i){
  if (i) SSD1306_Write(SSD1306_INVERTDISPLAY, 1, SSD1306_COMMAND);

  else SSD1306_Write(SSD1306_NORMALDISPLAY, 1, SSD1306_COMMAND);

}

void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color){
	int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
	uint8_t byte = 0;

	for(int16_t j=0; j<h; j++, y++)
	{
		for(int16_t i=0; i<w; i++)
		{
			if(i & 7)
			{
			   byte <<= 1;
			}
			else
			{
			   byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
			}
			if(byte & 0x80) SSD1306_DrawPixel(x+i, y, color);
		}
	}
}

void SSD1306_UpdateScreen(void) {
	uint8_t m;

	for (m = 0; m < 8; m++) {
		SSD1306_Write(0xB0 + m, 1, SSD1306_COMMAND);
		SSD1306_Write(0x00, 1, SSD1306_COMMAND);
		SSD1306_Write(0x10, 1, SSD1306_COMMAND);

		/* Write multi data */

		SSD1306_Write(SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH, SSD1306_DATA);
	}
}

void SSD1306_ToggleInvert(void) {
	uint16_t i;

	/* Toggle invert */
	ssd1306.Inverted = !ssd1306.Inverted;

	/* Do memory toggle */
	for (i = 0; i < sizeof(SSD1306_Buffer); i++) {
		SSD1306_Buffer[i] = ~SSD1306_Buffer[i];
	}
}

void SSD1306_Fill(SSD1306_COLOR_t color) {
	/* Set memory */
	memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		/* Error */
		return;
	}

	/* Check if pixels are inverted */
	if (ssd1306.Inverted) {
		color = (SSD1306_COLOR_t)!color;
	}

	/* Set color */
	if (color == SSD1306_COLOR_WHITE) {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}
