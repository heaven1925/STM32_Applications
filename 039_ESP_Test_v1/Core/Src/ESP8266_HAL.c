/*
 * ESP8266_HAL.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Controllerstech
 */


#include "UartRingbuffer_multi.h"
#include "ESP8266_HAL.h"
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern int testVolt[6];
extern int testTemp[6];
extern int i;

extern char VoltVal_birler[6] ;
extern char VoltVal_ondabirler[6] ;
extern char VoltVal_yuzdebirler[6] ;

extern char TempVal_onlar[6] ;
extern char TempVal_birler[6]  ;
extern char TempVal_ondabirler[6] ;

#define wifi_uart &huart2
#define pc_uart &huart1



char buffer[20];

char *Basic_inclusion ="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css\" integrity=\"sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh\" crossorigin=\"anonymous\"><link rel=\"preconnect\" href=\"https://fonts.gstatic.com\"><link href=\"https://fonts.googleapis.com/css2?family=Electrolize&display=swap\" rel=\"stylesheet\">\n\
<style>.main{font-family: 'Electrolize', sans-serif;}</style><title>Batarya Yönetim Sistemi Arayüzü</title></head><body><div class=\"container-fluid bg-dark main\"><div class=\"row\"><div class=\"col-12 text-light bg-dark h1 p-5 border border-warning\"><center> <i>Batarya Yönetim Sistemi Online Durum Takip Ekranı</i>\</center>\n\</div></div></div><div class=\"container-fluid bg border border-warning bg-dark text-light\"><div class=\"row\"><div class=\"col-6\"><div class=\"row\"><div class=\"col-6\"><img class=\"col-12\" src=\"https://www.kisa.link/OuF2\" alt=\"\"></div><div class=\"col-6\">\n\
 <ol class=\"text-left h3\"><li>Hücre: 1.11 V </li><li>Hücre: 2.22 V </li><li>Hücre: 3.33 </li><li>Hücre: 4.44 V </li><li>Hücre: 5.55 V </li><li>Hücre: 6.66 V </li><li>Hücre: 7.77 V </li></ol></div></div></div><div class=\"col-6\"><div class=\"row\"><div class=\"col-6\"><img class=\"col-12\" src=\"https://www.kisa.link/OuP3\" alt=\"\"></div><div class=\"col-6\"><ol class=\"text-left h3\">\n\
<li>Hücre: 11.1  °C</li><li>Hücre: 22.2  °C </li><li>Hücre: 33.3  °C</li><li>Hücre: 44.4  °C </li><li>Hücre: 55.5  °C </li><li>Hücre: 66.6  °C </li><li>Hücre: 77.7  °C </li></ol></div></div></div></div></div></div></ol></div></div></div><div class=\"col-6\"><div class=\"row\"><div class=\"col-6\">></div><div class=\"col-6\"><ol class=\"text-left h3\">\n\
	" ;

// voltVal_i[3] = birler basamağı
// voltVal_i[5] = ondabirler basamağı
// voltVal_i[6] = ondayüzler basamağı

char voltVal_1[10]= { '<','p','>','0','.','0','0','<','/','p','>' }; // <p>x.xx</p>
char voltVal_2[10]= { '<','p','>','0','.','0','0','<','/','p','>' };
char voltVal_3[10]= { '<','p','>','0','.','0','0','<','/','p','>' };
char voltVal_4[10]= { '<','p','>','0','.','0','0','<','/','p','>' };
char voltVal_5[10]= { '<','p','>','0','.','0','0','<','/','p','>' };
char voltVal_6[10]= { '<','p','>','0','.','0','0','<','/','p','>' };
char voltVal_7[10]= { '<','p','>','0','.','0','0','<','/','p','>' };


// tempVal_i[3] = onlar basamağı
// tempVal_i[3] = onlar basamağı
// tempVal_i[6] = ondabirler basamağı

char tempVal_1[10]= { '<','p','>','0','0','.','0','<','/','p','>' }; // <p>x.xx</p>
char tempVal_2[10]= { '<','p','>','0','0','.','0','<','/','p','>' };
char tempVal_3[10]= { '<','p','>','0','0','.','0','<','/','p','>' };
char tempVal_4[10]= { '<','p','>','0','0','.','0','<','/','p','>' };
char tempVal_5[10]= { '<','p','>','0','0','.','0','<','/','p','>' };
char tempVal_6[10]= { '<','p','>','0','0','.','0','<','/','p','>' };
char tempVal_7[10]= { '<','p','>','0','0','.','0','<','/','p','>' };

char *Terminate = "</body></html>";



void valueDigit(void)
{
	for(i=0; i<=6; i++)
	{
		VoltVal_birler[i]=testVolt[i]/100 +48 ; // x.__
		VoltVal_ondabirler[i]=testVolt[i]/10%10 + 48 ; // _.x_
		VoltVal_yuzdebirler[i]=testVolt[i] %10  + 48 ; // _._x

		TempVal_onlar[i]=testTemp[i]/100 +48 ; // x.__
		TempVal_birler[i]=testTemp[i]/10%10 + 48 ; // _.x_
		TempVal_ondabirler[i]=testVolt[i] %10  + 48 ; // _._x
	}
}



/*****************************************************************************************************************************************/

void ESP_Init (char *SSID, char *PASSWD)
{
	char data[80];

	Ringbuf_init();

	Uart_sendstring("AT+RST\r\n", wifi_uart);
	Uart_sendstring("RESETTING.", pc_uart);
	for (int i=0; i<5; i++)
	{
		Uart_sendstring(".", pc_uart);
		HAL_Delay(1000);
	}

	/********* AT **********/
	Uart_sendstring("AT\r\n", wifi_uart);
	while(!(Wait_for("AT\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("AT---->OK\n\n", pc_uart);


	/********* AT+CWMODE=1 **********/
	Uart_sendstring("AT+CWMODE=1\r\n", wifi_uart);
	while (!(Wait_for("AT+CWMODE=1\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("CW MODE---->1\n\n", pc_uart);


	/********* AT+CWJAP="SSID","PASSWD" **********/
	Uart_sendstring("connecting... to the provided AP\n", pc_uart);
	sprintf (data, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
	Uart_sendstring(data, wifi_uart);
	while (!(Wait_for("WIFI GOT IP\r\n\r\nOK\r\n", wifi_uart)));
	sprintf (data, "Connected to,\"%s\"\n\n", SSID);
	Uart_sendstring(data,pc_uart);


	/********* AT+CIFSR **********/
	Uart_sendstring("AT+CIFSR\r\n", wifi_uart);
	while (!(Wait_for("CIFSR:STAIP,\"", wifi_uart)));
	// while (!(Copy_upto("\"",buffer, wifi_uart)));
	/*
	 *
	 while (!(Wait_for("OK\r\n", wifi_uart)));
	int len = strlen (buffer);
	buffer[len-1] = '\0';
	sprintf (data, "IP ADDR: %s\n\n", buffer);
	Uart_sendstring(data, pc_uart);
	 *
	 */


	Uart_sendstring("AT+CIPMUX=1\r\n", wifi_uart);
	while (!(Wait_for("AT+CIPMUX=1\r\r\n\r\nOK\r\n", wifi_uart)));
	Uart_sendstring("CIPMUX---->OK\n\n", pc_uart);

	Uart_sendstring("AT+CIPSERVER=1,80\r\n", wifi_uart);
	while (!(Wait_for("OK\r\n", wifi_uart)));
	Uart_sendstring("CIPSERVER---->OK\n\n", pc_uart);

	Uart_sendstring("Now Connect to the IP ADRESS\n\n", pc_uart);

}




int Server_Send (char *str, int Link_ID)
{
	int len = strlen (str);
	char data[80];
	sprintf (data, "AT+CIPSEND=%d,%d\r\n", Link_ID, len);
	Uart_sendstring(data, wifi_uart);
	while (!(Wait_for(">", wifi_uart)));
	Uart_sendstring (str, wifi_uart);
	while (!(Wait_for("SEND OK", wifi_uart)));
	sprintf (data, "AT+CIPCLOSE=5\r\n");
	Uart_sendstring(data, wifi_uart);
	while (!(Wait_for("OK\r\n", wifi_uart)));


}

void Server_Handle (char *str, int Link_ID)
{
	char datatosend[1024] = {0};

		sprintf (datatosend, Basic_inclusion);
		strcat(datatosend, Terminate);
		Server_Send(datatosend, Link_ID);




}

void Server_Start (void)
{
	char buftocopyinto[1024];
	char Link_ID;
	while (!(Get_after("+IPD,", 1, &Link_ID, wifi_uart)));
	Link_ID -= 48;
	while (!(Copy_upto(" HTTP/1.1", buftocopyinto, wifi_uart)));


	if (Look_for("<li>Hücre: 1.11 </li>", buftocopyinto) == 1)
		{

			Server_Handle(voltVal_1[10],Link_ID);
		}


	else if (Look_for("<li>Hücre: 2.22 </li>", buftocopyinto) == 1)
	{

		Server_Handle(voltVal_2[10],Link_ID);
	}

	else if (Look_for("<li>Hücre: 3.33 </li>", buftocopyinto) == 1)
	{

		Server_Handle(voltVal_3[10],Link_ID);
	}

	else if (Look_for("<li>Hücre: 4.44 </li>", buftocopyinto) == 1)
		{

			Server_Handle(voltVal_4[10],Link_ID);
		}
	else if (Look_for("<li>Hücre: 5.55 </li>", buftocopyinto) == 1)
		{

			Server_Handle(voltVal_5[10],Link_ID);
		}
	else if (Look_for("<li>Hücre: 6.66 </li>", buftocopyinto) == 1)
		{

			Server_Handle(voltVal_6[10],Link_ID);
		}
	else if (Look_for("<li>Hücre: 7.77 </li>", buftocopyinto) == 1)
		{

			Server_Handle(voltVal_7[10],Link_ID);
		}

	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		Server_Handle("/ ", Link_ID);
	}


	   valueDigit();

	  	 /*
	  	  *  for(i=0; i<=6 ; i++)
	  	  {
	  		  testVolt[i]+=5;
	  		  testTemp[i]+=1;
	  	  }

	  	  if(testVolt[0]=370 || testTemp[0]==500)
	  	  {
	  		  for(i=0; i<=6 ; i++)
	  		  	  {
	  		  		  testVolt[i]=0;
	  		  		  testTemp[i]=0;
	  		  	  }
	  	  }
	  	  */





}
