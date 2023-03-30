/************************ START OF FILE ***************************************/
/*******************************************************************************
* @file           : sys_lcd_private.c
* @brief          : Main module 
******************************************************************************
* @autors					: aertekin , cagatay-00 , quebrada
* @version				: v1.0.0
* @date						: 28.11.2022
******************************************************************************/

#ifndef __SYS_LCD_PRIVATE__
#define __SYS_LCD_PRIVATE__


/*********************** INCLUDES **********************************************/

#include "sys_lcd_definition.h"
#include "sys_lcd_public.h"



/*********************** DEFINES ***********************************************/
#define		LCD_MESSAGE_TABLE_SIZE			7	//...

#define		SYS_MESSAGE_ROW							16
#define 	SYS_MESSAGE_COLUMN					2

#define		SYS_MESSAGE_SIZE						SYS_MESSAGE_ROW

enum {  
	ANGLE = 0     , 
	SPEED         ,
	DISTANCE      ,
	TIME          ,
	BATTERY_RATIO ,
	BATTERY_LIFE  ,
	RAM_DISTANCE
};



/********************** FUNCTION PROTOTYPE **************************************/	

err_t sys_lcd_writeMessage(uint8_t firstLineEnum  ,
													 uint8_t secondLineEnum ,
													 uint8_t* firstLineMsg	,
													 uint8_t* secondLineMsg	);



/************************ CONSOLE MSG TABLE ***********************************/	

const char sys_lcd_messageTable[LCD_MESSAGE_TABLE_SIZE][SYS_MESSAGE_SIZE] = {
	
	"DIREKSIYON ACISI" , /**<@INFO: Direksiyon açi bilgisini verir.                                        */
	"ARACIN HIZI     " , /**<@INFO: Aracin hiz bilgisini verir.                                            */
  "ALINAN YOL      " , /**<@INFO: Aracin aldigi yol bilgisini verir.                                     */	
	"GECEN SURE      " , /**<@INFO: Aracin harekete baslayip bulundugu durumda gecen süre bilgisini verir. */
	"SARJ YUZDESI    " , /**<@INFO: Kalan sarj yüzdesini verir.                                            */
	"SARJ OMRU       " , /**<@INFO: Bataryanin ne kadar süre gidecegi bilgisi verir.                       */
	"KALAN YOL       " , /**<@INFO: Parkurun bitmesine kaç km kaldigi bilgisini verir.                     */
	
	
};





































#endif /*__SYS_LCD_PRIVATE__*/

/*********************** END OF FILE ********************************************/
