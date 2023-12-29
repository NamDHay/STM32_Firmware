/*
 * 74hc595.h
 *
 *  Created on: Dec 28, 2023
 *      Author: NamDHay
 */

#ifndef INC_74HC595_H_
#define INC_74HC595_H_

#include "main.h"
#include "string.h"
#include "stdbool.h"

#define dspin                   hc595->ds.pin
#define dsport                  hc595->ds.port
#define clkpin                  hc595->clk.pin
#define clkport                 hc595->clk.port
#define latchpin                hc595->latch.pin
#define latchport               hc595->latch.port
#define oepin                   hc595->oe.pin
#define oeport                  hc595->oe.port

#define DELAY_MS(time)      (HAL_Delay(time))
#define HC595_WRITE(PIN, LOGIC) ((PIN == HC595_DS) ? HAL_GPIO_WritePin(latchport, latchpin, LOGIC)      :
                                ((PIN == HC595_CLK) ? HAL_GPIO_WritePin(clkport, clkpin, LOGIC))        :
                                ((PIN == HC595_LATCH) ? HAL_GPIO_WritePin(latchport, latchpin, LOGIC))  :
                                ((PIN == HC595_OE) ? HAL_GPIO_WritePin(oeport, oepin, LOGIC))           : 0)


typedef struct{
    GPIO_TypeDef *port;
    uint16_t pin;
}pinConfig;

typedef struct{
    pinConfig ds;
    pinConfig clk;
    pinConfig latch;
    pinConfig oe;
}HC595PIN;

typedef enum{
    HC595_DS,
    HC595_CLK,
    HC595_LATCH,
    HC595_OE,
}pinName;

void HC595_AssignPin(HC595PIN *hc595, GPIO_TypeDef *port, uint16_t pin, pinName name);
void HC595_ShiftOut()
#endif /* INC_74HC595_H_ */
