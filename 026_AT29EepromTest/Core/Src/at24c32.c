/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    AT24C32.c
  * @author	 Atakan ERTEKiN , atakanertekinn@gmail.com
  * @version V1.0.0
  * @date	 30.11.2022
  * @rev     V1.0.0
  * @brief	 AT24C32 I2C EEPROM C Driver
  * The AT24C32/64 provides 32,768/65,536 bits of serial electrically erasable
  * and programmable read only memory (EEPROM) organized as 4096/8192 words of
  * 8 bits each. The device’s cascadable feature allows up to 8 devices to share
  * a common 2- wire bus.
  ----------------------------Device Operation-----------------------------------
  CLOCK and DATA TRANSITIONS:
  The SDA pin is normally pulled high with an external device.
  Data on the SDA pin may change only during SCL low time periods
  Data changes during SCL high periods will indicate a start
  or stop condition as defined below.

  START CONDITION:
  A high-to-low transition of SDA with SCL high is a start condition
  which must precede any other command

  STOP CONDITION: A low-to-high transition of SDA with SCL high is a stop condition.
  After a read sequence, the stop command will place the EEPROM in a standby power
  mode

  ACKNOWLEDGE:
  All addresses and data words are serially transmitted to and from the
  EEPROM in 8-bit words. The EEPROM sends a zero during the ninth clock cycle to
  acknowledge that it has received each word.

  STANDBY MODE:
  The AT24C32/64 features a low power standby mode which is
  enabled: a) upon power-up and b) after the receipt of the STOP bit and the completion
  of any internal operations.

  MEMORY RESET:
  After an interruption in protocol, power loss or system reset, any 2-
  wire part can be reset by following these steps:

  ------------------------------------------------------------------------------
  Device Address 	 1	 0	 1	 0	  A2	A1	 A0	  RW
					MSB								  LSB

********************************************************************************/
/************************************DEFINES***********************************/


/************************************INCLUDES***********************************/

#include "at24c32.h"

/**
 * Method pointer struct implementation
 */
const AT24C32_st AT24C32  = {
	readEEPROM		  ,
	writeEEPROM		  ,
	writeEEPROMString ,
	readEEPROMString  ,
	eraseEEPROM		  ,
	fillEEPROM		  ,
	readAllEEPROM	  ,
};


/*******************************************************************************
  @func    : readEEPROM
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres
  @return  : uint8_t
  @date	   : 8.12.2022
  @brief   : read Data Eeprom
********************************************************************************/
uint8_t readEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres)
{
	HAL_StatusTypeDef result = HAL_OK;

	uint8_t val[2] = { 0 };
	val[0] = (memAdres >> 8) & 0xFF;
	val[1] = (memAdres & 0xFF);

	result = HAL_I2C_Master_Transmit(i2cbus, devAdres, val, 2, HAL_MAX_DELAY);
	HAL_Delay(10);

#ifndef DEBUG_FLASH_PROCESS
	if(result != HAL_OK) return 0xFF;

	HAL_I2C_Master_Receive(i2cbus, devAdres, val, 1, HAL_MAX_DELAY);
	HAL_Delay(10);

	return val[0];

#else
	uint8_t buf2[50] = { 0 };
	if (result != HAL_OK)
	{
		strcpy((char*) buf2, "EEPROM Read Error I2C-TX\r\n");
	}
	else
	{
		result = HAL_I2C_Master_Receive(i2cbus, devAdres, val, 1, HAL_MAX_DELAY);
		HAL_Delay(10);

		if (result != HAL_OK)
		{
			strcpy((char*) buf2, "EEPROM Read Error I2C-RX\r\n");
		}

	}
	HAL_UART_Transmit(&huart1, buf2, strlen((char*) buf2), 1000);
	return val[0];
#endif
}

/*******************************************************************************
  @func    : writeEEPROM
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t value
  @return  : void
  @date	   : 8.12.2022
  @brief   : write data Eeprom
********************************************************************************/
void writeEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t value)
{

	HAL_StatusTypeDef result = HAL_OK;

	uint8_t val[3] = { 0 };
	val[0] = (memAdres >> 8) & 0xFF;
	val[1] = (memAdres & 0xFF);
	val[2] = value;

	result = HAL_I2C_Master_Transmit(i2cbus, devAdres, val, 3, 1000);
	HAL_Delay(10);

#ifndef DEBUG_FLASH_PROCESS
	if(result != HAL_OK) return;


#else
	uint8_t buf2[50] = { 0 };
	if (ret != HAL_OK) {
		strcpy((char*) buf2, "EEPROM Write Error I2C-TX\r\n");
	} else {
		strcpy((char*) buf2, "EEPROM Write Success I2C-TX\r\n");
	}
	HAL_UART_Transmit(&huart1, buf2, strlen((char*) buf2), 1000);
#endif
}

/*******************************************************************************
  @func    : writeEEPROMString
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t *value
  @return  : void
  @date	   : 8.12.22
  @brief   : Write String on EEprom
********************************************************************************/
void writeEEPROMString(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint8_t *value)
{
	int pos = 0;
	while (*value != '\0')
	{
		AT24C32.writeEEPROM(i2cbus, devAdres, memAdres + pos, *value++);
		pos++;
	}
}

/*******************************************************************************
  @func    : readEEPROMString
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]
  @return  : void
  @date	   : 8.12.2022
  @brief   : Read String from EEprom
********************************************************************************/
void readEEPROMString(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[])
{
	for (int i = 0; i < len; i++)
	{
		retValue[i] = AT24C32.readEEPROM(i2cbus, devAdres, memAdres + i);
	}
}

/*******************************************************************************
  @func    : eraseEEPROM
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres
  @return  : void
  @date	   : 8.12.22
  @brief   : Erase Eeprom
********************************************************************************/
void eraseEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres) {

	HAL_StatusTypeDef result = HAL_OK;

	for (uint16_t i = 0; i < 4096; i += 32)
	{
		uint8_t val2[34] = { 0 };
		val2[0] = ((i) >> 8) & 0xFF;
		val2[1] = ((i) & 0xFF);
		result = HAL_I2C_Master_Transmit(i2cbus, devAdres, val2, 34, 1000);
		HAL_Delay(10);
	}
#ifdef DEBUG_FLASH_PROCESS
	uint8_t buf2[50] = { 0 };
	if (ret != HAL_OK) {
		strcpy((char*) buf2, "ERASE EEPROM Error I2C-TX\r\n");
	} else {
		strcpy((char*) buf2, "ERASE EEPROM Success I2C-TX\r\n");
	}
	HAL_UART_Transmit(&huart1, buf2, strlen((char*) buf2), 1000);
#endif
}

/*******************************************************************************
  @func    : fillEEPROM
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres
  @return  : void
  @date	   : 8.12.22
  @brief   : fill all Eeprom data
********************************************************************************/
void fillEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres)
	{
	HAL_StatusTypeDef result = HAL_OK;

	uint8_t fc = 32;
	for (uint16_t memAdres = 0; memAdres < 4096; memAdres += 32) {
		uint8_t val2[34] = { 0 };
		val2[0] = (memAdres >> 8) & 0xFF;
		val2[1] = (memAdres & 0xFF);
		for (uint8_t j = 2; j <= 33; j++) {
			val2[j] = fc++;
			if (fc > 127) fc = 32;
		}
		result = HAL_I2C_Master_Transmit(i2cbus, devAdres, val2, 34, 1000);
		HAL_Delay(10);
	}
#ifdef DEBUG_FLASH_PROCESS
	uint8_t buf2[50] = { 0 };
	if (ret != HAL_OK) {
		strcpy((char*) buf2, "FILL EEPROM Error I2C-TX\r\n");
	} else {
		strcpy((char*) buf2, "FILL EEPROM Success I2C-TX\r\n");
	}
	HAL_UART_Transmit(&huart1, buf2, strlen((char*) buf2), 1000);
#endif
	}

/*******************************************************************************
  @func    : readAllEEPROM
  @param   : I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[]
  @return  : void
  @date	   : 8.12.22
  @brief   : Read all bytes from Eeprom
********************************************************************************/
void readAllEEPROM(I2C_HandleTypeDef *i2cbus, uint8_t devAdres, uint16_t memAdres, uint16_t len, uint8_t retValue[])
{
	HAL_StatusTypeDef result = HAL_OK;

	uint8_t val[2] = { 0 };
	val[0] = (memAdres >> 8) & 0xFF;
	val[1] = (memAdres & 0xFF);

	result = HAL_I2C_Master_Transmit(i2cbus, devAdres, val, 2, 1000);
	HAL_Delay(10);

#ifdef DEBUG_FLASH_PROCESS
	uint8_t buf2[50] = { 0 };

	if (ret != HAL_OK)
	{
		strcpy((char*) buf2, "EEPROM Read Error I2C-TX\r\n");
	} else {
		ret = HAL_I2C_Master_Receive(i2cbus, devAdres, retValue, len, HAL_MAX_DELAY);
		HAL_Delay(10);
		if (ret != HAL_OK) {
			strcpy((char*) buf2, "EEPROM Read Error I2C-RX\r\n");
		} else {

		}
	}
	HAL_UART_Transmit(&huart1, buf2, strlen((char*) buf2), 1000);
#endif
}
