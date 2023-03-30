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

const	EEM_Protocol_opr_st	ops =
{
	EEM_INIT		,
	EEM_TX			,
	EEM_RX			,
	EEM_PUSH		,
	EEM_PULL		,
	EEM_RB_ISFULL 	,
	EEM_RB_ISEMPTY	,
	EEM_PERIODIC
};


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO	  :
********************************************************************************/
EEM_ERR_T EEM_INIT(  EEM_Protocol_obj_st*  param )
{
	EEM_ERR_T 			result = EEM_EOK;
	HAL_StatusTypeDef	status = HAL_OK;
	
#if defined(STM32F446xx)
	

	
	
#elif defined(STM32H750xx)
	
	param->fdHandle->hfdcanHandle.Instance = FDCAN1;
	param->fdHandle->hfdcanHandle.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	param->fdHandle->hfdcanHandle.Init.Mode = FDCAN_MODE_NORMAL;
	param->fdHandle->hfdcanHandle.Init.AutoRetransmission = ENABLE;
	param->fdHandle->hfdcanHandle.Init.TransmitPause = DISABLE;
	param->fdHandle->hfdcanHandle.Init.ProtocolException = DISABLE;
	param->fdHandle->hfdcanHandle.Init.NominalPrescaler = 12;
	param->fdHandle->hfdcanHandle.Init.NominalSyncJumpWidth = 1;
	param->fdHandle->hfdcanHandle.Init.NominalTimeSeg1 = 11;
	param->fdHandle->hfdcanHandle.Init.NominalTimeSeg2 = 2;
	param->fdHandle->hfdcanHandle.Init.DataPrescaler = 1;
	param->fdHandle->hfdcanHandle.Init.DataSyncJumpWidth = 1;
	param->fdHandle->hfdcanHandle.Init.DataTimeSeg1 = 1;
	param->fdHandle->hfdcanHandle.Init.DataTimeSeg2 = 1;
	param->fdHandle->hfdcanHandle.Init.MessageRAMOffset = 0;
	param->fdHandle->hfdcanHandle.Init.StdFiltersNbr = 1;
	param->fdHandle->hfdcanHandle.Init.ExtFiltersNbr = 0;
	param->fdHandle->hfdcanHandle.Init.RxFifo0ElmtsNbr = 0;
	param->fdHandle->hfdcanHandle.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
	param->fdHandle->hfdcanHandle.Init.RxFifo1ElmtsNbr = 0;
	param->fdHandle->hfdcanHandle.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
	param->fdHandle->hfdcanHandle.Init.RxBuffersNbr = 0;
	param->fdHandle->hfdcanHandle.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
	param->fdHandle->hfdcanHandle.Init.TxEventsNbr = 0;
	param->fdHandle->hfdcanHandle.Init.TxBuffersNbr = 0;
	param->fdHandle->hfdcanHandle.Init.TxFifoQueueElmtsNbr = 24;
	param->fdHandle->hfdcanHandle.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
	param->fdHandle->hfdcanHandle.Init.TxElmtSize = FDCAN_DATA_BYTES_8;

	status = HAL_FDCAN_Init(&param->fdHandle->hfdcanHandle);
	if(status != HAL_OK) return EEM_ERR;

	param->fdHandle->sFilterConfig.IdType = FDCAN_STANDARD_ID ;
	param->fdHandle->sFilterConfig.FilterIndex = 0;
	param->fdHandle->sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	param->fdHandle->sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0_HP;
	param->fdHandle->sFilterConfig.FilterID1 = 0x00 ;
	param->fdHandle->sFilterConfig.FilterID2 = 0x00 ;
	param->fdHandle->sFilterConfig.RxBufferIndex = 0;

	status = HAL_FDCAN_ConfigFilter(&param->fdHandle->hfdcanHandle ,
									&param->fdHandle->sFilterConfig);
	if(status != HAL_OK) return EEM_ERR;

	status = HAL_FDCAN_Start(&param->fdHandle->hfdcanHandle);
	if(status != HAL_OK) return EEM_ERR;

	status = HAL_FDCAN_ActivateNotification(&param->fdHandle->hfdcanHandle   ,
											FDCAN_IT_RX_FIFO0_NEW_MESSAGE |
											FDCAN_IT_TX_EVT_FIFO_NEW_DATA    ,
											0								 );
	if(status != HAL_OK) return EEM_ERR;

	/* Tx Header Main Configuration */
	param->fdHandle->txHeader.Identifier 			= EEM_TEST_ID 			;
	param->fdHandle->txHeader.IdType                = FDCAN_EXTENDED_ID     ;
	param->fdHandle->txHeader.TxFrameType           = FDCAN_DATA_FRAME      ;
	param->fdHandle->txHeader.DataLength            = FDCAN_DLC_BYTES_8     ;
	param->fdHandle->txHeader.ErrorStateIndicator   = FDCAN_ESI_ACTIVE      ;
	param->fdHandle->txHeader.BitRateSwitch         = FDCAN_BRS_OFF         ;
	param->fdHandle->txHeader.FDFormat              = FDCAN_CLASSIC_CAN     ;
	param->fdHandle->txHeader.TxEventFifoControl    = FDCAN_STORE_TX_EVENTS ;
	param->fdHandle->txHeader.MessageMarker         = 0                     ;

	/* Tx Test Message */
	volatile char testData[ EEM_MAX_SIZE ] =
	{
			'V'					,
			'E'             	,
			'R'             	,
	   (char)EEM_VERSION   		,
			'.'             	,
	   (char)EEM_SUBVERSION		,
			'.'             	,
	   (char)EEM_REVISION
	};

	status = HAL_FDCAN_AddMessageToTxFifoQ( &param->fdHandle->hfdcanHandle	,
											&param->fdHandle->txHeader		,
											(EEM_U8*)&testData[0]			);

#endif

	/* Clear ring buffer first */
	memset( &param->ringBuffer.data[0] 	,
			EEM_NULL			   		,
			EEM_BUFFER_SIZE		   		);

	param->ringBuffer.head = 0x00 ;
	param->ringBuffer.tail = 0x00 ;







	return result;
}

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
static EEM_ERR_T  EEM_PUSH( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* source)
{
	EEM_ERR_T result = EEM_EOK;
	
	if( EEM_TRUE == EEM_RB_ISFULL(ringBuf) )
	{
		/* If ring buffer is full must not push return ERR */
		return EEM_ERR;
	}
	else
	{
		memcpy( &ringBuf->data[ ringBuf->head ][0]  ,
				&source->DATA[0]					,
				EEM_MAX_SIZE						);

		ringBuf->extended_ID[ ringBuf->head ] = source ->EXTENDED_ID.main ;
		ringBuf->byte_count ++ ;

		ringBuf->head = ( ( ringBuf->head + 1 ) % EEM_BUFFER_SIZE );

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
static EEM_ERR_T	EEM_PULL( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* destination)
{
	EEM_ERR_T result = EEM_EOK;

	if( EEM_TRUE == EEM_RB_ISEMPTY(ringBuf) )
	{
		/* If ring buffer is empty must not pull return ERR */
		result = EEM_ERR;
	}
	else
	{
		memcpy( &destination->DATA[0]  				,
				&ringBuf->data[ ringBuf->head ][0]	,
				EEM_MAX_SIZE						);

		ringBuf->extended_ID[ ringBuf->head ] = destination->EXTENDED_ID.main;
		ringBuf->byte_count ++ ;

		ringBuf->tail = ( ( ringBuf->tail + 1 ) % EEM_BUFFER_SIZE );

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
EEM_ERR_T 		EEM_TX( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf )
{
	EEM_ERR_T result = EEM_EOK;
	HAL_StatusTypeDef status = HAL_OK;
	EEM_CAN_Packet_st	txHandle = {0};

	txHandle.EXTENDED_ID.main = param->fdHandle->txHeader.Identifier;
	memcpy( &txHandle.DATA[0]  , &param->txData[0] , EEM_MAX_SIZE );

	result = EEM_PUSH(ringBuf , &txHandle);
	if(result != EEM_EOK) return EEM_ERR;
	
#if defined(STM32F446xx)
	

	

#elif defined(STM32H750xx)
	/* Tx Header Main Configuration */
	status = HAL_FDCAN_AddMessageToTxFifoQ( &param->fdHandle->hfdcanHandle ,
											&param->fdHandle->txHeader	   ,
											&txHandle.DATA[0]			   );
	if(status != HAL_OK ) return EEM_ERR;

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
EEM_ERR_T 		EEM_RX( EEM_Protocol_obj_st* param, EEM_RING_Buffer_st* ringBuf )
{
	EEM_ERR_T 		  result = EEM_EOK;
	HAL_StatusTypeDef status = HAL_OK;

	EEM_CAN_Packet_st	rxHandle = {0};

#if defined(STM32F446xx)


	
	
#elif defined(STM32H750xx)
	
	status = HAL_FDCAN_GetRxMessage( &param->fdHandle->hfdcanHandle	,
									 FDCAN_RX_FIFO0					,
									 &param->fdHandle->rxHeader 	,
									 &param->rxData[0]				);
	if(status != HAL_OK ) return EEM_ERR;

	rxHandle.EXTENDED_ID.main = param->fdHandle->rxHeader.Identifier ;

#endif

	memcpy( &rxHandle.DATA[0] , &param->rxData[0] , EEM_MAX_SIZE );

	result = EEM_PULL( ringBuf, &rxHandle  );
	if( result != EEM_EOK ) return EEM_ERR;


	return result;
}




/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO    :
********************************************************************************/
static EEM_BOOL_T	EEM_RB_ISFULL( EEM_RING_Buffer_st* ringBuf )
{
	EEM_BOOL_T status = EEM_TRUE;

	if( ( (ringBuf->head + 1) % EEM_BUFFER_SIZE ) == ringBuf->tail )
	{
		status = EEM_TRUE;
	}
	else
	{
		status = EEM_FALSE;
	}

	return status;
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO	  :
********************************************************************************/
static EEM_BOOL_T	EEM_RB_ISEMPTY( EEM_RING_Buffer_st* ringBuf )
{
	EEM_BOOL_T status = EEM_TRUE;

	if( ringBuf->head == ringBuf->tail )
	{
		status = EEM_TRUE;
	}
	else
	{
		status = EEM_FALSE;
	}

	return status;

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
EEM_ERR_T 		EEM_PERIODIC( void* param )
{
	EEM_ERR_T result = EEM_EOK;

#if defined(STM32F446xx)




#elif defined(STM32H750xx)



#endif


	return result;
}

