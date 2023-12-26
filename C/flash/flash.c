/*
 * flash.c
 *
 *  Created on: Sep 29, 2023
 *      Author: NamDHay
 */

#include "flash.h"
#include "main.h"

SFlash_State_type sflashprocc;
flashPIDParam clone;

SFlash_StatusTypeDef Flash_Format(uint32_t addr)
{
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef fe;
	fe.TypeErase = FLASH_TYPEERASE_PAGES;
	fe.PageAddress = addr;
	fe.NbPages = 1;
	fe.Banks = FLASH_BANK_1;
	uint32_t pageErr = 0;
	if(HAL_FLASHEx_Erase(&fe, &pageErr) == HAL_OK){
		HAL_FLASH_Lock();
		return SFLASH_OK;
	}
	HAL_FLASH_Lock();
	return SFLASH_ERROR;
}

SFlash_StatusTypeDef Flash_Write(uint32_t address, void *data, size_t sizeofDataType){

	static uint8_t lengh = 0;
	static bool IsBusy = false;
	static uint32_t addrW = 0;
	uint16_t *dta = NULL;
	static uint16_t *pdta = NULL;
	if(IsBusy)	return SFLASH_BUSY;
	if(!address)	return SFLASH_ERROR;
	if(!lengh && !addrW){
		lengh = sizeofDataType;
		addrW = address;
	}
	if(!pdta){
		dta = (uint16_t*)data;
	}else
		dta = pdta;
	HAL_FLASH_Unlock();
	IsBusy = true;
	if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addrW, *dta) == HAL_OK){
		IsBusy = false;
		lengh -= 2;
		addrW += 2;
		dta++;
		pdta = dta;
	}
	if(lengh >= 1 && lengh <= sizeofDataType){
		HAL_FLASH_Lock();
		return SFLASH_BUSY;
	}else{
		lengh = 0;
		addrW = 0;
		pdta = NULL;
		HAL_FLASH_Lock();
		return SFLASH_OK;
	}
	return SFLASH_BUSY;
}

SFlash_StatusTypeDef Flash_Read(uint32_t address, void *data, size_t sizeOfDataType){
	static uint8_t lengh = 0;
	static uint32_t addrR = 0;
	uint16_t *dta = NULL;
	static uint16_t *pdta = NULL;
	if(!address)	return SFLASH_ERROR;
	if(!lengh && !addrR){
		lengh = sizeOfDataType;
		addrR = address;
	}
	if(!pdta){
		dta = (uint16_t*)data;
	}else
		dta = pdta;
	*dta = *(__IO uint16_t*) addrR;
	lengh -= 2;
	addrR += 2;
	dta++;
	pdta = dta;
	if(lengh > 0 && lengh <= sizeOfDataType){
		return SFLASH_BUSY;
	}else{
		lengh = 0;
		addrR = 0;
		pdta = NULL;
		return SFLASH_OK;
	}
}

SFlash_StatusTypeDef Flash_Update(uint32_t address, void *data, size_t sizeOfDataType){
	static uint16_t startmodify = 0;
	static uint8_t clonelengh = 0;

	if(address < FLASH_ADDR_BASE)	return SFLASH_ERROR;
	if(!startmodify) startmodify = address - FLASH_ADDR_BASE;
	if(!clonelengh){
		clonelengh = sizeOfDataType;
	}

	switch(sflashprocc){
	case STATE_PAGE_CLONE:
		while(Flash_Read(FLASH_ADDR_BASE, &clone, sizeof(flashPIDParam)) != SFLASH_OK);
		sflashprocc = STATE_PAGE_MODIFY;
		break;
	case STATE_PAGE_MODIFY:

		memcpy(((uint8_t *)&clone+startmodify),(uint8_t *)data,clonelengh);
		sflashprocc = STATE_PAGE_ERASED;

		break;
	case STATE_PAGE_ERASED:
		Flash_Format(FLASH_ADDR_BASE);
		sflashprocc = STATE_PAGE_WRITE;
		break;
	case STATE_PAGE_WRITE:
		while(Flash_Write(FLASH_ADDR_BASE, &clone, sizeof(flashPIDParam))!= SFLASH_OK);
		sflashprocc = STATE_PAGE_CLONE;
		return SFLASH_OK;
		break;
	}
	return SFLASH_BUSY;
}

//SFlash_StatusTypeDef Flash_Update_All(uint32_t address, void *data, size_t sizeOfDataType){
//	static uint16_t startmodify = 0;
//	static uint8_t clonelengh = 0;
//	uint16_t *cpy = NULL;
//
//	if(address < FLASH_ADDR_BASE)	return SFLASH_ERROR;
//	if(!startmodify) startmodify = address - FLASH_ADDR_BASE;
//	if(!clonelengh){
//		clonelengh = sizeOfDataType;
//	}
//
//	switch(sflashprocc){
//		case STATE_PAGE_CLONE:
//			while(Flash_Read(FLASH_ADDR_BASE, &clone, sizeof(flashPIDParam)) != SFLASH_OK);
//			sflashprocc = STATE_PAGE_MODIFY;
//			break;
//		case STATE_PAGE_MODIFY:
//
//			memcpy(((uint8_t *)&clone+startmodify),(uint8_t *)data,clonelengh);
//			sflashprocc = STATE_PAGE_ERASED;
//
//			break;
//		case STATE_PAGE_ERASED:
//			Flash_Format(FLASH_ADDR_BASE);
//			sflashprocc = STATE_PAGE_WRITE;
//			break;
//		case STATE_PAGE_WRITE:
//			while(Flash_Write(FLASH_ADDR_BASE, &clone, sizeof(flashPIDParam))!= SFLASH_OK);
//			sflashprocc = STATE_PAGE_CLONE;
//			return SFLASH_OK;
//			break;
//		}
//	return SFLASH_BUSY;
//}
