/*****************************************************************************/
/*  Filename: pca9552.h                                                      */
/*  Feature:  LED DRIVER                                                     */
/*  Module:   MISC                                                           */
/*  Author:	  Umit Kayacik umtkyck@gmail.com                                 */
/*                                                                           */
/*                                                                           */
/*  ********************* Ltd. owns the copyright in this                    */
/*  and associated documents and all rights are reserved.                    */
/*  This document and associated documents must not be                       */
/*  used for any purpose other than that for which they                      */
/*  are supplied and must not be copied in whole or in                       */
/*  part, or disclosed to others without the prior                           */
/*  written consent of ********************* Ltd.  Any copy                  */
/*  of this document made by any method must also contain a                  */
/*  copy of this legend.                                                     */
/*                                                                           */
/*  (c) ********************* LTD. 2020                                      */
/*****************************************************************************/

#define __pca9552_ /* multiple inclusion tag */

#include "_Pca9552_Led_Driver.h"

/* External variables -------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c3;


/*
 * PCA9552 I2C Addressing
 * 1 1 0 0 A2 A1 A0 R/W/
 * 1 1 0 0 0  1  1 0
 */


/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   None                                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name pca9552 constructor												 */
/* @param address I2C address of the IO Expander						     */
/* Creates the class interface and sets the I2C Address of the port          */
/*****************************************************************************/
uint8_t pca9552_init(uint8_t address)
{
    _addresss         = address;        // save the address id
    PCA_valreg._valueRegister   = 0;

	/* Checks for keypad is ready-to-go */
	if (HAL_I2C_IsDeviceReady(&hi2c3, _addresss,
							     I2C_TRIAL_TIMES, I2C_TIMEOUT) == HAL_OK)
	{
		_error = 0;

		/* set prescaler values for blinking when needed */
		pca9552_SetPWM(_addresss, PWM_PORT_0, FREQ_5_HZ);
		pca9552_SetPWM(_addresss, PWM_PORT_1, FREQ_2_HZ);
		pca9552_TurnOffAllLeds(_addresss);
	}
	else
	{
		_error = 1;
	}

    if (_error != 0)
    {
    	return false;
    }
    else
    {
    	return true;
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
/* @name pca9552_SetPWM                                                      */
/* @param address 	I2C address of the IO Expander						     */
/* @param pwm_port  There are 2 pwm reg in IC, choose PWM0 or PWM1           */
/* @param freq 		Blink freq in HZ						                 */
/* sets the freq of this IO pin                                              */
/*****************************************************************************/
void pca9552_SetPWM(uint8_t address, uint8_t pwm_port, uint8_t freq)
{
	_addresss   = address;

	uint16_t psc;

	psc = ((44 * 1) / freq) - 1;

	if (pwm_port is PWM_PORT_0)
	{
		pca9552_I2CSetValue(_addresss, ADDR_PSC0, psc);
		pca9552_I2CSetValue(_addresss, ADDR_PWM0, 0); // %100 duty
	}
	else
	{
		pca9552_I2CSetValue(_addresss, ADDR_PSC1, psc);
		pca9552_I2CSetValue(_addresss, ADDR_PWM1, 0); // %100 duty
	}

}

/*****************************************************************************/
/*                                SYNOPSIS                                   */
/*                                --------                                   */
/*   Function Return Value :-                                                */
/*   ------------------------                                                */
/*   @return value of pin                                                    */
/*                                                                           */
/*   Function Specification:-                                                */
/*   -----------------------                                                 */
/* @name digitalRead Reads the high/low value of specified pin				 */
/* @param address 	I2C address of the IO Expander						     */
/* @param pin																 */
/* Reads the selected pin.												     */
/*****************************************************************************/
uint8_t pca9552_DigitalRead(uint8_t address, uint8_t pin)
{
    uint16_t _inputData = 0;

    _addresss = address;

    // we wil only process pins <= 15
    if (pin > MAX_LED_NUMBER )
    	return 0xFF;

    _inputData  = pca9552_I2CGetValue(_addresss, ADDR_INPUT0);
    _inputData |= pca9552_I2CGetValue(_addresss, ADDR_INPUT1) << 8;

    PCA_pinstate._stateOfPins = _inputData;

    // now mask the bit required and see if it is a HIGH
    if ((_inputData & (1 << pin)) > 0)
    {
        // the bit is HIGH otherwise we would return a LOW value
        return GPIO_PIN_SET;
    }
    else
    {
        return GPIO_PIN_RESET;
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
/* @name digitalRead Reads the high/low value of specified pin				 */
/* @param address 	I2C address of the IO Expander						     */
/* @param pin		Spesific pin to change output state						 */
/* @param pin		There are 4 state for each out, OFF-ON-PWM0-PWM1		 */
/* Writes the selected pin.												     */
/*****************************************************************************/
void pca9552_DigitalWrite(uint8_t address, uint8_t pin, uint8_t value)
{
	uint32_t temp = 0;

	_addresss = address;

    PCA_valreg._valueRegister_0_3 	= (uint8_t)pca9552_I2CGetValue(_addresss, ADDR_LS0);
    PCA_valreg._valueRegister_4_7	= (uint8_t)pca9552_I2CGetValue(_addresss, ADDR_LS1);
    PCA_valreg._valueRegister_8_11 	= (uint8_t)pca9552_I2CGetValue(_addresss, ADDR_LS2);
	PCA_valreg._valueRegister_12_15	= (uint8_t)pca9552_I2CGetValue(_addresss, ADDR_LS3);

    temp = PCA_valreg._valueRegister;

    // if the value is LOW we will and the register value with correct bit set to zero
    if (value is LED_ON)
    {
        // this is a High value so we will or it with the value register 00
        temp = BIT_RESET(temp, LED_OFFSET[pin]);
        temp = BIT_RESET(temp, (LED_OFFSET[pin]+1));
    }
    else if (value is LED_OFF)
    {
        // this is a LOW value so we have to AND it with 0 into the _valueRegister 01
        temp = BIT_SET(temp, LED_OFFSET[pin]);
        temp = BIT_RESET(temp, (LED_OFFSET[pin]+1));
    }
    else if (value is PWM_0)
    {
        // this is a PWM0 value so we have to AND it with 0 into the _valueRegister 10
        temp = BIT_RESET(temp, LED_OFFSET[pin]);
        temp = BIT_SET(temp, (LED_OFFSET[pin]+1));
    }
    else if (value is PWM_1)
    {
        // this is a PWM1 value so we have to AND it with 0 into the _valueRegister 11
        temp = BIT_SET(temp, LED_OFFSET[pin]);
        temp = BIT_SET(temp, (LED_OFFSET[pin]+1));
    }
    else
    {
    	/* Do nothing */
    }

	PCA_valreg._valueRegister = temp;

    // check valid pin first
	// write configuration register to chip
    if (pin > MAX_LED_NUMBER)
    {
        _error = 255;            // invalid pin
        return;                  // exit
    }
    else if (pin <= 3)
    {
    	pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    }
    else if (pin <= 7 && pin > 3)
    {
    	pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    }
    else if (pin <= 11 && pin > 7)
    {
    	pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    }
    else if (pin <= 15 && pin > 11)
    {
    	pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
    }
    else
    {
    	/* Do nothing */
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
/* @name pca9552_TurnOffAllLeds				                                 */
/* @param address 	I2C address of the IO Expander						     */
/* Turns off all LEDs for required Bus ID								     */
/*****************************************************************************/
void pca9552_TurnOffAllLeds(uint8_t address)
{
	uint32_t temp = 0;

	_addresss = address;

    temp = (uint32_t)0x55555555; /* 01 for all led bits */

    PCA_valreg._valueRegister = temp;

    pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
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
/* @name pca9552_TurnOnAllLeds				                                 */
/* @param address 	I2C address of the IO Expander						     */
/* Turns on all LEDs for required Bus ID								     */
/*****************************************************************************/
void pca9552_TurnOnAllLeds(uint8_t address)
{
	uint32_t temp = 0;

	_addresss = address;

    temp = 0x00000000; /* 00 for all led bits */

    PCA_valreg._valueRegister = temp;

    pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
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
/* @name pca9552_TurnOnAllLeds				                                 */
/* @param address 	I2C address of the IO Expander						     */
/* Turns on all LEDs for required Bus ID								     */
/*****************************************************************************/
void pca9552_TurnOnSpecWhiteLeds(uint8_t address)
{
	uint32_t temp = 0;

	_addresss = address;

    temp = 0x00000000; /* 00 for all led bits */

    PCA_valreg._valueRegister = temp;

    pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
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
/* @name pca9552_TurnOnAllLeds				                                 */
/* @param address 	I2C address of the IO Expander						     */
/* Turns on all LEDs for required Bus ID								     */
/*****************************************************************************/
void pca9552_TurnOnSpecRedLeds(uint8_t address)
{
	uint32_t temp = 0;

	_addresss = address;

    temp = 0x00000000; /* 00 for all led bits */

    PCA_valreg._valueRegister = temp;

    pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
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
/* @name pca9552_TurnOnAllLeds				                                 */
/* @param address 	I2C address of the IO Expander						     */
/* Turns on all LEDs for required Bus ID								     */
/*****************************************************************************/
void pca9552_TurnOnButtonAllLeds(uint8_t address, uint8_t button)
{
	uint32_t temp = 0;

	_addresss = address;

    temp = 0x00000000; /* 00 for all led bits */

    PCA_valreg._valueRegister = temp;

    pca9552_I2CSetValue(_addresss, ADDR_LS0, PCA_valreg._valueRegister_0_3);
    pca9552_I2CSetValue(_addresss, ADDR_LS1, PCA_valreg._valueRegister_4_7);
    pca9552_I2CSetValue(_addresss, ADDR_LS2, PCA_valreg._valueRegister_8_11);
    pca9552_I2CSetValue(_addresss, ADDR_LS3, PCA_valreg._valueRegister_12_15);
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
/*   Stores states of all pins in _stateOfPins                               */
/*****************************************************************************/
void pca9552_UpdatePinStates(uint8_t address)
{
	_addresss = address;

	PCA_pinstate._stateOfPins  = pca9552_I2CGetValue(_addresss, ADDR_INPUT0);
	PCA_pinstate._stateOfPins |= pca9552_I2CGetValue(_addresss, ADDR_INPUT1) << 8;
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
/* @name digitalRead Reads the high/low value of specified pin				 */
/* @param address 	I2C address of the IO Expander						     */
/* @param pin																 */
/* Reads the state of selected pin.										     */
/*****************************************************************************/
uint8_t pca9552_StateOfPin(uint8_t address, uint8_t pin)
{
	_addresss = address;

	pca9552_Get_PinStates(address);

	if ((PCA_pinstate._stateOfPins & (1 << pin)) > 0)
	{
		// the bit is HIGH otherwise we would return a LOW value
		return GPIO_PIN_SET;
	}
	else
	{
		return GPIO_PIN_RESET;
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
/* @param address 	Address of I2C chip										 */
/* @param reg    	Register to read from									 */
/* @return data in register													 */
/* Reads the data from addressed chip at selected register. \n				 */
/* If the value is above 255, an error is set. \n							 */
/* 256 = either 0 or more than one byte is received from the chip			 */
/*****************************************************************************/
uint16_t pca9552_I2CGetValue(uint8_t address, uint8_t reg)
{
    uint16_t _inputData;
	uint8_t cmd[1];
	/* Preserve data from uninitialized pointer */
	uint8_t *data = (uint8_t *)malloc(1 * sizeof(uint8_t));

	cmd[0] = reg;

	//Waits for the i2c is in ready state
	while (HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY);

    // read the address input register
	if (HAL_I2C_Master_Transmit(&hi2c3, address, cmd, 1, I2C_TIMEOUT) == HAL_OK)
	{
	    // ask for 1 bytes to be returned
		HAL_I2C_Master_Receive(&hi2c3, address, data, 1, I2C_TIMEOUT);

		_inputData = data[0];
		free(data);
		return _inputData;
	}
	else
	{
		free(data);
        //
        // we are not receing the bytes we need
        //
        return 0x100;   // error code is above normal data range
	}

/* TODO TESTINFG
	while(HAL_I2C_Master_Receive(hi2c,(uint16_t)DevAddr, (uint8_t*)pData,(uint8_t)pLen,I2C_TIMEOUT)!=HAL_OK)
	{
	if(HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF)
	{
	  return false;
	}
	}
	return true;
*/
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
/* @param address 	Address of I2C chip										 */
/* @param reg  		register to write to									 */
/* @param value    	value to write to register								 */
/* Write the value given to the register set to selected chip.				 */
/*****************************************************************************/
void pca9552_I2CSetValue(uint8_t address, uint8_t reg, uint8_t value)
{
	uint8_t cmd[2];

	cmd[0] = reg;
	cmd[1] = value;

	//Waits for the i2c is in ready state.
	while (HAL_I2C_GetState(&hi2c3) is_not HAL_I2C_STATE_READY);

	while(HAL_I2C_Master_Transmit(&hi2c3, (uint16_t)address,
			      (uint8_t*)cmd, (uint8_t)2, I2C_TIMEOUT) is_not HAL_OK)
	{
		if(HAL_I2C_GetError(&hi2c3) is_not HAL_I2C_ERROR_AF)
		{
			_error = true;
			//return false;
		}
	}

	_error = false;
	//return true;
}
