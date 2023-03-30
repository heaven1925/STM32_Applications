/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
  * @warning 42MHz CAN Clock -> 250KBps configuration
********************************************************************************/

#ifndef __EEM_PROTOCOL_H__
#define	__EEM_PROTOCOL_H__

#if defined(STM32F446xx)
/*
* STM32F4xx series are using bxCAN periph
*/
#include "stm32f4xx.h"
#elif defined(STM32H750xx)
/*
* STM32F4xx series are using FDCAN periph
*/
#include "stm32h7xx.h"
#endif

/* Library Header Definitions */
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

/********************** EEMProtocol version information **********************/
#define EEM_VERSION                1L              /**< major version number */
#define EEM_SUBVERSION             0L              /**< minor version number */
#define EEM_REVISION               0L              /**< revise version number*/

/********************** EEMProtocol basic data type definitions *************/
typedef signed   char              EEM_I8    ;    /**<  8bit integer type */
typedef signed   short             EEM_I16   ;    /**< 16bit integer type */
typedef signed   int               EEM_I32   ;    /**< 32bit integer type */
typedef unsigned char              EEM_U8    ;    /**<  8bit unsigned integer type */
typedef unsigned short             EEM_U16   ;    /**< 16bit unsigned integer type */
typedef unsigned int               EEM_U32   ;    /**< 32bit unsigned integer type */


/*
* BOOL Type Definitions
*/
typedef EEM_U8					   	EEM_BOOL_T;
#define EEM_TRUE                    1             /**< boolean true  */
#define EEM_FALSE                   0             /**< boolean fails */

/*
* Error Type Definitions
*/
typedef EEM_U8					   	EEM_ERR_T;
#define EEM_EOK                      0             /**< There is no error */
#define EEM_ERR                      1             /**< A generic error happens */

/* null code definition  */
#define EEM_NULL                     (0)

/*----------------------------------------------------------------------------*/
/* Miscellaneous definitions                                                  */
/*----------------------------------------------------------------------------*/

/*
* Can packet maximum byte size
*/
#define	EEM_MAX_SIZE				   	8


/*
* Can packet handler ring buffer maximum size
*/
#define	EEM_BUFFER_SIZE					20

/*
* EEMProtocol Identifier type data structure
*/
typedef union{
		EEM_U32 main;
		struct
		{
			EEM_U8	dummy 		: 3 ; /* Excess bits */
			/***** PROTOCOL BASE BITS **********/
			EEM_U8	priority 	: 3 ; /* Priority */
			EEM_U8	reserved	: 1 ; /* R */
			EEM_U8	dataPoint	: 1 ; /* DP */
			/***********************************/
			EEM_U8  messageID	: 8 ; /* Specific Message ID */
			EEM_U8  DA			: 8 ; /* Destination Addr    */
			EEM_U8  SA			: 8 ; /* Source Addr		 */
		}Pages;
}EEM_CAN_ID_st;


/*
* EEMProtocol Packet main data structure
*/
typedef struct
{
	/* Main CAN Packet */
	EEM_CAN_ID_st 	EXTENDED_ID			;
	/* CAN Data */
	EEM_U8	DATA[ EEM_MAX_SIZE ];
	/* CAN Byte */
	EEM_U8			BYTE_COUNT			;
}EEM_CAN_Packet_st;


typedef struct
{
	/* ring buffer main buffer */
	EEM_U32			extended_ID[ EEM_BUFFER_SIZE ];
	EEM_U8			data[ EEM_BUFFER_SIZE ][ EEM_MAX_SIZE ];
	EEM_U32			byte_count;
	/* ring buffer obj's */
	EEM_U8 			head;	/* Head of ring buffer */
	EEM_U8			tail;	/* Tail of ring buffer */
}EEM_RING_Buffer_st;

#if defined(STM32F446xx)

/*
* EEMProtocol STM32F446xx data structure
*/	
typedef struct
{
/* Main bxCAN Periph Handle */
CAN_HandleTypeDef hbxcanHandle;
/* bxCAN Filter Handle */
CAN_FilterTypeDef sFilterConfig;
/* Classic CAN Variables */
CAN_TxHeaderTypeDef   	txHeader;
CAN_RxHeaderTypeDef   	rxHeader;
EEM_U8               	txData[ EEM_MAX_SIZE ];
EEM_U8               	rxData[ EEM_MAX_SIZE ];
/**************************/
}EEM_bxCAN_PeriphBase_st;	

#elif defined(STM32H750xx)

/*
* EEMProtocol STM32H750xx data structure
*/	
typedef struct
{
/* Main FDCAN Periph Handle */
FDCAN_HandleTypeDef 	hfdcanHandle;
/* FDCAN Filter Handle */
FDCAN_FilterTypeDef		sFilterConfig;
/* Classic CAN Variables */
FDCAN_TxHeaderTypeDef   txHeader;
FDCAN_RxHeaderTypeDef   rxHeader;
/**************************/
}EEM_FDCAN_PeriphBase_st;	
#endif


typedef struct 
{
#if defined(STM32F446xx)
	EEM_bxCAN_PeriphBase_st*  bxHandle;
#elif defined(STM32H750xx)
	EEM_FDCAN_PeriphBase_st*  fdHandle;
#endif
	/* Main Can Packet */
	EEM_U8           txData[ EEM_MAX_SIZE ];
	EEM_U8           rxData[ EEM_MAX_SIZE ];
	/* Ring Buffer Struct */
	EEM_RING_Buffer_st		 ringBuffer;
}EEM_Protocol_obj_st;


/*
* EEM_Protocol_Methods
*/
typedef struct
{
	/*
	* Init function Method 
	*/
	EEM_ERR_T      (*EEM_Init	)( EEM_Protocol_obj_st*  param                            	);
	EEM_ERR_T      (*EEM_TX		)( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf	);
	EEM_ERR_T 	   (*EEM_RX		)( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf	);
	EEM_ERR_T  	   (*EEM_PUSH	)( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param 	);
	EEM_ERR_T  	   (*EEM_PULL	)( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param 	);
	EEM_BOOL_T	   (*EEM_RB_ISFULL  )( EEM_RING_Buffer_st* ringBuf );
	EEM_BOOL_T	   (*EEM_RB_ISEMPTY )( EEM_RING_Buffer_st* ringBuf );
	/*
	Protocol machine change data defined format of variables
	*/
	EEM_ERR_T     (*EEM_PERIODIC)( void* param );
	
}EEM_Protocol_opr_st;


typedef struct{
	
	EEM_Protocol_obj_st		obj;
	EEM_Protocol_opr_st		ops;
	
}EEM_Protocol_st;

/*----------------------------------------------------------------------------*/
/* Functions used outside this module                                         */
/*----------------------------------------------------------------------------*/
EEM_ERR_T 		EEM_INIT	(  EEM_Protocol_obj_st*  param );

EEM_ERR_T 		EEM_TX		( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf );
		
EEM_ERR_T 		EEM_RX		( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf );

EEM_ERR_T 		EEM_PERIODIC( void* param );

/*----------------------------------------------------------------------------*/
/* Functions used only by this module                                         */
/*----------------------------------------------------------------------------*/
static EEM_U8   EEM_PUSH( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param);

static EEM_U8	EEM_PULL( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param);

static EEM_BOOL_T	EEM_RB_ISFULL( EEM_RING_Buffer_st* ringBuf );

static EEM_BOOL_T	EEM_RB_ISEMPTY( EEM_RING_Buffer_st* ringBuf );


/*----------------------------------------------------------------------------*/
/* Variables used only by this module                                         */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Variables used outside this module                                         */
/*----------------------------------------------------------------------------*/
EEM_Protocol_st	protocol;

/*----------------------------------------------------------------------------*/
/* Externs for variables                                                      */
/*----------------------------------------------------------------------------*/


#endif /* __EEM_PROTOCOL_H__ */
/***********************************END OF FILE********************************/
