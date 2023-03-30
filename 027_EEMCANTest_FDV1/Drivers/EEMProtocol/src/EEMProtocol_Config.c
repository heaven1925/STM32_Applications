/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.c
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#include "EEMProtocol_Config.h"
#include "EEMProtocol.h"


	extern BCM_Module_st	BCM_MSG;
/* HVAC module has been written Cpp language in order to arduino framework */
/* Simple computer protocol has written pyhton language */
	extern BMS_Module_st	BMS_MSG;
	extern MS1_Module_st	MS1_MSG;
	extern MS2_Module_st	MS2_MSG;
	extern ISO_Module_st	ISO_MSG;
	extern TLM_Module_st	TLM_MSG;
	extern YSB_Module_st	YSB_MSG;



#if defined( BCM_MODULE )

/*******************************************************************************
	 @func    :	EEM_FILTER_BCM
	 @param   : FDCAN_FilterTypeDef sFilterConfig
	 @return  : EEM_ERR_T
	 @date	  : 7.02.2023
	 @INFO	  :	BCM Specific CANBUS Filtering Function
********************************************************************************/
EEM_ERR_T EEM_FILTER_BCM( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

	EEM_CAN_ID_st MessageID_01   = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_01.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_01.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_01.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_01.Pages.messageID = MESSAGE01 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_01.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_01.Pages.SA		  = HVAC_NODE	 ;	/* 8 Bit Source Addr		*/
	BCM_MSG.Message01_ID		  = MessageID_01.identifier ;

	EEM_CAN_ID_st MessageID_02   = {0}			 ;	/* 29 Bit Extended ID Frame */
    MessageID_02.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
    MessageID_02.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
    MessageID_02.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
    MessageID_02.Pages.messageID = MESSAGE02 	 ;  /* 8 Bit Message Soft ID 	*/
    MessageID_02.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
    MessageID_02.Pages.SA		  = HVAC_NODE	 ;	/* 8 Bit Source Addr		*/
    BCM_MSG.Message02_ID		  = MessageID_02.identifier ;

    EEM_CAN_ID_st MessageID_07   = {0}			 ;	/* 29 Bit Extended ID Frame */
    MessageID_07.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
    MessageID_07.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
    MessageID_07.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
    MessageID_07.Pages.messageID = MESSAGE07 	 ;  /* 8 Bit Message Soft ID 	*/
    MessageID_07.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
    MessageID_07.Pages.SA		  = MS1_NODE	 ;	/* 8 Bit Source Addr		*/
    BCM_MSG.Message07_ID		  = MessageID_07.identifier ;

	 EEM_CAN_ID_st MessageID_08   = {0}			 ;	/* 29 Bit Extended ID Frame */
	 MessageID_08.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	 MessageID_08.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	 MessageID_08.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	 MessageID_08.Pages.messageID = MESSAGE08 	 ;  /* 8 Bit Message Soft ID 	*/
	 MessageID_08.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	 MessageID_08.Pages.SA		  = MS1_NODE	 ;	/* 8 Bit Source Addr		*/
	 BCM_MSG.Message08_ID		  = MessageID_08.identifier ;

	 EEM_CAN_ID_st MessageID_09   = {0}			 ;	/* 29 Bit Extended ID Frame */
	 MessageID_09.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	 MessageID_09.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	 MessageID_09.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	 MessageID_09.Pages.messageID = MESSAGE09 	 ;  /* 8 Bit Message Soft ID 	*/
	 MessageID_09.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	 MessageID_09.Pages.SA		  = MS2_NODE	 ;	/* 8 Bit Source Addr		*/
	 BCM_MSG.Message09_ID		  = MessageID_09.identifier ;

	 EEM_CAN_ID_st MessageID_10   = {0}			 ;	/* 29 Bit Extended ID Frame */
	 MessageID_10.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	 MessageID_10.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	 MessageID_10.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	 MessageID_10.Pages.messageID = MESSAGE10 	 ;  /* 8 Bit Message Soft ID 	*/
	 MessageID_10.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	 MessageID_10.Pages.SA		  = MS2_NODE	 ;	/* 8 Bit Source Addr		*/
	 BCM_MSG.Message10_ID		  = MessageID_10.identifier ;

	 EEM_CAN_ID_st MessageID_18   = {0}			 ;	/* 29 Bit Extended ID Frame */
	 MessageID_18.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	 MessageID_18.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	 MessageID_18.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	 MessageID_18.Pages.messageID = MESSAGE09 	 ;  /* 8 Bit Message Soft ID 	*/
	 MessageID_18.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	 MessageID_18.Pages.SA		  = MS1_NODE	 ;	/* 8 Bit Source Addr		*/
	 BCM_MSG.Message18_ID		  = MessageID_18.identifier ;

	 EEM_CAN_ID_st MessageID_19   = {0}			 ;	/* 29 Bit Extended ID Frame */
	 MessageID_19.Pages.priority  = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	 MessageID_19.Pages.reserved  = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	 MessageID_19.Pages.dataPoint = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	 MessageID_19.Pages.messageID = MESSAGE10 	 ;  /* 8 Bit Message Soft ID 	*/
	 MessageID_19.Pages.DA		  = BCM_NODE	 ;	/* 8 Bit Destination Addr	*/
	 MessageID_19.Pages.SA		  = MS2_NODE	 ;	/* 8 Bit Source Addr		*/
	 BCM_MSG.Message19_ID		  = MessageID_19.identifier ;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))



#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_01.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_02.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 2;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_07.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 3;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_08.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 4;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_09.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 5;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_10.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 6;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_18.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 7;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_19.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

#else

#if defined(SPI2CAN_Protocol)



#else
//ERROR
#endif


#endif
	return result;
}

#elif defined( HVAC_MODULE )
/* HVAC module has been written Cpp language in order to arduino framework */
#elif defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif defined( BMS_MODULE )
EEM_ERR_T EEM_FILTER_BMS( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( MS1_MODULE )
EEM_ERR_T EEM_FILTER_MS1( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

	EEM_CAN_ID_st MessageID_20    = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_20.Pages.priority   = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_20.Pages.reserved   = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_20.Pages.dataPoint  = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_20.Pages.messageID  = MESSAGE20 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_20.Pages.DA		  = MS1_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_20.Pages.SA		  = BCM_NODE	 ;	/* 8 Bit Source Addr		*/
	MS1_MSG.Message20_ID = MessageID_20.identifier;

	EEM_CAN_ID_st MessageID_21    = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_21.Pages.priority   = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_21.Pages.reserved   = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_21.Pages.dataPoint  = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_21.Pages.messageID  = MESSAGE21 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_21.Pages.DA		  = MS1_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_21.Pages.SA		  = BCM_NODE	 ;	/* 8 Bit Source Addr		*/
	MS1_MSG.Message21_ID = MessageID_21.identifier;



#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_20.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_21.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

#else



#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}


#elif defined( MS2_MODULE )
EEM_ERR_T EEM_FILTER_MS2( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	EEM_CAN_ID_st MessageID_22    = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_22.Pages.priority   = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_22.Pages.reserved   = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_22.Pages.dataPoint  = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_22.Pages.messageID  = MESSAGE22 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_22.Pages.DA		  = MS2_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_22.Pages.SA		  = BCM_NODE	 ;	/* 8 Bit Source Addr		*/

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_22.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

	EEM_CAN_ID_st MessageID_23    = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_23.Pages.priority   = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_23.Pages.reserved   = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_23.Pages.dataPoint  = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_23.Pages.messageID  = MESSAGE23 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_23.Pages.DA		  = MS2_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_23.Pages.SA		  = BCM_NODE	 ;	/* 8 Bit Source Addr		*/

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_23.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}


#elif defined( ISO_MODULE )
EEM_ERR_T EEM_FILTER_ISO( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}
#elif defined( TLM_MODULE )
EEM_ERR_T EEM_FILTER_TLM( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( YSB_MODULE )
EEM_ERR_T EEM_FILTER_YSB( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#endif
