/*
 * 74hc595.cpp
 *
 *  Created on: Dec 29, 2023
 *      Author: NamDHay
 */

#include "74hc595.h"

void HC595::AssignPin(GPIO_TypeDef *port, uint16_t pin, pinName name){
    switch(name){
        case HC595_LATCH:
            hc595pin->ds.port = port;
            hc595pin->ds.pin = pin;
        break;
        case HC595_CLK:
            hc595pin->clk.port = port;
            hc595pin->clk.pin = pin;
        break;
        case HC595_DS:
            hc595pin->ds.port = port;
            hc595pin->ds.pin = pin;
        break;
        case HC595_OE:
            hc595pin->oe.port = port;
            hc595pin->oe.pin = pin;
        break;
    }
}

void HC595::ShiftOut(uint8_t n, ShiftType type){
    for(uint8_t i = 0; i<(8n); i++){
        if(type == LSB){
            if(data & 0x01)     HC595_WRITE(HC595_DS,1);
            else                 HC595_WRITE(HC595_DS,0);
            data = data >> 1;
        }else{
            if(!(data & 0x80000000UL))     HC595_WRITE(HC595_DS,0);
            else                 HC595_WRITE(HC595_DS,1);
            data = data << 1;
        }
        HC595_WRITE(HC595_CLK, 1);
        HC595_WRITE(HC595_CLK, 0);
    }
    HC595_WRITE(HC595_LATCH,1);
    HC595_WRITE(HC595_LATCH,0);
}

void HC595::SetBit(uint8_t bit, uint8_t n){
    if(bit > (8*n-1)) return;
    data = data | (1UL<<bit);
}

void HC595::ClearBit(uint8_t bit, uint8_t n){
    if(bit > (8*n-1)) return;
    data = data & ~(1UL<<bit);
}