/*
 * flash.h
 *
 *  Created on: Sep 29, 2023
 *      Author: NamDHay
 */

#ifndef INC_FLASH_SAVE_H_
#define INC_FLASH_SAVE_H_

#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#define FLASH_ADDR_BASE		(0x08000000+1024*64)
#define FLASH_ADDR_PAGE1	(0x08000000+1024*64)
#define FLASH_ADDR_PAGE2	(0x08000000+1024*63)

typedef struct flashPIDParam{
	uint8_t ID;
	float kp;
	float ki;
	float kd;
	float deltaT;
	float alpha;
}flashPIDParam;

typedef enum SFlash_State_type{
	STATE_PAGE_CLONE,
	STATE_PAGE_MODIFY,
	STATE_PAGE_ERASED,
	STATE_PAGE_WRITE,
}SFlash_State_type;

typedef enum SFlash_StatusTypeDef{
	SFLASH_OK,
	SFLASH_BUSY,
	SFLASH_ERROR,
	SFLASH_FULL,
	SFLASH_VALID,
}SFlash_StatusTypeDef;

SFlash_StatusTypeDef Flash_Format(uint32_t addr);
SFlash_StatusTypeDef Flash_Write(uint32_t address, void *data, size_t sizeofDataType);
SFlash_StatusTypeDef Flash_Read(uint32_t address, void *data, size_t sizeOfDataType);
SFlash_StatusTypeDef Flash_Update(uint32_t address, void *data, size_t sizeOfDataType);
#endif /* INC_FLASH_SAVE_H_ */
