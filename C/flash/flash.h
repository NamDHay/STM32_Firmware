/*
 * flash.h
 *
 *  Created on: Mar 15, 2024
 *      Author: namdhay
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define FLASH_BASE_ADDR		0X08000000
#define FLASH_TARGET_PAGE	64
#define FLASH_TARGET_ADDR	(FLASH_BASE_ADDR + FLASH_TARGET_PAGE * 1024)

#define VALID_FLASH_SPACE	20 		//bytes unit


typedef enum {
	FLASH_CHECK_FREESPACE,
	FLASH_WRITE,
	FLASH_CLONE,
	FLASH_UPDATE,
}FlashWriteProcedure;

HAL_StatusTypeDef flash_Erase(uint32_t addr);
HAL_StatusTypeDef flash_Write(uint32_t addr, uint16_t *data, size_t lengh);
HAL_StatusTypeDef flash_Read(uint32_t addr, uint16_t *data, size_t lengh);
HAL_StatusTypeDef flash_Write2(uint32_t addr, uint16_t *data, size_t lengh);
#endif /* INC_FLASH_H_ */
