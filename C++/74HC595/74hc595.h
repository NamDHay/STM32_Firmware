/*
 * 74hc595.h
 *
 *  Created on: Dec 29, 2023
 *      Author: NamDHay
 */

#ifndef INC_74HC595_H_
#define INC_74HC595_H_

#include "main.h"
#include "stdbool.h"
#include "stdio.h"

#define HC595_Delay(time)   HAL_Delay(time)

#define HC595_WRITE(PIN, LOGIC) ((PIN == HC595_DS) ? HAL_GPIO_WritePin(latchport, latchpin, LOGIC)      :
                                ((PIN == HC595_CLK) ? HAL_GPIO_WritePin(clkport, clkpin, LOGIC))        :
                                ((PIN == HC595_LATCH) ? HAL_GPIO_WritePin(latchport, latchpin, LOGIC))  :
                                ((PIN == HC595_OE) ? HAL_GPIO_WritePin(oeport, oepin, LOGIC))           : 0)

class HC595{
private:
    typedef struct pinConfig{
	    GPIO_TypeDef *port;
	    uint16_t pin;
    }pinConfig;
    typedef enum{
	    HC595_LATCH,
	    HC595_CLK,
	    HC595_DS,
	    HC595_OE
    }pinName;
    typedef struct HC595{
	    pinConfig ds;
	    pinConfig clk;
	    pinConfig latch;
	    pinConfig oe;
	uint32_t data;
}HC595;
public:
    void HC595_AssignPin(GPIO_TypeDef *port, uint16_t pin, pinName name);
}


#endif /* INC_74HC595_H_ */