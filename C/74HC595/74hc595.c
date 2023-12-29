/*
 * 74hc595.c
 *
 *  Created on: Dec 28, 2023
 *      Author: NamDHay
 */
#include "74hc595.h"

void HC595_AssignPin(HC595PIN *hc595, GPIO_TypeDef *port, uint16_t pin, pinName name){
    switch(name){
        case HC595_DS:
        dsport = port;
        dspin = pin;
        break;
        case HC595_CLK:
        clkport = port;
        clkpin = pin;
        break;
        case HC595_LATCH:
        latchport = port;
        latchpin = pin;
        break;
        case HC595_OE:
        oeport = port;
        oepin = pin;
        break;
    }
    
}
