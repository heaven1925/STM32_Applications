/************************ START OF FILE ***************************************/
/*******************************************************************************
* @file           : sys_lcd_public.c
* @brief          : Main module 
******************************************************************************
* @autors					: aertekin , cagatay-00 , quebrada
* @version				: v1.0.0
* @date						: 28.11.2022
******************************************************************************/
#include "stm32l4xx.h"
extern I2C_HandleTypeDef hi2c1;
#define SLAVE_ADDRESS_LCD 0x4E 

/*********************** INCLUDES **********************************************/


#include "sys_lcd_private.h"
#include "sys_lcd_public.h"
#include "sys_lcd_definition.h"

/*******************************************************************************
	 @func    :	sys_flash_init
	 @param   : void
	 @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	lcd init ayarlarini yapan fonksiyon.
********************************************************************************/
void sys_lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	sys_lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	sys_lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	sys_lcd_send_cmd (0x30);
	HAL_Delay(10);
	sys_lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	sys_lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	sys_lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	sys_lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	sys_lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	sys_lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

/*******************************************************************************
	 @func    :	sys_lcd_send_cmd
	 @param   : char cmd
	// @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	komutu lcd nin bagli oldugu cihaza gonderir
********************************************************************************/

void sys_lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*******************************************************************************
	 @func    :	sys_lcd_send_data
	 @param   : char
	 @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	verileri lcd nin bagli oldugu cihaza gonderir.
********************************************************************************/

void sys_lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*******************************************************************************
	 @func    :	sys_fclear
	 @param   : void
	 @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	lcd yi clear eder
********************************************************************************/
void sys_lcd_clear (void)
{
	sys_lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		sys_lcd_send_data (' ');
	}
}

/*******************************************************************************
	 @func    :	sys_lcd_put_cur
	 @param   : int row, ,nt col
	 @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	lcd satir ve sütun ayarlarini yapar.
********************************************************************************/

void sys_lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    sys_lcd_send_cmd (col);
}

/*******************************************************************************
	 @func    :	sys_send_string
	 @param   : char *str
	 @return  : err_t
	 @date	  : 23.09.2022
	 @INFO		:	diziyi lcd ye gondermek icin kullanilir.
********************************************************************************/
void sys_lcd_send_string (char *str)
{
	while (*str) sys_lcd_send_data (*str++);
}
