/*
 * ee.h
 *
 *  Created on: Nov 30, 2023
 *      Author: NamDHay
 */

#ifndef INC_EE_H_
#define INC_EE_H_

#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#define FLASH_ADDR_BASE		(0x08000000+1024*64)
#define FLASH_ADDR_PAGE1	(0x08000000+1024*64)
#define FLASH_ADDR_PAGE2	(0x08000000+1024*63)

typedef enum SFlash_StatusTypeDef{
	SFLASH_OK,
	SFLASH_BUSY,
	SFLASH_ERROR,
	SFLASH_FULL,
	SFLASH_VALID,
}SFlash_StatusTypeDef;

typedef enum SFlash_State_type{
	STATE_PAGE_CLONE,
	STATE_PAGE_MODIFY,
	STATE_PAGE_ERASED,
	STATE_PAGE_WRITE,
}SFlash_State_type;

typedef struct flashPIDParam{
	float kp;
	float ki;
	float kb;
	float kd;
	float deltaT;
	float alpha;
	uint8_t ID;
}flashPIDParam;

class EE{
public:
	flashPIDParam clone;
	SFlash_State_type sflashprocc;

	SFlash_StatusTypeDef Format(uint32_t addr);
	SFlash_StatusTypeDef Write(uint32_t address, void *data, size_t sizeofDataType);
	SFlash_StatusTypeDef Read(uint32_t address, void *data, size_t sizeOfDataType);
	SFlash_StatusTypeDef Update(uint32_t address, void *data, size_t sizeOfDataType);
};

#endif /* INC_EE_H_ */
