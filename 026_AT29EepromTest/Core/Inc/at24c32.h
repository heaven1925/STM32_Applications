/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    at24c32.h
  * @author	 Atakan ERTEKiN , atakanertekinn@gmail.com
  * @version V1.0.0
  * @date	 30.11.2022
  * @rev     V1.0.0
  * @brief	 AT24C32 I2C EEPROM C Driver
********************************************************************************/
/************************************DEFINES***********************************/

#ifndef INC_AT24C32_H_
#define INC_AT24C32_H_

/************************************INCLUDES***********************************/



#include <stdint.h>
#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG_FLASH_PROCESS
extern UART_HandleTypeDef 	huart1;
#endif

/* Device addr 1010 A2 A1 A0 R/w */
/*			   1010 0 0 0 1 = A1  -> Read  */
/*			   1010 0 0 0 1 = A0  -> Write */
#define 	I2C_WRITE_ADDR  0xA0
#define		I2C_READ_ADDR	0xA1

uint8_t readEEPROM			(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres);
void 	writeEEPROM			(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t value);
void 	writeEEPROMString	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t *value);
void 	readEEPROMString	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]);
void 	eraseEEPROM			(I2C_HandleTypeDef *i2cbus, uint8_t devAdres);
void 	fillEEPROM			(I2C_HandleTypeDef *i2cbus, uint8_t devAdres);
void 	readAllEEPROM		(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]);

typedef struct
{
	uint8_t (* readEEPROM		)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres);
	void 	(* writeEEPROM		)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t value);
	void 	(* writeEEPROMString)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t *value);
	void 	(* readEEPROMString	)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]);
	void 	(* eraseEEPROM		)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres);
	void 	(* fillEEPROM		)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres);
	void 	(* readAllEEPROM	)	(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]);

}AT24C32_st;

extern const AT24C32_st AT24C32;
extern HAL_StatusTypeDef 	ret;

#endif /* INC_AT24C32_H_ */
