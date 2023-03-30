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

#ifndef INC__PCA9552_LED_DRIVER_H_
#define INC__PCA9552_LED_DRIVER_H_

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_gpio.h"

/* I2C BUS IDs */
#define TCA8418_ADDR                     0x68

/*
 * PCA9552 I2C Addressing
 * 1 1 0 0 A2 A1 A0 R/W/
 * 1 1 0 0 0  1  1 0
 */

/* USER CODE BEGIN PV */
static const uint8_t PCA9552_ADDR_1 = 0x61 << 1; // Use 8-bit address
static const uint8_t PCA9552_ADDR_2 = 0x62 << 1; // Use 8-bit address
static const uint8_t PCA9552_ADDR_4 = 0x63 << 1; // Use 8-bit address
static const uint8_t PCA9552_ADDR_5 = 0x65 << 1; // Use 8-bit address

static const uint8_t PCA9552_ADDR	= 0b11000110 ;

/* I2C Base Definitions */
#define I2C_TRIAL_TIMES                  10
#define I2C_TIMEOUT		                 10

/* Global Terms */

#define is								==
#define is_not							!=
#define and								&&
#define or								||
#define	NOT_USED						81 /* Key val 1..80 */


/*** Public Defined Data ***/

// pca9552 address defines
#define ADDR_INPUT0      	0x00
#define ADDR_INPUT1      	0x01
#define ADDR_PSC0      		0x02
#define ADDR_PWM0      		0x03
#define ADDR_PSC1      		0x04
#define ADDR_PWM1      		0x05
#define ADDR_LS0     		0x06
#define ADDR_LS1     		0x07
#define ADDR_LS2     		0x08
#define ADDR_LS3     		0x09

#define PWM_PORT_0     		0x00
#define PWM_PORT_1     		0x01

#define FREQ_1_HZ     		1
#define FREQ_2_HZ     		2
#define FREQ_3_HZ     		3
#define FREQ_4_HZ     		4
#define FREQ_5_HZ     		5

// user defines
#define PIN_INPUT      		0x0
#define PIN_OUTPUT     		0x1

#define BIT_SET(addr, shift) 	(addr | (1 << shift))
#define BIT_RESET(addr, shift) 	(addr & ~(1 << shift))
#define BIT_GET(addr, shift) 	(addr & (1 << shift))

#define LED_0_MASK  	0xFFFFFFFC
#define LED_1_MASK  	0xFFFFFFF3
#define LED_2_MASK  	0xFFFFFFCF
#define LED_3_MASK  	0xFFFFFF3F
#define LED_4_MASK  	0xFFFFFCFF
#define LED_5_MASK  	0xFFFFF3FF
#define LED_6_MASK  	0xFFFFCFFF
#define LED_7_MASK  	0xFFFF3FFF
#define LED_8_MASK  	0xFFFCFFFF
#define LED_9_MASK  	0xFFF3FFFF
#define LED_10_MASK  	0xFFCFFFFF
#define LED_11_MASK  	0xFF3FFFFF
#define LED_12_MASK  	0xFCFFFFFF
#define LED_13_MASK  	0xF3FFFFFF
#define LED_14_MASK  	0xCFFFFFFF
#define LED_15_MASK  	0x3FFFFFFF

#define MAX_LED_NUMBER      15

/*** Public Types *** */
enum /** enum with names of ports ED0 - ED15 */
{
    PCA_LED0=0, PCA_LED1, 	PCA_LED2, 	PCA_LED3,
	PCA_LED4, 	PCA_LED5, 	PCA_LED6, 	PCA_LED7,
	PCA_LED8, 	PCA_LED9, 	PCA_LED10, 	PCA_LED11,
	PCA_LED12, 	PCA_LED13, 	PCA_LED14, 	PCA_LED15
};

/** enum with names of the ports as they're referred to on the datasheet */
enum
{
    P00, P01, P02, P03, P04, P05, P06, P07,
    P10, P11, P12, P13, P14, P15, P16, P17,
};

enum
{
	LED_ON	=	0,
	LED_OFF,
	PWM_0,
	PWM_1
};

/*** Public Function Prototypes ***/
uint8_t pca9552_init(uint8_t address);
void 	pca9552_SetPWM(uint8_t address, uint8_t pwm_port, uint8_t freq);
uint8_t pca9552_DigitalRead(uint8_t address, uint8_t pin);
void 	pca9552_DigitalWrite(uint8_t address, uint8_t pin, uint8_t value);
void 	pca9552_UpdatePinStates(uint8_t address);
uint8_t pca9552_StateOfPin(uint8_t address, uint8_t pin);
void 	pca9552_TurnOffAllLeds(uint8_t address);
void 	pca9552_TurnOnAllLeds(uint8_t address);

/*** Multiple Inclusion Tag ***/
#ifdef __pca9552_

/*** Private Function Prototypes ***/
// low level methods
uint16_t 	pca9552_I2CGetValue(uint8_t address, uint8_t reg);
void 		pca9552_I2CSetValue(uint8_t address, uint8_t reg, uint8_t value);

/*** Private Defines ***/

/*** Private Types *** */
union PinState
{
	struct {
		uint8_t _stateOfPins_low;          // low order byte
		uint8_t _stateOfPins_high;         // high order byte
	};
	uint16_t _stateOfPins;                 // 16 bits presentation
};

union ConfigurationRegister
{
	struct {
		uint8_t _configurationRegister_low;          // low order byte
		uint8_t _configurationRegister_high;         // high order byte
	};
	uint16_t _configurationRegister;                 // 16 bits presentation
};

union ValueRegister
{
	struct {
		uint8_t _valueRegister_0_3;                  // low order byte
		uint8_t _valueRegister_4_7;                  // low order byte
		uint8_t _valueRegister_8_11;                  // low order byte
		uint8_t _valueRegister_12_15;                 // high order byte
	};
	uint32_t _valueRegister;
};

/*** Private Implementation Variables ***/
static const uint32_t LED_MASK[16]=
{
    0xFFFFFFFC,
    0xFFFFFFF3,
    0xFFFFFFCF,
    0xFFFFFF3F,

    0xFFFFFCFF,
    0xFFFFF3FF,
    0xFFFFCFFF,
    0xFFFF3FFF,

    0xFFFCFFFF,
    0xFFF3FFFF,
    0xFFCFFFFF,
    0xFF3FFFFF,

    0xFCFFFFFF,
    0xF3FFFFFF,
    0xCFFFFFFF,
    0x3FFFFFFF
};

static const uint32_t LED_OFFSET[16]=
{
    0, /* LED 0 */
    2,
    4,
    6,

    8, /* LED 4 */
    10,
    12,
    14,

    16, /* LED 8 */
    18,
    20,
    22,

    24, /* LED 12 */
    26,
    28,
    30
};

union PinState PCA_pinstate;
union ConfigurationRegister PCA_confreg;
union ValueRegister PCA_valreg;

uint8_t _addresss;                                    // address of port this class is supporting
int _error;                                          // error code from I2C

#else

/*** Extern Function Prototypes ***/

/*** Extern Implementation Variables ***/

#endif /*__pca9552_*/

#endif /* INC__PCA9552_LED_DRIVER_H_ */
