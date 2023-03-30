/*****************************************************************************/
/*  Filename: tca8418_keypad.h                                               */
/*  Feature:  KEYPAD                                                         */
/*  Module:   KEYPAD                                                         */
/*  Author:	  Umit Kayacik umtkyck@gmail.com                                 */
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

#ifndef INC__TCA8418_KEYPAD_H_
#define INC__TCA8418_KEYPAD_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

/* I2C BUS IDs */
#define TCA8418_ADDR                     0x68

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
/** Comment this define to disable interrupt support */
#define TCA8418_INTERRUPT_SUPPORT

#define KEYPAD 			0x37
#define GPIO 			0x38
#define EDGE 			0x39
#define LEVEL 			0x40
#define INTERRUPT 		0x41
#define NOINTERRUPT 	0x42
#define FIFO 			0x43
#define NOFIFO 			0x44
#define DEBOUNCE 		0x45
#define NODEBOUNCE 		0x46

#ifndef I2CTIMEOUT
  #define I2CTIMEOUT 	100
#endif

/* TCA8418 hardware limits */
#define TCA8418_MAX_ROWS 8
#define TCA8418_MAX_COLS 10

/* TCA8418 register offsets */
#define REG_CFG 				0x01
#define REG_INT_STAT 			0x02
#define REG_KEY_LCK_EC 			0x03
#define REG_KEY_EVENT_A 		0x04
#define REG_KEY_EVENT_B 		0x05
#define REG_KEY_EVENT_C 		0x06
#define REG_KEY_EVENT_D 		0x07
#define REG_KEY_EVENT_E			0x08
#define REG_KEY_EVENT_F			0x09
#define REG_KEY_EVENT_G 		0x0A
#define REG_KEY_EVENT_H 		0x0B
#define REG_KEY_EVENT_I 		0x0C
#define REG_KEY_EVENT_J 		0x0D
#define REG_KP_LCK_TIMER 		0x0E
#define REG_UNLOCK1 			0x0F
#define REG_UNLOCK2 			0x10
#define REG_GPIO_INT_STAT1 		0x11
#define REG_GPIO_INT_STAT2 		0x12
#define REG_GPIO_INT_STAT3 		0x13
#define REG_GPIO_DAT_STAT1 		0x14
#define REG_GPIO_DAT_STAT2 		0x15
#define REG_GPIO_DAT_STAT3 		0x16
#define REG_GPIO_DAT_OUT1 		0x17
#define REG_GPIO_DAT_OUT2 		0x18
#define REG_GPIO_DAT_OUT3 		0x19
#define REG_GPIO_INT_EN1 		0x1A
#define REG_GPIO_INT_EN2 		0x1B
#define REG_GPIO_INT_EN3 		0x1C
#define REG_KP_GPIO1 			0x1D
#define REG_KP_GPIO2 			0x1E
#define REG_KP_GPIO3 			0x1F
#define REG_GPI_EM1 			0x20
#define REG_GPI_EM2 			0x21
#define REG_GPI_EM3 			0x22
#define REG_GPIO_DIR1 			0x23
#define REG_GPIO_DIR2 			0x24
#define REG_GPIO_DIR3 			0x25
#define REG_GPIO_INT_LVL1 		0x26
#define REG_GPIO_INT_LVL2 		0x27
#define REG_GPIO_INT_LVL3 		0x28
#define REG_DEBOUNCE_DIS1 		0x29
#define REG_DEBOUNCE_DIS2 		0x2A
#define REG_DEBOUNCE_DIS3 		0x2B
#define REG_GPIO_PULL1 			0x2C
#define REG_GPIO_PULL2 			0x2D
#define REG_GPIO_PULL3 			0x2E

/* TCA8418 bit definitions */
#define CFG_AI 					0x80
#define CFG_GPI_E_CFG 			0x40
#define CFG_OVR_FLOW_M 			0x20
#define CFG_INT_CFG 			0x10
#define CFG_OVR_FLOW_IEN 		0x08
#define CFG_K_LCK_IEN 			0x04
#define CFG_GPI_IEN 			0x02
#define CFG_KE_IEN 				0x01

#define INT_STAT_CAD_INT 		0x10
#define INT_STAT_OVR_FLOW_INT 	0x08
#define INT_STAT_K_LCK_INT 		0x04
#define INT_STAT_GPI_INT 		0x02
#define INT_STAT_K_INT 			0x01

/* TCA8418 register masks */
#define KEY_LCK_EC_KEC 			0x7
#define KEY_EVENT_CODE 			0x7f
#define KEY_EVENT_VALUE 		0x80

/* TCA8418 Rows and Columns */
#define ROW0 0x01
#define ROW1 0x02
#define ROW2 0x04
#define ROW3 0x08
#define ROW4 0x10
#define ROW5 0x20
#define ROW6 0x40
#define ROW7 0x80

#define COL0 0x0001
#define COL1 0x0002
#define COL2 0x0004
#define COL3 0x0008
#define COL4 0x0010
#define COL5 0x0020
#define COL6 0x0040
#define COL7 0x0080
#define COL8 0x0100
#define COL9 0x0200

/*** Public Types *** */

/*** Public Function Prototypes ***/
void 	tca8418_ClearInterruptStatus(uint8_t flags);
void 	tca8418_Keypad_init(void);
uint8_t tca8418_ReadKeypad(void);

/*** Multiple Inclusion Tag ***/
#ifdef __tca8418_

/*** Private Function Prototypes ***/
uint8_t 	tca8418_ConfigureKeys(uint8_t rows, uint16_t cols, uint8_t config);
void 		tca8418_WriteByte(uint8_t data, uint8_t reg);
uint8_t 	tca8418_Read3Bytes(uint32_t *data, uint8_t reg);
void 		tca8418_Write3Bytes(uint32_t data, uint8_t reg);
uint8_t 	tca8418_ReadByte(uint8_t *data, uint8_t reg);
void 		tca8418_PinMode(uint32_t pin, uint8_t mode);
void 		tca8418_DigitalWrite(uint32_t pin, uint8_t value);
uint8_t 	tca8418_DigitalRead(uint32_t pin);
void 		tca8418_Write(uint32_t value);
uint32_t 	tca8418_Read(void);
void 		tca8418_Toggle(uint32_t pin);
void 		tca8418_Blink(uint32_t pin, uint16_t count, uint32_t duration);
void 		tca8418_ReadGPIO();
void 		tca8418_UpdateGPIO();
void 		tca8418_Dumpreg(void);
uint8_t 	tca8418_GetInterruptStatus(void);
uint8_t 	tca8418_GetKeyEvent(uint8_t event);
uint8_t 	tca8418_GetKeyEventCount(void);
uint32_t 	tca8418_GetGPIOInterrupt(void);
uint8_t 	tca8418_IsKeyDown(uint8_t key);
uint8_t 	tca8418_GetKey(uint8_t *key);

#ifdef TCA8418_INTERRUPT_SUPPORT
void 		tca8418_EnableInterrupt(uint8_t pin, void(*selfCheckFunction)(void));
void 		tca8418_DisableInterrupt();
void 		tca8418_PinInterruptMode(uint32_t pin, uint8_t mode, uint8_t level, uint8_t fifo);
//void pinInterruptMode(uint32_t pin, uint8_t mode);
#endif

/*** Private Defines ***/

/*** Private Implementation Variables ***/
#ifdef TCA8418_INTERRUPT_SUPPORT
/** Old value of _PIN variable */
volatile uint32_t _oldPIN;

/** ISR ignore flag */
volatile uint8_t _isrIgnore;

/** PCINT pin used for "INT" pin handling */
uint8_t _pcintPin;

/** Interrupts modes of pins ( LOW, CHANGE, FALLING, RISING)  */
uint8_t _intMode[24];

/** Interrupts callback functions */
void (*_intCallback[24])(void);
#endif

uint8_t 	_address;
uint32_t 	_PKG; 		// Pin Keypad or GPIO 0=GPIO, 1=Keypad
uint32_t 	_PORT;
uint32_t 	_PIN; 		// Pin State
uint32_t 	_DDR; 		//Pin Direction INPUT or OUTPUT
uint32_t	_PUR; 		//Pull-Up Resistor Selection
#else

/*** Extern Function Prototypes ***/

/*** Extern Implementation Variables ***/

#endif /* __tca8418_ */

#endif /* INC__TCA8418_KEYPAD_H_ */
