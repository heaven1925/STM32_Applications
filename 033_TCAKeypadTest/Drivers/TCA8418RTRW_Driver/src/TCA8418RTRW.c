/*****************************************************************************/
/*	Filename: tca8418_keypad.c												 */
/*	Feature:  INPUT CAPTURE													 */
/*	Module:	  KEYPAD														 */
/*  Author:	  Umit Kayacik umtkyck@gmail.com                                 */
/*                                                                           */
/*																			 */
/*	********************* Ltd. owns the copyright in this					 */
/*	and associated documents and all rights are reserved.					 */
/*	This document and associated documents must not be						 */
/*	used for any purpose other than that for which they						 */
/*	are supplied and must not be copied in whole or in						 */
/*	part, or disclosed to others without the prior							 */
/*	written consent of ********************* Ltd.	Any copy				 */
/*	of this document made by any method must also contain a					 */
/*	copy of this legend.													 */
/*																			 */
/*	(c) ********************* LTD. 2020										 */
/*****************************************************************************/

#define __tca8418_ /* multiple inclusion tag */

#include "TCA8418RTRW.h"
#include "stdbool.h"

extern I2C_HandleTypeDef hi2c2;

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Inits the TCA8418 for keypad operation                                  */
/*****************************************************************************/
void tca8418_Keypad_init(void)
{
	uint8_t rows;
	uint16_t cols;
	uint8_t config;
	//@BACK: 4X4 VE 6X4 için duzenle
	rows 	= ROW0|ROW1|ROW2|ROW3;
	cols 	= COL0|COL1|COL2;
	config 	= CFG_KE_IEN|CFG_INT_CFG;

	tca8418_ConfigureKeys(rows, cols, config);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Returns the value of keypad value                                       */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Reads keypad value from latest event                                    */
/*****************************************************************************/
uint8_t tca8418_ReadKeypad(void)
{
  return(tca8418_GetKeyEvent(0));
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Boolean state                                                           */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name tca8418_ConfigureKeys												 */
/* @param rows ROW number of keypad						                     */
/* @param cols COLOUMN number of keypad						                 */
/* @param confi config mode, pls look at header for bit meanings             */
/* Configure the TCA8418 for keypad operation                                */
/*****************************************************************************/
uint8_t tca8418_ConfigureKeys(uint8_t rows, uint16_t cols, uint8_t config)
{
	uint8_t col_tmp;

	//Pins all default to GPIO. pinMode(x, KEYPAD); may be used for
	//individual pins.
	tca8418_WriteByte(rows, REG_KP_GPIO1);

	col_tmp = (uint8_t)(0xff & cols);
	tca8418_WriteByte(col_tmp, REG_KP_GPIO2);
	col_tmp = (uint8_t)(0x03 & (cols>>8));
	tca8418_WriteByte(col_tmp, REG_KP_GPIO3);

	config |= CFG_AI;
	tca8418_WriteByte(config, REG_CFG);

	return true;
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Writes value to keypads reqister                                  */
/* @param data 					                                             */
/* @param req Register memory         						                 */
/*****************************************************************************/
void tca8418_WriteByte(uint8_t data, uint8_t reg)
{
	uint8_t cmd[2];

	cmd[0] = reg;
	cmd[1] = data;

	//Waits for the i2c is in ready state.
	while (HAL_I2C_GetState(&hi2c2) is_not HAL_I2C_STATE_READY);

	//Transmit data to IC
	HAL_I2C_Master_Transmit(&hi2c2, TCA8418_ADDR, cmd, 2, I2C_TIMEOUT);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Received register value                                                 */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Read value from keypads reqister                                  */
/* @param data 					                                             */
/* @param req Register memory         						                 */
/*****************************************************************************/
uint8_t tca8418_ReadByte(uint8_t *data, uint8_t reg)
{
	uint8_t cmd[1];

	cmd[0] = reg;

	//Waits for the i2c is in ready state.
	while (HAL_I2C_GetState(&hi2c2) is_not HAL_I2C_STATE_READY);

	//Transmit address data to IC
	if (HAL_I2C_Master_Transmit(&hi2c2, TCA8418_ADDR, cmd, 1, I2C_TIMEOUT) == HAL_OK)
	{
		//Receive value from IC
		HAL_I2C_Master_Receive(&hi2c2, TCA8418_ADDR, data, 1, I2C_TIMEOUT);
		return true;
	}
	else
	{
		return false;
	}
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Can be used for CTRL+ALT+DEL ops                                  */
/* @param data 					                                             */
/* @param req Register memory         						                 */
/*****************************************************************************/
void tca8418_Write3Bytes(uint32_t data, uint8_t reg)
{
	uint8_t cmd[4];

	union
	{
		uint8_t b[4];
		uint32_t w;
	} datau;

	datau.w = data;

	cmd[0] = reg;
	cmd[1] = datau.b[0];
	cmd[2] = datau.b[1];
	cmd[3] = datau.b[2];

	//Waits for the i2c is in ready state.
	while (HAL_I2C_GetState(&hi2c2) is_not HAL_I2C_STATE_READY);

	//Transmit address data to IC
	HAL_I2C_Master_Transmit(&hi2c2, TCA8418_ADDR, cmd, 4, I2C_TIMEOUT);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Received register value                                                 */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Read value from keypads reqister                                  */
/* @param data 					                                             */
/* @param req Register memory         						                 */
/*****************************************************************************/
uint8_t tca8418_Read3Bytes(uint32_t *data, uint8_t reg)
{
	uint8_t cmd[1];

	union
	{
		uint8_t b[4];
		uint32_t w;
	} datau;

	datau.w = *data;

	cmd[0] = reg;

	//Waits for the i2c is in ready state.
	while (HAL_I2C_GetState(&hi2c2) is_not HAL_I2C_STATE_READY);

	//Transmit address data to IC
	if (HAL_I2C_Master_Transmit(&hi2c2, TCA8418_ADDR, cmd, 1, I2C_TIMEOUT) == HAL_OK)
	{
		//Receive value from IC
		HAL_I2C_Master_Receive(&hi2c2, TCA8418_ADDR, &datau.b[0], 3, I2C_TIMEOUT);
		return true;
	}
	else
	{
		return false;
	}
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Writes value the GPIO port                                              */
/*****************************************************************************/
void tca8418_Write(uint32_t value)
{
	_PORT = value;

	tca8418_UpdateGPIO();
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Reads the GPIO port                                                     */
/*****************************************************************************/
uint32_t tca8418_Read(void)
{
	tca8418_ReadGPIO();

	return _PORT;
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Toggles pin when it is in output mode                                   */
/*****************************************************************************/
void tca8418_Toggle(uint32_t pin)
{
	_PORT ^= (bit(pin));

	tca8418_UpdateGPIO();
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Blinks pin when it is in output mode                                    */
/*****************************************************************************/
void tca8418_Blink(uint32_t pin, uint16_t count, uint32_t duration)
{
	duration /= count * 2;

	while(count--)
	{
		tca8418_Toggle(pin);
		HAL_Delay(duration);
		tca8418_Toggle(pin);
		HAL_Delay(duration);
	}
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Reads all IO ports with its register in bulk                            */
/*****************************************************************************/
void tca8418_ReadGPIO()
{
#ifdef TCA8418_INTERRUPT_SUPPORT
	/* Store old _PIN value */
	_oldPIN = _PIN;
#endif

	tca8418_Read3Bytes((uint32_t *)&_PORT, REG_GPIO_DAT_OUT1);	//Read Data OUT Registers
	tca8418_Read3Bytes((uint32_t *)&_PIN, REG_GPIO_DAT_STAT1);	//Read Data STATUS Registers
	tca8418_Read3Bytes((uint32_t *)&_DDR, REG_GPIO_DIR1);		//Read Data DIRECTION Registers
	tca8418_Read3Bytes((uint32_t *)&_PKG, REG_KP_GPIO1);		//Read Keypad/GPIO SELECTION Registers
	tca8418_Read3Bytes((uint32_t *)&_PUR, REG_GPIO_PULL1);		//Read KPull-Up RESISTOR Registers
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/*   Updates all IO ports with its register in bulk                          */
/*****************************************************************************/
void tca8418_UpdateGPIO()
{
	tca8418_Write3Bytes((uint32_t)_PORT, REG_GPIO_DAT_OUT1);	//Write Data OUT Registers
	tca8418_Write3Bytes((uint32_t)_DDR, REG_GPIO_DIR1);			//Write Data DIRECTION Registers
	tca8418_Write3Bytes((uint32_t)_PKG, REG_KP_GPIO1);			//Write Keypad/GPIO SELECTION Registers
	tca8418_Write3Bytes((uint32_t)_PUR, REG_GPIO_PULL1);		//Write Pull-Up RESISTOR Registers
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   ISR val                                                                 */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Gets ISR status                                                   */
/*****************************************************************************/
uint8_t tca8418_GetInterruptStatus(void)
{
	uint8_t status;

	tca8418_ReadByte(&status, REG_INT_STAT);
	return(status & 0x0F);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Clears ISR status for new reads                                   */
/* @param flags, pls look at header file                                     */
/*****************************************************************************/
void tca8418_ClearInterruptStatus(uint8_t flags)
{

	flags &= 0x0F;
	tca8418_WriteByte(flags, REG_INT_STAT);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Event address value                                                     */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Reads the specific event address                                  */
/* @param  FIFO event address                                                */
/*****************************************************************************/
uint8_t tca8418_GetKeyEvent(uint8_t event)
{
	uint8_t keycode;

	if (event > 9)
		return 0x00;

	tca8418_ReadByte(&keycode, (REG_KEY_EVENT_A+event));
	return(keycode);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Count number                                                            */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Gets filled FIFO number                                           */
/*****************************************************************************/
uint8_t tca8418_GetKeyEventCount(void)
{
	uint8_t count;

	tca8418_ReadByte(&count, REG_KEY_LCK_EC);
	return(count & 0x0F);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   ISR value                                                               */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Gets the stored interrupt status                                  */
/*****************************************************************************/
uint32_t tca8418_GetGPIOInterrupt(void)
{
	uint32_t Ints;

	union {
		uint32_t val;
	uint8_t arr[4];
	} IntU;

	tca8418_ReadByte(&IntU.arr[2], REG_GPIO_INT_STAT3);
	tca8418_ReadByte(&IntU.arr[1], REG_GPIO_INT_STAT2);
	tca8418_ReadByte(&IntU.arr[0], REG_GPIO_INT_STAT1);

	Ints = IntU.val;
	return(Ints);
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Boolean state                                                           */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Checks the key is in down state                                   */
/* @param key, pressed key                                                   */
/*****************************************************************************/
uint8_t tca8418_IsKeyDown(uint8_t key)
{
	if(key & 0x80)
		return true;
	else
		return false;
}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   Boolean state                                                           */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name   Logic get key value from keypads reqister                         */
/* @param key, pointer to received value                                     */
/*****************************************************************************/
uint8_t tca8418_GetKey(uint8_t *key)
{
	uint8_t tmpkey;

	tmpkey = tca8418_ReadKeypad();
	*key = *key & 0x7F;

	return(tca8418_IsKeyDown(tmpkey));
}
