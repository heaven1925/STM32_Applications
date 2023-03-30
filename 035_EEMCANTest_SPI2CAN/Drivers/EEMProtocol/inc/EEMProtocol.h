/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __EEM_PROTOCOL_H__
#define	__EEM_PROTOCOL_H__

/*
 *
*/
#ifndef SPI2CAN_Protocol
#define SPI2CAN_Protocol
//#undef SPI2CAN_Protocol
#endif

/*
 *
*/
#ifndef BXCAN_Protocol
#define BXCAN_Protocol
#undef  BXCAN_Protocol
#endif

/*
 *
*/
#ifndef FDCAN_Protocol
#define FDCAN_Protocol
#undef  FDCAN_Protocol
#endif


#if defined(SPI2CAN_Protocol)
/*
* STM32xxx series are using MCP2515 SPI2CAN Module
*/
#include "MCP2515.h"
#include "CAN_SPI.h"
#endif


#if defined(STM32F446xx) || defined(STM32F407xx)
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
typedef signed   char              EEM_I8       ; /**<  8bit integer type */
typedef signed   short             EEM_I16      ; /**< 16bit integer type */
typedef signed   int               EEM_I32      ; /**< 32bit integer type */
typedef unsigned char              EEM_U8       ; /**<  8bit unsigned integer type */
typedef unsigned short             EEM_U16      ; /**< 16bit unsigned integer type */
typedef unsigned int               EEM_U32      ; /**< 32bit unsigned integer type */


/*
* BOOL Type Definitions
*/
typedef EEM_U8					   	EEM_BOOL_T  ;
#define EEM_TRUE                    1             /**< boolean true  */
#define EEM_FALSE                   0             /**< boolean fails */

/*
* Error Type Definitions
*/
typedef EEM_U8					   	EEM_ERR_T   ;
#define EEM_EOK                      0             /**< There is no error */
#define EEM_ERROR                    1             /**< A generic error happens */

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
		EEM_U32 identifier;
		struct
		{
			/***** PROTOCOL BASE BITS **********/
			EEM_U8  SA			: 8 ; /* Source Addr		 */
			EEM_U8  DA			: 8 ; /* Destination Addr    */
			EEM_U8  messageID	: 8 ; /* Specific Message ID */
			EEM_U8	dataPoint	: 1 ; /* DP */
			EEM_U8	reserved	: 1 ; /* R */
			EEM_U8	priority 	: 3 ; /* Priority */
			EEM_U8	dummy 		: 3 ; /* Excess bits */
			/***********************************/
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
	EEM_U8			DATA[ EEM_MAX_SIZE ];
	/* CAN Byte Count */
	EEM_U32			TX_BYTE_COUNT		;
	EEM_U32			RX_BYTE_COUNT		;
}EEM_CAN_Packet_st;

typedef struct
{
	/* ring buffer main buffer */
	EEM_U8			data[ EEM_BUFFER_SIZE ][ EEM_MAX_SIZE ];
	EEM_CAN_ID_st	id[EEM_BUFFER_SIZE];
	EEM_U32			byte_count;
	/* ring buffer obj's */
	EEM_U8 			head;	/* Head of ring buffer */
	EEM_U8			tail;	/* Tail of ring buffer */
	EEM_BOOL_T		full;	/* Full or Empty status of buffer */
}EEM_RING_Buffer_st;

#if (( defined(STM32F446xx) || defined(STM32F407xx) ) && defined(BXCAN_Protocol) )

/*
* EEMProtocol STM32F446xx BXCAN data structure
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

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

/*
* EEMProtocol STM32H750xx FDCAN data structure
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
EEM_U8               	txData[ EEM_MAX_SIZE ];
EEM_U8               	rxData[ EEM_MAX_SIZE ];
/**************************/
}EEM_FDCAN_PeriphBase_st;	

#else

#if defined(SPI2CAN_Protocol)

typedef struct
{
	uCAN_MSG	txMessage;
	uCAN_MSG	rxMessage;
}EEM_SPI2CAN_PeriphBase_st;
#else
//ERROR
#endif

#endif


typedef struct 
{
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
	EEM_bxCAN_PeriphBase_st	 	bxHandle;
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
	EEM_FDCAN_PeriphBase_st  	dHandle;
#else
#if defined(SPI2CAN_Protocol)
	EEM_SPI2CAN_PeriphBase_st	spi2canHandle;
#else
//ERROR
#endif
#endif
	/* Main Can Packet */
	EEM_CAN_Packet_st		 canPacket;
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
	EEM_ERR_T 		 (*EEM_INIT )( EEM_Protocol_obj_st*  param	);
	EEM_ERR_T		 (*EEM_TX	)( EEM_CAN_Packet_st* param, EEM_U32 period );
	EEM_ERR_T 		 (*EEM_RX	)( EEM_CAN_Packet_st* 	param 	  ,
#if   (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
							 	  CAN_RxHeaderTypeDef   rxHeader  ,
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
								  FDCAN_RxHeaderTypeDef rxHeader   ,
#else
#if defined(SPI2CAN_Protocol)
								  uCAN_MSG*				rxPacked   ,
#endif
#endif
								  EEM_U8*				rxData	  );
/*
	Protocol machine change data defined format of variables
	*/
}EEM_Protocol_opr_st;


typedef struct{
	
	EEM_Protocol_obj_st		obj;
	EEM_Protocol_opr_st		ops;
	
}EEM_Protocol_st;

/*----------------------------------------------------------------------------*/
/* Functions used outside this module                                         */
/*----------------------------------------------------------------------------*/
EEM_ERR_T 		EEM_INIT	( EEM_Protocol_obj_st*  param );

EEM_ERR_T 		EEM_TX		( EEM_CAN_Packet_st* param, EEM_U32 period );
		
EEM_ERR_T 		EEM_RX		( EEM_CAN_Packet_st* 	param 	  ,
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
							 CAN_RxHeaderTypeDef   rxHeader	  ,
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
							 FDCAN_RxHeaderTypeDef rxHeader   ,
#else
#if defined(SPI2CAN_Protocol)
							 uCAN_MSG*			rxPacked	  ,
#endif
#endif
							 EEM_U8*				rxData	  );


EEM_ERR_T 		EEM_PERIODIC( EEM_CAN_Packet_st*  param );

/*----------------------------------------------------------------------------*/
/* Functions used only by this module                                         */
/*----------------------------------------------------------------------------*/
void   			EEM_PUSH	( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param);

void			EEM_POP 	( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param);

EEM_BOOL_T		EEM_IS_EMPTY( const EEM_RING_Buffer_st* buffer );

EEM_BOOL_T		EEM_IS_FULL	( const EEM_RING_Buffer_st* buffer );



/*----------------------------------------------------------------------------*/
/* Variables used only by this module                                         */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Variables used outside this module                                         */
/*----------------------------------------------------------------------------*/
extern 			EEM_Protocol_st			protocol;
extern const	EEM_Protocol_opr_st		ops;
/*----------------------------------------------------------------------------*/
/* Externs for variables                                                      */
/*----------------------------------------------------------------------------*/


#endif /* __EEM_PROTOCOL_H__ */
/***********************************END OF FILE********************************/
