/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#include "EEMProtocol.h"
#include "EEMProtocol_Config.h"

const	EEM_Protocol_opr_st		ops = 
{
	EEM_INIT		,
	EEM_TX			,
	EEM_RX
};

	BCM_Module_st	BCM_MSG;
/* HVAC module has been written Cpp language in order to arduino framework */
/* Simple computer protocol has written pyhton language */
	BMS_Module_st	BMS_MSG;
	MS1_Module_st	MS1_MSG;
	MS2_Module_st	MS2_MSG;
	ISO_Module_st	ISO_MSG;
	TLM_Module_st	TLM_MSG;
	YSB_Module_st	YSB_MSG;


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T EEM_INIT( EEM_Protocol_obj_st*  param )
{
	
	EEM_ERR_T result = EEM_EOK;

/* Ring Buffer Init Sequance */

	param->ringBuffer.head = 0;
	param->ringBuffer.tail = 0;
	param->ringBuffer.full = EEM_FALSE;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
	
	
	
	
	
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
	/*@NOTICE: All Configs for 42MHz CAN BASE CLOCK */

	param->fdHandle.hfdcanHandle.Instance 					= FDCAN1;
	param->fdHandle.hfdcanHandle.Init.FrameFormat 			= FDCAN_FRAME_CLASSIC;
	param->fdHandle.hfdcanHandle.Init.Mode 					= FDCAN_MODE_NORMAL;
	param->fdHandle.hfdcanHandle.Init.AutoRetransmission 	= ENABLE;
	param->fdHandle.hfdcanHandle.Init.TransmitPause 		= DISABLE;
	param->fdHandle.hfdcanHandle.Init.ProtocolException 	= DISABLE;
	param->fdHandle.hfdcanHandle.Init.NominalPrescaler 		= 12;
	param->fdHandle.hfdcanHandle.Init.NominalSyncJumpWidth 	= 1;
	param->fdHandle.hfdcanHandle.Init.NominalTimeSeg1 		= 11;
	param->fdHandle.hfdcanHandle.Init.NominalTimeSeg2 		= 2;
	param->fdHandle.hfdcanHandle.Init.DataPrescaler 		= 1;
	param->fdHandle.hfdcanHandle.Init.DataSyncJumpWidth 	= 1;
	param->fdHandle.hfdcanHandle.Init.DataTimeSeg1 			= 1;
	param->fdHandle.hfdcanHandle.Init.DataTimeSeg2 			= 1;
	param->fdHandle.hfdcanHandle.Init.MessageRAMOffset 		= 0;
	param->fdHandle.hfdcanHandle.Init.StdFiltersNbr 		= 0;
#if 	defined(BCM_MODULE)
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 7;
#elif	defined( HVAC_MODULE )
/* HVAC module protocol has been written cpp language in order to arduino framework */
#elif	defined( SCB_MODULE )
/* Simple computer protocol has been written pyhton language */
#elif	defined( BMS_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 2;
#elif	defined( MS1_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( MS2_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( ISO_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( TLM_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#else
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1; //@INFO: Tüm can paketleri alınır.
#endif
	param->fdHandle.hfdcanHandle.Init.RxFifo0ElmtsNbr 		= 1;
	param->fdHandle.hfdcanHandle.Init.RxFifo0ElmtSize 		= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.RxFifo1ElmtsNbr 		= 0;
	param->fdHandle.hfdcanHandle.Init.RxFifo1ElmtSize 		= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.RxBuffersNbr 			= 1;
	param->fdHandle.hfdcanHandle.Init.RxBufferSize 			= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.TxEventsNbr 			= 0;
	param->fdHandle.hfdcanHandle.Init.TxBuffersNbr 			= 0;
	param->fdHandle.hfdcanHandle.Init.TxFifoQueueElmtsNbr 	= 24;
	param->fdHandle.hfdcanHandle.Init.TxFifoQueueMode 		= FDCAN_TX_FIFO_OPERATION;
	param->fdHandle.hfdcanHandle.Init.TxElmtSize 			= FDCAN_DATA_BYTES_8;
	if (HAL_FDCAN_Init(&param->fdHandle.hfdcanHandle) != HAL_OK)
	{
		return EEM_ERROR;
	}
#else

#if defined(SPI2CAN_Protocol)

	EEM_U8 ret;

	ret = CANSPI_Initialize();
	if( ret < 0 )
	{
		return EEM_ERROR;
	}

#else

#endif

#endif

#if defined(BCM_MODULE)
	if( EEM_FILTER_BCM( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( HVAC_MODULE )
	/* HVAC module has been written Cpp language in order to arduino framework */
#elif	defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif	defined( BMS_MODULE )
	if( EEM_FILTER_BMS( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( MS1_MODULE )
	if( EEM_FILTER_MS1( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( MS2_MODULE )
	if( EEM_FILTER_MS2( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( ISO_MODULE )
	if( EEM_FILTER_ISO( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( TLM_MODULE )
	if( EEM_FILTER_TLM( param ) != EEM_EOK ) return EEM_ERROR;
#else
	/* No Filter */
#endif


#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))





#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	/* Configure global filter to reject all non-matching frames */
	 HAL_FDCAN_ConfigGlobalFilter(&param->fdHandle.hfdcanHandle, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

	if(HAL_FDCAN_Start(&param->fdHandle.hfdcanHandle)!= HAL_OK)
	{
		return EEM_ERROR;
	}

	if (HAL_FDCAN_ActivateNotification(&param->fdHandle.hfdcanHandle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE
																	   , 0) != HAL_OK)
	{
		return EEM_ERROR;
	}

	/* TEST MESSAGE FOR CAN LINE */
	/*******************************************************************************/
	FDCAN_TxHeaderTypeDef   TestTxHeader;
	EEM_U8               	TestTxData[8] = { 0xEE , EEM_VERSION , 0xEE , EEM_SUBVERSION , 0xEE , EEM_REVISION , 0xEE , 0xEE};
	TestTxHeader.Identifier 			= 0x65D;
	TestTxHeader.IdType 				= FDCAN_STANDARD_ID;
	TestTxHeader.TxFrameType 			= FDCAN_DATA_FRAME;
	TestTxHeader.DataLength 			= FDCAN_DLC_BYTES_8;
	TestTxHeader.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
	TestTxHeader.BitRateSwitch	 		= FDCAN_BRS_OFF;
	TestTxHeader.FDFormat 				= FDCAN_CLASSIC_CAN;
	TestTxHeader.TxEventFifoControl 	= FDCAN_STORE_TX_EVENTS;
	TestTxHeader.MessageMarker 			= 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&param->fdHandle.hfdcanHandle, &TestTxHeader, TestTxData)!= HAL_OK)
	{
		return EEM_ERROR;
	}
	/*******************************************************************************/
#else

#if defined(SPI2CAN_Protocol)

#else

#endif

#endif

	return result;
}



/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO	  :
********************************************************************************/
void   EEM_PUSH( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param)
{
	EEM_U8 loopVal = 0 ;

	for(loopVal = 0 ; loopVal < 8 ; loopVal++)
	{
		ringBuf->data[ ringBuf->tail ][ loopVal ] = param->DATA[ loopVal ];
	}
	ringBuf->id[ ringBuf->tail ].identifier = param->EXTENDED_ID.identifier;
	ringBuf->byte_count++;

	ringBuf->tail = ( ringBuf->tail + 1 ) % EEM_BUFFER_SIZE ;
	
	if( ringBuf->tail == ringBuf->head )
	{
		ringBuf->full = EEM_TRUE ;
	}
	
}



/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void	EEM_POP( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param)
{
	EEM_U8 loopVal = 0 ;

	for(loopVal = 0 ; loopVal <= 8 ; loopVal++)
	{
		param->DATA[ loopVal ] = ringBuf->data[ ringBuf->head ][ loopVal ];
	}
	param->EXTENDED_ID.identifier = ringBuf->id[ ringBuf->head ].identifier;
	ringBuf->byte_count++;
	
	ringBuf->head = (ringBuf->head + 1) % EEM_BUFFER_SIZE ;
	ringBuf->full = EEM_FALSE;


}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T 		EEM_TX( EEM_CAN_Packet_st* param, EEM_U32 period )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))


#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	memcpy( &protocol.obj.fdHandle.txData , &param->DATA[0] , EEM_MAX_SIZE );

	protocol.obj.fdHandle.txHeader.IdType 				= FDCAN_EXTENDED_ID 				;
	protocol.obj.fdHandle.txHeader.Identifier			= param->EXTENDED_ID.identifier		;
	protocol.obj.fdHandle.txHeader.TxFrameType			= FDCAN_DATA_FRAME			        ;
	protocol.obj.fdHandle.txHeader.DataLength			= FDCAN_DLC_BYTES_8			        ;
	protocol.obj.fdHandle.txHeader.BitRateSwitch 		= FDCAN_BRS_OFF				        ;
	protocol.obj.fdHandle.txHeader.FDFormat 			= FDCAN_CLASSIC_CAN			        ; //@BACK: Classic or FD format ?
	protocol.obj.fdHandle.txHeader.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS		        ;
	protocol.obj.fdHandle.txHeader.MessageMarker 		= 0							        ;

	
	if( HAL_FDCAN_AddMessageToTxFifoQ (&protocol.obj.fdHandle.hfdcanHandle  ,
									   &protocol.obj.fdHandle.txHeader		,
									    protocol.obj.fdHandle.txData			) != HAL_OK)
	{
		 	return EEM_ERROR;
	}
#else

#if defined(SPI2CAN_Protocol)

	uCAN_MSG txPacked;
	txPacked.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B ;
	txPacked.frame.dlc	  = EEM_MAX_SIZE;
	txPacked.frame.id	  = param->EXTENDED_ID.identifier;

	memcpy(&txPacked.frame.data0 , &param->DATA[0] , EEM_MAX_SIZE );

	CANSPI_Transmit(&txPacked);

#else

#endif

#endif
	
	



	return result;
}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/	
EEM_ERR_T 		EEM_RX( EEM_CAN_Packet_st* 	param 	  ,
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
						CAN_RxHeaderTypeDef   rxHeader	  ,
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
						FDCAN_RxHeaderTypeDef rxHeader    ,
#else
#if defined(SPI2CAN_Protocol)
						uCAN_MSG*			rxPacked      ,
#endif
#endif
						EEM_U8*				rxData	  	   )
{
	EEM_ERR_T result = EEM_EOK;

#if defined(STM32F446xx)



#elif defined(STM32H750xx)

	memcpy( &param->DATA[0] , &rxData[0] , EEM_MAX_SIZE );
	param->EXTENDED_ID.identifier = rxHeader.Identifier;

#else

#if defined(SPI2CAN_Protocol)

	//@That library used polling method
	if( CANSPI_Receive(rxPacked) )
	{
		memcpy(&param->DATA[0] , &rxPacked->frame.data0 , EEM_MAX_SIZE  );
		param->EXTENDED_ID.identifier = rxPacked->frame.id ;
	}
	else
	{
		return EEM_ERROR;
	}

#else

#endif

#endif

	/* Received Data Handled Push Ring Buffer */
	EEM_PUSH( &protocol.obj.ringBuffer , param);

	return result;
}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T 	EEM_PERIODIC( EEM_CAN_Packet_st*  param )
{
	EEM_ERR_T 	   result 	= EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol)) || (defined(STM32H750xx) && defined(FDCAN_Protocol))
	//bxCAN ve FDCAN IRQ Handler'da recv yapmaktadir.
#else

	uCAN_MSG rxHandle = {0};

	result = EEM_RX(param, &rxHandle, NULL);
	if( result != EEM_EOK ) return result;

#endif

	while( !EEM_IS_EMPTY(&protocol.obj.ringBuffer) )
	{
	   EEM_POP(&protocol.obj.ringBuffer, param);

#ifdef DEBUG_EN
	    printf("ID : %X" , param->EXTENDED_ID );
		printf("%02 %02 %02 %02 %02 %02 %02 %02 \n" , param->DATA[0] ,
					                                  param->DATA[1] ,
		                                              param->DATA[2] ,
		                                              param->DATA[3] ,
		                                              param->DATA[4] ,
		                                              param->DATA[5] ,
		                                              param->DATA[6] ,
		                                              param->DATA[7] ,
		                                              param->DATA[0] );
#endif
	}

	
	switch( param->EXTENDED_ID.Pages.messageID )
	{
//#if defined(BCM_MODULE)

	case MESSAGE01 :

		BCM_MSG.Message01.SPN.HVAC_led01_u1 = ( param->DATA[0] & 0x01 );
		BCM_MSG.Message01.SPN.HVAC_led02_u1 = (( param->DATA[0] & 0x02 ) >> 1 );
		BCM_MSG.Message01.SPN.HVAC_led03_u1 = (( param->DATA[0] & 0x04 ) >> 2 );
		BCM_MSG.Message01.SPN.HVAC_led04_u1 = (( param->DATA[0] & 0x08 ) >> 3 );
		BCM_MSG.Message01.SPN.HVAC_led05_u1 = (( param->DATA[0] & 0x10 ) >> 4 );
		BCM_MSG.Message01.SPN.HVAC_led06_u1 = (( param->DATA[0] & 0x20 ) >> 5 );
		BCM_MSG.Message01.SPN.HVAC_led07_u1 = (( param->DATA[0] & 0x40 ) >> 6 );
		BCM_MSG.Message01.SPN.HVAC_led08_u1 = (( param->DATA[0] & 0x80 ) >> 7 );
		BCM_MSG.Message01.SPN.HVAC_led09_u1 = ( param->DATA[1] & 0x01 );
		BCM_MSG.Message01.SPN.HVAC_led10_u1 = (( param->DATA[1] & 0x02 ) >> 1 );
		BCM_MSG.Message01.SPN.HVAC_led11_u1 = (( param->DATA[1] & 0x04 ) >> 2 );
		BCM_MSG.Message01.SPN.HVAC_led12_u1 = (( param->DATA[1] & 0x08 ) >> 3 );

		BCM_MSG.Message01.SPN.HVAC_pressureVal_u8 	= (EEM_U8)( (EEM_U8)( (param->DATA[1] & 0xF0) >> 4 )  |
												   	    		(EEM_U8)( (param->DATA[2] & 0x0F) << 4 )  );

		BCM_MSG.Message01.SPN.HVAC_indoorTempVal_u8 = (EEM_U8)( (EEM_U8)( (param->DATA[2] & 0xF0) >> 4 ) |
													 			(EEM_U8)( (param->DATA[3] & 0x0F) << 4 ) );

		BCM_MSG.Message01.SPN.HVAC_indoorHumidVal_u8 = (EEM_U8)( (EEM_U8)( (param->DATA[3] & 0xF0) >> 4 ) |
				 	 	 	 	 	 	 	 	 	 	  		(EEM_U8)( (param->DATA[4] & 0x0F) << 4 ) );

		BCM_MSG.Message01.SPN.HVAC_rtcCalib_u1 			= (EEM_U8)( ( param->DATA[4] & 0x10) >> 4 );
		BCM_MSG.Message01.SPN.HVAC_rtcNewSecond_u8 		= (EEM_U8)( ( param->DATA[4] & 0x20) >> 5 );
		BCM_MSG.Message01.SPN.HVAC_rtcNewMinutes_u8 	= (EEM_U8)( ( param->DATA[4] & 0x40) >> 6 );
		BCM_MSG.Message01.SPN.HVAC_rtcNewHour_u8 		= (EEM_U8)( ( param->DATA[4] & 0x80) >> 7 );
		BCM_MSG.Message01.SPN.HVAC_rtcNewDay_u8 		= (EEM_U8)(   param->DATA[5] & 0x01 );
		BCM_MSG.Message01.SPN.HVAC_rtcNewMonth_u8 		= (EEM_U8)( ( param->DATA[5] & 0x02 ) >> 1 );


	break;

	case MESSAGE02 :


		BCM_MSG.Message02.SPN.HVAC_fireVal				= (EEM_U8)( param->DATA[0] & 0x0F );
		BCM_MSG.Message02.SPN.HVAC_smokeVal 			= (EEM_U8)(( param->DATA[0] & 0xF0 ) >> 4 );

		BCM_MSG.Message02.SPN.HVAC_windPressure1 		= ( param->DATA[0] );
		BCM_MSG.Message02.SPN.HVAC_windPressure2 		= ( param->DATA[1] );
		BCM_MSG.Message02.SPN.HVAC_leftFrontWheel_xy 	= ( param->DATA[2] );
		BCM_MSG.Message02.SPN.HVAC_rightFrontWheel_xy 	= ( param->DATA[3] );
		BCM_MSG.Message02.SPN.HVAC_status00_u1 	        = ( param->DATA[4] & 0x01 );
		BCM_MSG.Message02.SPN.HVAC_status01_u1 	        = (( param->DATA[4] & 0x02 ) >> 1 );
		BCM_MSG.Message02.SPN.HVAC_status02_u1 	        = (( param->DATA[4] & 0x04 ) >> 2 );
		BCM_MSG.Message02.SPN.HVAC_status03_u1 	        = (( param->DATA[4] & 0x08 ) >> 3 );
		BCM_MSG.Message02.SPN.HVAC_status04_u1 	        = (( param->DATA[4] & 0x10 ) >> 4 );
		BCM_MSG.Message02.SPN.HVAC_status05_u1 	        = (( param->DATA[4] & 0x20 ) >> 5 );
		BCM_MSG.Message02.SPN.HVAC_status06_u1 	        = (( param->DATA[4] & 0x40 ) >> 6 );
		BCM_MSG.Message02.SPN.HVAC_status07_u1 	        = (( param->DATA[4] & 0x80 ) >> 7 );
		BCM_MSG.Message02.SPN.HVAC_Hgear_cmd 		    = (  param->DATA[5] & 0x07 );
		BCM_MSG.Message02.SPN.HVAC_Gear_cmd 		    = (( param->DATA[5] & 0x18 ) >> 3 );
		BCM_MSG.Message02.SPN.HVAC_cmdbit05_u1 	        = (( param->DATA[5] & 0x20 ) >> 5 );
		BCM_MSG.Message02.SPN.HVAC_cmdbit06_u1 	        = (( param->DATA[5] & 0x40 ) >> 6 );
		BCM_MSG.Message02.SPN.HVAC_cmdbit07_u1 	        = (( param->DATA[5] & 0x80 ) >> 7 );



	break;

	case MESSAGE07 :

		BCM_MSG.Message07.SPN.MS1_rpm 		= param->DATA[0] ;

		BCM_MSG.Message07.SPN.MS1_voltage 	= (EEM_U32)((EEM_U32)( param->DATA[1]	    )	|
														(EEM_U32)( param->DATA[2] << 8  )   |
														(EEM_U32)( param->DATA[3] << 16 )   |
														(EEM_U32)( param->DATA[4] << 24 )   );


		BCM_MSG.Message07.SPN.MS1_current 	= (EEM_U16)((EEM_U16)( param->DATA[5]	    )	|
														(EEM_U16)( param->DATA[6] << 8  )   );

		BCM_MSG.Message07.SPN.MS1_temp 		= param->DATA[7] ;

	break;

	case MESSAGE08 :

		BCM_MSG.Message08.SPN.MS1_Speed  = (EEM_U32)((EEM_U32)( param->DATA[0]	     )	 |
													 (EEM_U32)( param->DATA[1] << 8  )   |
			                                         (EEM_U32)( param->DATA[2] << 16 )   |
			                                         (EEM_U32)( param->DATA[3] << 24 )   );

		BCM_MSG.Message08.SPN.MS1_Direction = (EEM_U32)( (EEM_U32)( param->DATA[4]	     )	 |
													 	 (EEM_U32)( param->DATA[5] << 8  )   |
														 (EEM_U32)( param->DATA[6] << 16 )   |
														 (EEM_U32)( param->DATA[7] << 24 )   );

	break;

	case MESSAGE09 :

		BCM_MSG.Message09.SPN.MS2_rpm 		= param->DATA[0] ;

		BCM_MSG.Message09.SPN.MS2_voltage 	= (EEM_U32)((EEM_U32)( param->DATA[1]	    )	|
														(EEM_U32)( param->DATA[2] << 8  )   |
														(EEM_U32)( param->DATA[3] << 16 )   |
														(EEM_U32)( param->DATA[4] << 24 )   );


		BCM_MSG.Message09.SPN.MS2_current 	= (EEM_U16)((EEM_U16)( param->DATA[5]	    )	|
														(EEM_U16)( param->DATA[6] << 8  )   );

		BCM_MSG.Message09.SPN.MS2_temp 		= param->DATA[7] ;

	break;

	case MESSAGE10 :

		BCM_MSG.Message10.SPN.MS2_Speed   = (EEM_U32)((EEM_U32)( param->DATA[0]	     )	  |
													  (EEM_U32)( param->DATA[1] << 8  )   |
			                                          (EEM_U32)( param->DATA[2] << 16 )   |
			                                          (EEM_U32)( param->DATA[3] << 24 )   );

		BCM_MSG.Message10.SPN.MS2_Direction  = (EEM_U32)( (EEM_U32)( param->DATA[4]	      )	  |
													 	  (EEM_U32)( param->DATA[5] << 8  )   |
														  (EEM_U32)( param->DATA[6] << 16 )   |
														  (EEM_U32)( param->DATA[7] << 24 )   );

	break;

	case MESSAGE18 :

		BCM_MSG.Message18.SPN.MS1_warningFlag01 =  ( param->DATA[0] & 0x01 );
		BCM_MSG.Message18.SPN.MS1_warningFlag02 = (( param->DATA[0] & 0x02 ) >> 1 );
		BCM_MSG.Message18.SPN.MS1_warningFlag03 = (( param->DATA[0] & 0x04 ) >> 2 );
		BCM_MSG.Message18.SPN.MS1_warningFlag04 = (( param->DATA[0] & 0x08 ) >> 3 );
		BCM_MSG.Message18.SPN.MS1_warningFlag05 = (( param->DATA[0] & 0x10 ) >> 4 );
		BCM_MSG.Message18.SPN.MS1_warningFlag06 = (( param->DATA[0] & 0x20 ) >> 5 );
		BCM_MSG.Message18.SPN.MS1_warningFlag07 = (( param->DATA[0] & 0x40 ) >> 6 );
		BCM_MSG.Message18.SPN.MS1_warningFlag08 = (( param->DATA[0] & 0x80 ) >> 7 );

		BCM_MSG.Message18.SPN.MS1_errorFlag01 =  ( param->DATA[1] & 0x01 );
		BCM_MSG.Message18.SPN.MS1_errorFlag02 = (( param->DATA[1] & 0x02 ) >> 1 );
		BCM_MSG.Message18.SPN.MS1_errorFlag03 = (( param->DATA[1] & 0x04 ) >> 2 );
		BCM_MSG.Message18.SPN.MS1_errorFlag04 = (( param->DATA[1] & 0x08 ) >> 3 );
		BCM_MSG.Message18.SPN.MS1_errorFlag05 = (( param->DATA[1] & 0x10 ) >> 4 );
		BCM_MSG.Message18.SPN.MS1_errorFlag06 = (( param->DATA[1] & 0x20 ) >> 5 );
		BCM_MSG.Message18.SPN.MS1_errorFlag07 = (( param->DATA[1] & 0x40 ) >> 6 );
		BCM_MSG.Message18.SPN.MS1_errorFlag08 = (( param->DATA[1] & 0x80 ) >> 7 );

		BCM_MSG.Message18.SPN.MS1_statusBit01 =  ( param->DATA[2] & 0x01 );
		BCM_MSG.Message18.SPN.MS1_statusBit02 = (( param->DATA[2] & 0x02 ) >> 1 );
		BCM_MSG.Message18.SPN.MS1_statusBit03 = (( param->DATA[2] & 0x04 ) >> 2 );
		BCM_MSG.Message18.SPN.MS1_statusBit04 = (( param->DATA[2] & 0x08 ) >> 3 );
		BCM_MSG.Message18.SPN.MS1_statusBit05 = (( param->DATA[2] & 0x10 ) >> 4 );
		BCM_MSG.Message18.SPN.MS1_statusBit06 = (( param->DATA[2] & 0x20 ) >> 5 );
		BCM_MSG.Message18.SPN.MS1_statusBit07 = (( param->DATA[2] & 0x40 ) >> 6 );
		BCM_MSG.Message18.SPN.MS1_statusBit08 = (( param->DATA[2] & 0x80 ) >> 7 );

		BCM_MSG.Message18.SPN.MS1_dummyByte01 = param->DATA[3];
		BCM_MSG.Message18.SPN.MS1_dummyByte02 = param->DATA[4];
		BCM_MSG.Message18.SPN.MS1_dummyByte03 = param->DATA[5];
		BCM_MSG.Message18.SPN.MS1_dummyByte04 = param->DATA[6];
		BCM_MSG.Message18.SPN.MS1_dummyByte04 = param->DATA[7];

	break;


	case MESSAGE19 :

		BCM_MSG.Message19.SPN.MS2_warningFlag01 =  ( param->DATA[0] & 0x01 );
		BCM_MSG.Message19.SPN.MS2_warningFlag02 = (( param->DATA[0] & 0x02 ) >> 1 );
		BCM_MSG.Message19.SPN.MS2_warningFlag03 = (( param->DATA[0] & 0x04 ) >> 2 );
		BCM_MSG.Message19.SPN.MS2_warningFlag04 = (( param->DATA[0] & 0x08 ) >> 3 );
		BCM_MSG.Message19.SPN.MS2_warningFlag05 = (( param->DATA[0] & 0x10 ) >> 4 );
		BCM_MSG.Message19.SPN.MS2_warningFlag06 = (( param->DATA[0] & 0x20 ) >> 5 );
		BCM_MSG.Message19.SPN.MS2_warningFlag07 = (( param->DATA[0] & 0x40 ) >> 6 );
		BCM_MSG.Message19.SPN.MS2_warningFlag08 = (( param->DATA[0] & 0x80 ) >> 7 );

		BCM_MSG.Message19.SPN.MS2_errorFlag01 =  ( param->DATA[1] & 0x01 );
		BCM_MSG.Message19.SPN.MS2_errorFlag02 = (( param->DATA[1] & 0x02 ) >> 1 );
		BCM_MSG.Message19.SPN.MS2_errorFlag03 = (( param->DATA[1] & 0x04 ) >> 2 );
		BCM_MSG.Message19.SPN.MS2_errorFlag04 = (( param->DATA[1] & 0x08 ) >> 3 );
		BCM_MSG.Message19.SPN.MS2_errorFlag05 = (( param->DATA[1] & 0x10 ) >> 4 );
		BCM_MSG.Message19.SPN.MS2_errorFlag06 = (( param->DATA[1] & 0x20 ) >> 5 );
		BCM_MSG.Message19.SPN.MS2_errorFlag07 = (( param->DATA[1] & 0x40 ) >> 6 );
		BCM_MSG.Message19.SPN.MS2_errorFlag08 = (( param->DATA[1] & 0x80 ) >> 7 );

		BCM_MSG.Message19.SPN.MS2_statusBit01 =  ( param->DATA[2] & 0x01 );
		BCM_MSG.Message19.SPN.MS2_statusBit02 = (( param->DATA[2] & 0x02 ) >> 1 );
		BCM_MSG.Message19.SPN.MS2_statusBit03 = (( param->DATA[2] & 0x04 ) >> 2 );
		BCM_MSG.Message19.SPN.MS2_statusBit04 = (( param->DATA[2] & 0x08 ) >> 3 );
		BCM_MSG.Message19.SPN.MS2_statusBit05 = (( param->DATA[2] & 0x10 ) >> 4 );
		BCM_MSG.Message19.SPN.MS2_statusBit06 = (( param->DATA[2] & 0x20 ) >> 5 );
		BCM_MSG.Message19.SPN.MS2_statusBit07 = (( param->DATA[2] & 0x40 ) >> 6 );
		BCM_MSG.Message19.SPN.MS2_statusBit08 = (( param->DATA[2] & 0x80 ) >> 7 );

		BCM_MSG.Message19.SPN.MS2_dummyByte01 = param->DATA[3];
		BCM_MSG.Message19.SPN.MS2_dummyByte02 = param->DATA[4];
		BCM_MSG.Message19.SPN.MS2_dummyByte03 = param->DATA[5];
		BCM_MSG.Message19.SPN.MS2_dummyByte04 = param->DATA[6];
		BCM_MSG.Message19.SPN.MS2_dummyByte04 = param->DATA[7];


	break;


//#elif defined(HVAC_MODULE)
/* HVAC module has been written Cpp language in order to arduino framework */
//#elif defined(SCB_MODULE)
	/* Simple computer protocol has written pyhton language */
//#elif defined(BMS_MODULE)

	case MESSAGE24 :

	break;

//#elif defined(MS1_MODULE)

	case MESSAGE20 :

		MS1_MSG.Message20.SPN.MS1_Speed   = (EEM_U32)((EEM_U32)( param->DATA[0]	      )	  |
				 	 	 	 	 	 	 	 	 	  (EEM_U32)( param->DATA[1] << 8  )   |
													  (EEM_U32)( param->DATA[2] << 16 )   |
													  (EEM_U32)( param->DATA[3] << 24 )   );
		MS1_MSG.Message20.SPN.MS1_Mode	  = param->DATA[4];
		MS1_MSG.Message20.SPN.MS1_SuddenBrake = (param->DATA[5] & 0x01 );
		//@INFO: RFU Bits
		MS1_MSG.Message20.SPN.MS1_otherflag02 = ( (param->DATA[5] & 0x02 ) >> 1 );
		MS1_MSG.Message20.SPN.MS1_otherflag03 = ( (param->DATA[5] & 0x04 ) >> 2 );
		MS1_MSG.Message20.SPN.MS1_otherflag04 = ( (param->DATA[5] & 0x08 ) >> 3 );
		MS1_MSG.Message20.SPN.MS1_otherflag05 = ( (param->DATA[5] & 0x10 ) >> 4 );
		MS1_MSG.Message20.SPN.MS1_otherflag06 = ( (param->DATA[5] & 0x20 ) >> 5 );
		MS1_MSG.Message20.SPN.MS1_otherflag07 = ( (param->DATA[5] & 0x40 ) >> 6 );
		MS1_MSG.Message20.SPN.MS1_otherflag08 = ( (param->DATA[5] & 0x80 ) >> 7 );

	break;

	case MESSAGE21 :

		MS1_MSG.Message21.SPN.MS1_dummy01  = (EEM_U32)((EEM_U32)( param->DATA[0]	   )   |
						 	 	 	 	 	 	 	   (EEM_U32)( param->DATA[1] << 8  )   |
													   (EEM_U32)( param->DATA[2] << 16 )   |
													   (EEM_U32)( param->DATA[3] << 24 )   );

		MS1_MSG.Message21.SPN.MS1_dummy02  = (EEM_U32)((EEM_U32)( param->DATA[0]	   )   |
						 	 	 	 	 	 	 	   (EEM_U32)( param->DATA[1] << 8  )   |
													   (EEM_U32)( param->DATA[2] << 16 )   |
													   (EEM_U32)( param->DATA[3] << 24 )   );

	break;

//#elif defined(MS2_MODULE)
	case MESSAGE22 :

		MS2_MSG.Message22.SPN.MS2_Speed   = (EEM_U32)((EEM_U32)( param->DATA[0]	      )	  |
				 	 	 	 	 	 	 	 	 	  (EEM_U32)( param->DATA[1] << 8  )   |
													  (EEM_U32)( param->DATA[2] << 16 )   |
													  (EEM_U32)( param->DATA[3] << 24 )   );
		MS2_MSG.Message22.SPN.MS2_Mode	  = param->DATA[4];
		MS2_MSG.Message22.SPN.MS2_SuddenBrake = (param->DATA[5] & 0x01 );
		//@INFO: RFU Bits
		MS2_MSG.Message22.SPN.MS2_otherflag02 = ( (param->DATA[5] & 0x02 ) >> 1 );
		MS2_MSG.Message22.SPN.MS2_otherflag03 = ( (param->DATA[5] & 0x04 ) >> 2 );
		MS2_MSG.Message22.SPN.MS2_otherflag04 = ( (param->DATA[5] & 0x08 ) >> 3 );
		MS2_MSG.Message22.SPN.MS2_otherflag05 = ( (param->DATA[5] & 0x10 ) >> 4 );
		MS2_MSG.Message22.SPN.MS2_otherflag06 = ( (param->DATA[5] & 0x20 ) >> 5 );
		MS2_MSG.Message22.SPN.MS2_otherflag07 = ( (param->DATA[5] & 0x40 ) >> 6 );
		MS2_MSG.Message22.SPN.MS2_otherflag08 = ( (param->DATA[5] & 0x80 ) >> 7 );

	break;

	case MESSAGE23 :

		MS2_MSG.Message23.SPN.MS2_dummy01  = (EEM_U32)((EEM_U32)( param->DATA[0]	   )   |
						 	 	 	 	 	 	 	   (EEM_U32)( param->DATA[1] << 8  )   |
													   (EEM_U32)( param->DATA[2] << 16 )   |
													   (EEM_U32)( param->DATA[3] << 24 )   );

		MS2_MSG.Message23.SPN.MS2_dummy02  = (EEM_U32)((EEM_U32)( param->DATA[0]	   )   |
						 	 	 	 	 	 	 	   (EEM_U32)( param->DATA[1] << 8  )   |
													   (EEM_U32)( param->DATA[2] << 16 )   |
													   (EEM_U32)( param->DATA[3] << 24 )   );

	break;

//#elif defined(ISO_MODULE)

//#elif defined(TLM_MODULE)

//#elif defined(YSB_MODULE)

	case MESSAGE25 :

	break;

//#else

//#endif
	}

	
	return result;
}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
EEM_BOOL_T	EEM_IS_EMPTY( const EEM_RING_Buffer_st* buffer )
{
	 return (buffer->head == buffer->tail && !buffer->full);
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
EEM_BOOL_T	EEM_IS_FULL( const EEM_RING_Buffer_st* buffer )
{
	  return buffer->full;
}







