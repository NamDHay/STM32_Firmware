/*
 * flash.c
 *
 *  Created on: Mar 15, 2024
 *      Author: namdhay
 */

#include "flash.h"

FlashWriteProcedure writeprocedure;

// Temporary flash parameter
typedef struct FlashTemp_t {
	uint32_t addr;
	uint16_t *data;
	uint8_t lengh;
}FlashTemp_t;

HAL_StatusTypeDef flash_Erase(uint32_t addr) {
	//Check for valid input parameter
	if(!addr)	return HAL_ERROR;

	//Unlock flash
	HAL_FLASH_Unlock();

	//Init erase flash parameter
	FLASH_EraseInitTypeDef err;
	err.Banks = 1;
	err.NbPages = 1;
	err.PageAddress = addr;
	err.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t fe;

	//Erase flash
	HAL_FLASHEx_Erase(&err, &fe);

	//Lock flash
	HAL_FLASH_Lock();
	return HAL_OK;
}


HAL_StatusTypeDef flash_Write(uint32_t addr, uint16_t *data, size_t lengh) {
	//Check for valid input parameter
	if(!data || !lengh || !addr)	return HAL_ERROR;

	HAL_FLASH_Unlock();

	static FlashTemp_t wtemp;

	if(!wtemp.addr || !wtemp.lengh || !wtemp.data) {
		wtemp.addr = addr;
		wtemp.lengh = lengh;
		wtemp.data = data;
	}

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, wtemp.addr, (uint64_t)*wtemp.data);
	wtemp.addr += 2;
	wtemp.lengh -= 2;
	wtemp.data++;

	if(wtemp.lengh > 0 && wtemp.lengh <= lengh) {
		HAL_FLASH_Lock();
	}else {
		wtemp.data = NULL;
		wtemp.addr = 0;
		wtemp.lengh = 0;
		HAL_FLASH_Lock();
		return HAL_OK;
	}

	return HAL_BUSY;
}

HAL_StatusTypeDef flash_Read(uint32_t addr, uint16_t *data, size_t lengh) {
	//Check for valid input parameter
	if(!data || !lengh || !addr)	return HAL_ERROR;

	static FlashTemp_t rtemp;

	if(!rtemp.addr || !rtemp.lengh || !rtemp.data) {
		rtemp.addr = addr;
		rtemp.lengh = lengh;
		rtemp.data = data;
	}

	*rtemp.data = *(__IO uint16_t  *)(rtemp.addr);

	rtemp.addr += 2;
	rtemp.lengh -= 2;
	rtemp.data++;

	if(rtemp.lengh > 0 && rtemp.lengh <= lengh) {
		__NOP();
	}else {
		rtemp.data = NULL;
		rtemp.addr = 0;
		rtemp.lengh = 0;
		return HAL_OK;
	}

	return HAL_BUSY;
}

static HAL_StatusTypeDef flash_check_freespace(uint32_t addr, size_t lengh) {
	//Check for valid input parameter
	if(!lengh || !addr)	return HAL_ERROR;

	static FlashTemp_t ctemp;

	if(!ctemp.addr || !ctemp.lengh) {
		ctemp.addr = addr;
		ctemp.lengh = lengh;
	}

	if(*(__IO uint16_t  *)(ctemp.addr) != 0xFFFF) {
		return HAL_ERROR;
	}

	ctemp.addr += 2;
	ctemp.lengh -= 2;

	if(ctemp.lengh > 0 && ctemp.lengh <= lengh) {
		__NOP();
	}else {
		ctemp.addr = 0;
		ctemp.lengh = 0;
		return HAL_OK;
	}

	return HAL_BUSY;
}

HAL_StatusTypeDef flash_Write2(uint32_t addr, uint16_t *data, size_t lengh) {
	//Check for valid input parameter
	if(!data || !lengh || !addr)	return HAL_ERROR;

	static uint16_t *temp = NULL;

	switch(writeprocedure) {
	case FLASH_CHECK_FREESPACE:
		HAL_StatusTypeDef err = flash_check_freespace(addr, lengh);
		if(err == HAL_OK) {
			writeprocedure = FLASH_WRITE;
		}else if(err == HAL_ERROR) {
			writeprocedure = FLASH_CLONE;
			temp = calloc(VALID_FLASH_SPACE / 2,sizeof(uint16_t));
		}
		break;
	case FLASH_WRITE:
		if(flash_Write(addr, data, lengh) == HAL_OK){
			writeprocedure = FLASH_CHECK_FREESPACE;
			return HAL_OK;
		}
		break;
	case FLASH_CLONE:
		if(flash_Read(FLASH_TARGET_ADDR, temp, VALID_FLASH_SPACE) == HAL_OK) {
			flash_Erase(FLASH_TARGET_ADDR);
			writeprocedure = FLASH_UPDATE;
			return HAL_BUSY;
		}
		break;
	case FLASH_UPDATE:
		if(flash_Write(FLASH_TARGET_ADDR, temp, VALID_FLASH_SPACE) == HAL_OK) {
			free(temp);
			writeprocedure = FLASH_CHECK_FREESPACE;
			return HAL_OK;
		}
		break;
	}
	return HAL_BUSY;
}
