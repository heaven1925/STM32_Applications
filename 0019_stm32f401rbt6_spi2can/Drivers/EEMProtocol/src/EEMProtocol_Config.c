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

extern HVAC_Module_st	HVAC_MSG;
extern BCM_Module_st	BCM_MSG;
extern SCB_Module_st	SCB_MSG;
extern BMS_Module_st	BMS_MSG;
extern MS1_Module_st	MS1_MSG;
extern MS2_Module_st	MS2_MSG;
extern ISO_Module_st	ISO_MSG;
extern TLM_Module_st	TLM_MSG;
extern YSB_Module_st	YSB_MSG;

EEM_U8 fixed_version_messages[][EEM_MAX_SIZE] =
{
		{ 0xEE , 0x00 , 0xEE , 0x00 , 0xEE , 0x00 , 0xEE , 0x00 } ,
		{ 0xEE , 0xEE , 0xEE , 0xEE , 0xEE , 0xEE , 0xEE , 0xEE }
};

EEM_U8 fixed_queryByte_messages[][EEM_MAX_SIZE] =
{
		{ 0x00 , 0x00 , 0x00 , 0x00 ,  0x00 , 0x00 , 0x00 , 0xFF } ,
		{ 0x00 , 0x00 , 0x00 , 0x00 ,  0x00 , 0x00 , 0xFF , 0x00 } ,
		{ 0x00 , 0x00 , 0x00 , 0x00 ,  0x00 , 0xFF , 0x00 , 0x00 } ,
		{ 0x00 , 0x00 , 0x00 , 0x00 ,  0xFF , 0x00 , 0x00 , 0x00 } ,
		{ 0x00 , 0x00 , 0x00 , 0xFF ,  0x00 , 0x00 , 0x00 , 0x00 } ,
		{ 0x00 , 0x00 , 0xFF , 0x00 ,  0x00 , 0x00 , 0x00 , 0x00 } ,
		{ 0x00 , 0xFF , 0x00 , 0x00 ,  0x00 , 0x00 , 0x00 , 0x00 } ,
		{ 0xFF , 0x00 , 0x00 , 0x00 ,  0x00 , 0x00 , 0x00 , 0x00 }
};

EEM_FixedMessage_st version[] =
{
		{ .identifier = 0x1FEE00EE , .fixedMessage = fixed_version_messages[0] },
		{ .identifier = 0x1FEEEE00 , .fixedMessage = fixed_version_messages[1] }
};

EEM_FixedMessage_st queryByte[] =
{
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[0] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[1] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[2] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[3] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[4] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[5] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[6] },
		{ .identifier = 0x1FFFFFFF , .fixedMessage = fixed_queryByte_messages[7] },
};

EEM_FixedFormat_st	fixed[] =
{
		{ .name = "Version   " , .msg = version    , .repeit_count = 1 } ,
		{ .name = "QueryByte " , .msg = queryByte  , .repeit_count = 1 }

};


void EEM_SEND_FIXEDMSG(void)
{
	/*
	EEM_CAN_Packet_st packHandle;

	packHandle.EXTENDED_ID = fixed->msg->identifier;
	memcpy( &packHandle.DATA[0] , &fixed->msg->fixedMessage[0] , EEM_MAX_SIZE);

	EEM_TX( EEM_CAN_Packet_st* param, EEM_U32 period )
	*/
}

/*******************************************************************************
	 @func    :	EEM_SET_IDENTIFIERS
	 @param   : void
	 @return  : void
	 @date	  : 7.02.2023
	 @INFO	  :	Set All Identifiers
********************************************************************************/
void EEM_SET_IDENTIFIERS(void)
{
	/* Message Identifier Handler */
	EEM_CAN_ID_st ID[SIZE_OF_MSG] = {0};

	ID[MSG01_INDEX].Pages.priority 		= PRIORITY_010 ;
	ID[MSG01_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG01_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG01_INDEX].Pages.messageID 	= MESSAGE01 ;
	ID[MSG01_INDEX].Pages.DA 			= BCM_NODE;
	ID[MSG01_INDEX].Pages.SA 			= HVAC_NODE ;
	HVAC_MSG.Message01_ID = ID[MSG01_INDEX].identifier ;

	ID[MSG02_INDEX].Pages.priority 		= PRIORITY_010 ;
	ID[MSG02_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG02_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG02_INDEX].Pages.messageID 	= MESSAGE02 ;
	ID[MSG02_INDEX].Pages.DA 			= BCM_NODE;
	ID[MSG02_INDEX].Pages.SA 			= HVAC_NODE ;
	HVAC_MSG.Message02_ID = ID[MSG02_INDEX].identifier ;

	ID[MSG03_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG03_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG03_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG03_INDEX].Pages.messageID 	= MESSAGE03 ;
	ID[MSG03_INDEX].Pages.DA 			= TLM_NODE;
	ID[MSG03_INDEX].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message03_ID = ID[MSG03_INDEX].identifier ;

	ID[MSG04_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG04_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG04_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG04_INDEX].Pages.messageID 	= MESSAGE04 ;
	ID[MSG04_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG04_INDEX].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message04_ID = ID[MSG04_INDEX].identifier ;

	ID[MSG05_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG05_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG05_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG05_INDEX].Pages.messageID 	= MESSAGE05 ;
	ID[MSG05_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG05_INDEX].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message05_ID = ID[MSG05_INDEX].identifier ;

	ID[MSG06_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG06_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG06_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG06_INDEX].Pages.messageID 	= MESSAGE06 ;
	ID[MSG06_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG06_INDEX].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message06_ID = ID[MSG06_INDEX].identifier ;

	ID[MSG07_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG07_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG07_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG07_INDEX].Pages.messageID 	= MESSAGE07 ;
	ID[MSG07_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG07_INDEX].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message07_ID = ID[MSG07_INDEX].identifier ;

	ID[MSG08_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG08_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG08_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG08_INDEX].Pages.messageID 	= MESSAGE08 ;
	ID[MSG08_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG08_INDEX].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message08_ID = ID[MSG08_INDEX].identifier ;

	ID[MSG09_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG09_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG09_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG09_INDEX].Pages.messageID 	= MESSAGE09 ;
	ID[MSG09_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG09_INDEX].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message09_ID = ID[MSG09_INDEX].identifier ;

	ID[MSG10_INDEX].Pages.priority 		= PRIORITY_100 ;
	ID[MSG10_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG10_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG10_INDEX].Pages.messageID 	= MESSAGE10 ;
	ID[MSG10_INDEX].Pages.DA 			= SCB_NODE;
	ID[MSG10_INDEX].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message10_ID = ID[MSG10_INDEX].identifier ;

	ID[MSG11_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG11_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG11_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG11_INDEX].Pages.messageID 	= MESSAGE11 ;
	ID[MSG11_INDEX].Pages.DA 			= MS1_NODE;
	ID[MSG11_INDEX].Pages.SA 			= BCM_NODE ;
	BCM_MSG.Message11_ID = ID[MSG11_INDEX].identifier ;

	ID[MSG12_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG12_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG12_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG12_INDEX].Pages.messageID 	= MESSAGE12 ;
	ID[MSG12_INDEX].Pages.DA 			= MS2_NODE;
	ID[MSG12_INDEX].Pages.SA 			= BCM_NODE ;
	BCM_MSG.Message12_ID = ID[MSG12_INDEX].identifier ;

	ID[MSG13_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG13_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG13_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG13_INDEX].Pages.messageID 	= MESSAGE13 ;
	ID[MSG13_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG13_INDEX].Pages.SA 			= MS1_NODE ;
	MS1_MSG.Message13_ID = ID[MSG13_INDEX].identifier ;

	ID[MSG14_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG14_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG14_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG14_INDEX].Pages.messageID 	= MESSAGE14 ;
	ID[MSG14_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG14_INDEX].Pages.SA 			= MS1_NODE ;
	MS1_MSG.Message14_ID = ID[MSG14_INDEX].identifier ;

	ID[MSG15_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG15_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG15_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG15_INDEX].Pages.messageID 	= MESSAGE15 ;
	ID[MSG15_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG15_INDEX].Pages.SA 			= MS1_NODE ;
	MS1_MSG.Message15_ID = ID[MSG15_INDEX].identifier ;

	ID[MSG16_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG16_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG16_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG16_INDEX].Pages.messageID 	= MESSAGE16 ;
	ID[MSG16_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG16_INDEX].Pages.SA 			= MS2_NODE ;
	MS2_MSG.Message16_ID = ID[MSG16_INDEX].identifier ;

	ID[MSG17_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG17_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG17_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG17_INDEX].Pages.messageID 	= MESSAGE17 ;
	ID[MSG17_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG17_INDEX].Pages.SA 			= MS2_NODE ;
	MS2_MSG.Message17_ID = ID[MSG17_INDEX].identifier ;

	ID[MSG18_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG18_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG18_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG18_INDEX].Pages.messageID 	= MESSAGE18 ;
	ID[MSG18_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG18_INDEX].Pages.SA 			= MS2_NODE ;
	MS2_MSG.Message18_ID = ID[MSG18_INDEX].identifier ;

	ID[MSG19_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG19_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG19_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG19_INDEX].Pages.messageID 	= MESSAGE19 ;
	ID[MSG19_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG19_INDEX].Pages.SA 			= MS1_NODE ;
	BCM_MSG.Message19_ID = ID[MSG19_INDEX].identifier ;

	ID[MSG20_INDEX].Pages.priority 		= PRIORITY_001 ;
	ID[MSG20_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG20_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG20_INDEX].Pages.messageID 	= MESSAGE20 ;
	ID[MSG20_INDEX].Pages.DA 			= BCM_NODE ;
	ID[MSG20_INDEX].Pages.SA 			= MS2_NODE ;
	BCM_MSG.Message20_ID = ID[MSG20_INDEX].identifier ;

	ID[MSG21_INDEX].Pages.priority 		= PRIORITY_011 ;
	ID[MSG21_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG21_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG21_INDEX].Pages.messageID 	= MESSAGE21 ;
	ID[MSG21_INDEX].Pages.DA 			= BCM_NODE;
	ID[MSG21_INDEX].Pages.SA 			= SCB_NODE;
	SCB_MSG.Message21_ID = ID[MSG21_INDEX].identifier ;

	ID[MSG22_INDEX].Pages.priority 		= PRIORITY_111 ;
	ID[MSG22_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG22_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG22_INDEX].Pages.messageID 	= MESSAGE22 ;
	ID[MSG22_INDEX].Pages.DA 			= BCM_NODE;
	ID[MSG22_INDEX].Pages.SA 			= TLM_NODE;
	TLM_MSG.Message22_ID = 	ID[MSG22_INDEX].identifier ;

	ID[MSG23_INDEX].Pages.priority 		= PRIORITY_111 ;
	ID[MSG23_INDEX].Pages.reserved 		= NOT_RESERVED ;
	ID[MSG23_INDEX].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[MSG23_INDEX].Pages.messageID 	= MESSAGE23 ;
	ID[MSG23_INDEX].Pages.DA 			= BCM_NODE;
	ID[MSG23_INDEX].Pages.SA 			= TLM_NODE;
	TLM_MSG.Message23_ID = 	ID[MSG23_INDEX].identifier ;


}


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

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))


	param->bxHandle.sFilterConfig.FilterFIFOAssignment 	= CAN_FILTER_FIFO0;
	param->bxHandle.sFilterConfig.FilterIdHigh			= 0;
	param->bxHandle.sFilterConfig.FilterIdLow			= 0;
	param->bxHandle.sFilterConfig.FilterMaskIdHigh		= 0;
	param->bxHandle.sFilterConfig.FilterMaskIdLow		= 0;
	param->bxHandle.sFilterConfig.FilterScale			= CAN_FILTERSCALE_32BIT;
	param->bxHandle.sFilterConfig.FilterActivation		= ENABLE;

	if( HAL_CAN_ConfigFilter(&param->bxHandle.hbxcanHandle, &param->bxHandle.sFilterConfig ) != HAL_OK )
	{
		return EEM_ERROR;
	}


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

	 /* MCP2515 Module specific filtering will patch later */

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
