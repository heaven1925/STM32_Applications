/************************ START OF FILE ***************************************/
/*******************************************************************************
* @file           : sys_lcd_public.c
* @brief          : Main module 
******************************************************************************
* @autors					: aertekin , cagatay-00 , quebrada
* @version				: v1.0.0
* @date						: 28.11.2022
******************************************************************************/

#ifndef __SYS_LCD_PUBLIC__
#define __SYS_LCD_PUBLIC__


/*********************** INCLUDES **********************************************/
#include "sys_lcd_definition.h"

/******************** PUBLIC FUNCTION PROTOTYPE *********************************/	
extern err_t sys_lcd_writeMessage(uint8_t firstLineEnum  ,
													 uint8_t secondLineEnum ,
													 uint8_t* firstLineMsg	,
													 uint8_t* secondLineMsg	);


void sys_lcd_init (void);   // initialize lcd

void sys_lcd_send_cmd (char cmd);  // send command to the lcd

void sys_lcd_send_data (char data);  // send data to the lcd

void sys_lcd_send_string (char *str);  // send string to the lcd

void sys_lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void sys_lcd_clear (void);






































#endif /*__SYS_LCD_PUBLIC__*/

/*********************** END OF FILE ********************************************/

