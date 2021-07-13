/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h" // Ana dosya header file
#include "cmsis_os.h" // Dosya Sistemi kütüphaneleri
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "STM_MY_LCD16X2.h"	// 16x2 LCD Kütüphanesi

#include "fatfs_sd.h" // SD Kart kütüphaneleri

#include "math.h"  // Matematiksel işlem kütüphanesi


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;	// verilerin ölçüldüğü adc
DMA_HandleTypeDef hdma_adc1;	// kullanılan DMA

SPI_HandleTypeDef hspi3;	// SD Kart haberleşmesi

TIM_HandleTypeDef htim1;	// Servo için PWM
TIM_HandleTypeDef htim4;	// SD Kart için gerekli timer
TIM_HandleTypeDef htim5;	// RGB için PWM
TIM_HandleTypeDef htim7;	// Systick için timer

UART_HandleTypeDef huart1; // Konsol için UART
UART_HandleTypeDef huart3;	// 2. işlemciye veri aktarılması için UART


/* USER CODE BEGIN PV */

// default taskhandler her cubemx değiştiğinde silinecek !

int rgbDataRed=0;	// RGB Kırmızı Renk Değişkeni
int rgbDataBlue=0;	// RGB Mavi Renk Değişkeni
int rgbDataGreen=0;	// RGB Yeşil Renk Değişkeni

int adcValues[20]={};	// ADC Değerlerinin Tutulduğu Array - Raw data
int adcVal[8];		// Gerilim Değerlerinin tutuduğu Array
int adcValTemp[8];	// Sıcaklık Değerlerinin tutulduğu Array
int voltValue[8];	// 0-3.7V Arası gerilim değerleri
int tempValue[8];	// 15-90 *C Arası Sıcaklı değerleri
int blocktemp=0;	// Blok geriliminin tutulduğu yer
int j=0;	// Döngü değişkeni
int k=0;	// Döngü değişkeni

int tempAvgRgb=0;	// Rgb için ortalama sıcaklık değişkeni
double tempAvg=0;	// Ortalama sıcaklık
int tempDummy=0;	// Ortalama sıcaklık tutucusu


// SD CARD Definitions
double tmp=0; // Sd karta aktarılacak sıcaklık değişeni
int tempIntVal=0;	// Sd karta aktarılacak değişken int formatı

char buffer[100]={}; // Sd kartta kullanılacak buffer
int i=0;	// Döngü değişkeni

int servoAngle=0;	// Servo motor başlangıç açısı

int sayi[7] = { 111 , 222 ,333 ,444 ,555,666,777}; // Test Arrayi

char birlerDigit[7] ;	// Birler basamağı değerleri
char onlarDigit[7] ;	// Onlar basamağı değerleri
char yuzlerDigit[7] ;	// Yüzler basamağı değerleri
char cellNumber;	// Hücre numarası değişkeni

int balanceVoltage=0; // Dengeleme Voltajı değeri

int test=0;	// Test değişkeni

int menu;	// LCD Arayüz değişkeni
int ClearStatus=0;	// LCD Ekran temizleme bayrağı


int sdInt = 0;	// Sd kart button kesme değişkeni
int wifiInt = 0;	// wifi button kesme değişkeni
int  fanInt = 0;	// fan button kesme değişkeni
int startInt = 0;	// aç/kapa button kesme değişkeni

int sdlog = 0; // sürekli dosyalama yapmaması için
int wifilog = 0; // sürekli wifi aktif etmemesis için

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void Servo_Angle(int servoAngle)
{
	if(servoAngle<=0)	// girilen açı değeri 0 dan küçükse
	{
		servoAngle=0;   // servo motor 0 derece sabitlensin
	}
	if(servoAngle>=180) // girilen açı değeri 180 den büyükse
	{
		servoAngle=180; // servo motor 1800 derece sabitlensin
	}

	servoAngle=servoAngle+45;
	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,servoAngle);
	// diğer durumlar için CCR Registarına ilgili bilgi aktarılsın.

}

int balancingValue(int * sayi)
  {
  	int balanceVoltage=sayi[0];

  	for(int i=1;i<7;i++)
  	{
  	    if(sayi[i]<balanceVoltage)
  	    {
  	    	balanceVoltage=sayi[i];
  	    }
  	}

  	return balanceVoltage;
  }

void SD_Write(void)
  	  {

	sdlog++;

	Mount_SD("/");
	Format_SD();
	Create_File("ADC_DATA.TXT");
	Create_File("TEMP.TXT");

	while(i<=6)
	{
		birlerDigit[i] = sayi[i] % 10 + 48;
		onlarDigit[i] = sayi[i] / 10 % 10 + 48;
		yuzlerDigit[i] = sayi[i] /100 + 48;

		Update_File("ADC_DATA.TXT", "\n Hucre ");
		HAL_Delay(1);
		buffer[0] = i + 49 ;
		buffer[1] = '\0' ;

		Update_File("ADC_DATA.TXT", buffer);
		HAL_Delay(1);
		Update_File("ADC_DATA.TXT", " = ");
		HAL_Delay(1);

		buffer[0] = yuzlerDigit[i];


		Update_File("ADC_DATA.TXT", buffer);
		HAL_Delay(1);

		Update_File("ADC_DATA.TXT", ".");
		HAL_Delay(1);

		buffer[0] = onlarDigit[i];
		buffer[1] = birlerDigit[i];
		Update_File("ADC_DATA.TXT", buffer);
		HAL_Delay(1);

		Update_File("ADC_DATA.TXT", " V");
		HAL_Delay(1);

		i++;
	}

	Update_File("ADC_DATA.TXT", "\n Hucre Dengeleme Gerilimi : ");
	balanceVoltage = balancingValue(sayi);

	birlerDigit[i] = balanceVoltage % 10 + 48;
	onlarDigit[i] = balanceVoltage / 10 % 10 + 48;
	yuzlerDigit[i] = balanceVoltage /100 + 48;

	buffer[0] = yuzlerDigit[i];
	buffer[1] = '\0' ;

	Update_File("ADC_DATA.TXT", buffer);

	Update_File("ADC_DATA.TXT", ".");
	HAL_Delay(1);

	buffer[0] = onlarDigit[i];
	buffer[1] = birlerDigit[i];

	Update_File("ADC_DATA.TXT", buffer);
	HAL_Delay(1);


     i=0;
	while(i<=6)
	{
		birlerDigit[i] = sayi2[i] % 10 + 48;
		onlarDigit[i] = sayi2[i] / 10 % 10 + 48;
		yuzlerDigit[i] = sayi2[i] /100 + 48;

		Update_File("TEMP.TXT", "\n Temp ");
		HAL_Delay(1);
		buffer[0] = i + 49 ;
		buffer[1] = '\0' ;

		Update_File("TEMP.TXT", buffer);
		HAL_Delay(1);
		Update_File("TEMP.TXT", " = ");
		HAL_Delay(1);

		buffer[0] = yuzlerDigit[i];
		buffer[1] = onlarDigit[i];

		Update_File("TEMP.TXT", buffer);
		HAL_Delay(1);

		Update_File("TEMP.TXT", ".");
		HAL_Delay(1);


		buffer[0] = birlerDigit[i];
		Update_File("TEMP.TXT", buffer);
		HAL_Delay(1);

		Update_File("TEMP.TXT", " C");
		HAL_Delay(1);

		i++;
	}


	Update_File("TEMP.TXT", "\n Ortalama Sıcaklık : ");

	for(i=0;i<=6;i++)
	{
		temperatureAvg+=sayi2[i];
	}
	temperatureAvg/=7;

	birlerDigit[i] = temperatureAvg % 10 + 48;
	onlarDigit[i] = temperatureAvg / 10 % 10 + 48;
	yuzlerDigit[i] = temperatureAvg /100 + 48;

	buffer[0] = yuzlerDigit[i];
	buffer[1] = onlarDigit[i];
	buffer[2] = '\0' ;

	Update_File("TEMP.TXT", buffer);

	Update_File("TEMP.TXT", ".");
	HAL_Delay(1);


	buffer[0] = birlerDigit[i];

	Update_File("TEMP.TXT", buffer);
	HAL_Delay(1);

	Unmount_SD("/");


  	  }

void set_rgb (uint8_t red,uint8_t blue,uint8_t green)
{
	htim4.Instance->CCR1=red;
	htim4.Instance->CCR2=blue;
	htim4.Instance->CCR3=green;
}

void rgbCommand(void)
{
	if( tempAvg>=500 || tempValue[0]>=500
				|| tempValue[1]>=500 || tempValue[2]>=500 || tempValue[3]>=500
				|| tempValue[4]>=500 || tempValue[5]>=500 || tempValue[6]>=500 )
		{
			tempAvgRgb=255;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
			fanInt=1;
		}

	else
	{
		tempAvgRgb=(tempAvg-200)*255/300;
		if(tempAvgRgb<0)
		{
			tempAvgRgb=0;
		}
		fanInt=0;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
	}

	rgbDataRed=tempAvgRgb;  // 50 derecede 255
	rgbDataBlue=255-tempAvgRgb;	// 50 derecede 1

	set_rgb(rgbDataRed,rgbDataBlue,0);



}

void rgbAnimation(void)
{
	for(i=0;i<=255;i++)
	{
		set_rgb(i,255-i,0);
		for(j=0;j<=5000;j++);
	}
	for(i=0;i<=255;i++)
	{
		set_rgb(255-i,i,0);
		for(j=0;j<=5000;j++);
	}
	for(i=0;i<=255;i++)
		{
			set_rgb(0,255-i,i);
			for(j=0;j<=5000;j++);
		}
	for(i=0;i<=255;i++)
			{
				set_rgb(0,0,255-i);
				for(j=0;j<=5000;j++);
			}

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_TIM7_Init();
  MX_FATFS_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */


      HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
      HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
      HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

      HAL_TIM_Base_Start(&htim7);  // us delay timer
      HAL_TIM_Base_Start_IT(&htim1); // periodic delay timer


      // HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);

      LCD1602_Begin8BIT(RS_GPIO_Port, E_Pin, RS_Pin, D0_GPIO_Port, D0_Pin, D1_Pin, D2_Pin, D3_Pin, D4_GPIO_Port, D4_Pin, D5_Pin, D6_Pin, D7_Pin);

      		LCD1602_setCursor(1,1);
      		  LCD1602_print("BATTERY");
      		  LCD1602_setCursor(2,1);
      		  LCD1602_print("MANAGEMENT SYS");


      	// 3 ANGLE
      	// 6 FAN
      	// 1 TERMO
      	// 2 BATTERY
      	// 4 WIFI
      	// 5 SD
      	// 7 BELL

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1); // Normalde Servo PWM STOP

	  if(startInt==1)	// SİSTEM AKTİF
	  {

		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);	// YEŞİL LED ON
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);	// KIRMIZI LED OFF
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
		  if(sdInt==1)	// SD CARD Aktif dosyalama yapılıyor.
		  {
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			  // SD KART KESMESİ

			  	  	  	  LCD1602_setCursor(2,8);
			  			  LCD1602_writeData(5);

			  			  LCD1602_setCursor(2,9);
			  			  LCD1602_print("SD ON");
			  			  if(sdlog==0)
			  			  {
			  				Send_Uart("Dosyalama işlemi basliyor");
			  				SD_Write();
			  			  }
			  			  else
			  				 Send_Uart("Daha önce Dosyalama Yapildi");
		  }
		  else if(sdInt!=1 && wifiInt!=1) // SD ON ve WİFİ ON yazisini temizleme
		  		  {
		  			  LCD1602_setCursor(2,8);
		  			  LCD1602_print("        ");
		  		  }


		  if(wifiInt==1) // WIFI AKTIF UARTTAN VERİLER İLETİLİYOR.
		  {
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			  // WIFI KESMESI

			  LCD1602_setCursor(2,8);
			  LCD1602_writeData(4);

			  LCD1602_setCursor(2,9);
			  LCD1602_print("WIFI ON");

			  // UARTTAN VERİLER 2. İŞLEMCİYE İLETİLİYOOR

			  if(wifilog==0)
			  {
				  	  	  	  Send_Uart(birlerDigit);
				  			  Send_Uart(onlarDigit);
				  			  Send_Uart(yuzlerDigit);
			  }
			  else
			  {
				  Send_Uart("Daha önce Wifi Açıldı");
			  }


		  }


		  if(fanInt==1)	// FAN AKTİF VE SERVO VE DC MOTOR ÇALIŞIYOR
		  {
			  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET); // TRANSISTOR B'SINE GIDIYOR.
			  for(i=0;i<=180;i+=10)
			  {
				  Servo_Angle(i);
				  HAL_Delay(50);
			  }

			  for(i=180;i>=0;i-=10)
			  {
				  Servo_Angle(i);
				  				  HAL_Delay(50);
			  }

		  }
		  else
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);

		  	   if(ClearStatus==1)
		  	   {
		  		 LCD1602_clear();
		  	   }
		  	 ClearStatus=0;

		  	    LCD1602_setCursor(1,1);
		      	LCD1602_writeData(1);
		      	LCD1602_setCursor(1,6);
		      	LCD1602_print("V");
		      	LCD1602_setCursor(2,1);
		      	LCD1602_writeData(0);
		      	LCD1602_setCursor(2,6);
		      	LCD1602_writeData(2);

		      	LCD1602_setCursor(1,8);
		      	LCD1602_print("CELL NO:");
		      	LCD1602_noBlink();

		      	// VOLTAGE SENSOR READ


		      	HAL_ADC_Start(&hadc1);
		      	for(i=0; i<=14 ; i++)
		      	{
		      		HAL_ADC_PollForConversion(&hadc1, 50);
		      		adcValues[i]=HAL_ADC_GetValue(&hadc1);
		      	}
		      	HAL_ADC_Stop(&hadc1);


		      	for(i=0; i<=6 ; i++)
		      	{
		      		voltValue[i]=adcValues[i]*370/4095;
		      	}

		      	for(i=0; i<=7 ; i++)
		      	{

		      			tempDummy=adcValues[i+7];

		      			if(tempDummy<=0)
		      			{
		      				tmp=0;
		      			}
		      			else
		      			{
		      				tmp = log(((40950000 / tempDummy) - 10000));
		      						      			tmp = 1 / (0.001129148 + (0.000234125 + (		0.0000000876741 * tmp * tmp)) * tmp);
		      						      			tmp = tmp - 278.15;
		      			}
	   			tempValue[i]=tmp*10;

		      		}

		      	blocktemp = tempValue[7]*10;
		      			      		tempValue[2]-=190;

		      		for(i=0;i<=6;i++)
		      		{
		      			tempAvg += tempValue[i];
		      		}
		      		tempAvg=tempAvg/7.0;



		      		rgbCommand();



		  	  // MAIN LOOP



		  	  switch(menu)
		  	  {
		  	  case 0:
		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[0]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[0]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(1);


		  		  LCD1602_setCursor(2,2);
		  		  LCD1602_PrintInt(tempValue[0]/1);
		  		  LCD1602_setCursor(2,4);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(2,5);
		  		  tempIntVal=tempValue[0];
		  		  tempIntVal %= 10;
		  		  LCD1602_PrintInt(tempIntVal);
		  		LCD1602_noBlink();


		  		  break;
		  	  case 1:
		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[1]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[1]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(2);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[1]/1);
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[1];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();
		  		  break;
		  	  case 2:

		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[2]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[2]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(3);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[2]/1);
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[2];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();
		  		  break;
		  	  case 3:


		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[3]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[3]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(4);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[3]/1);
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[3];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();
		  		  break;
		  	  case 4:


		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[4]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[4]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(5);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[4]/1);
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[4];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();
		  		  break;
		  	  case 5:

		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[5]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[5]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(6);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[5]/1 - 10);
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[5];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();

		  		  break;
		  	  case 6:

		  		  LCD1602_setCursor(1,2);
		  		  LCD1602_PrintInt(voltValue[6]/100);
		  		  LCD1602_setCursor(1,3);
		  		  LCD1602_print(".");
		  		  LCD1602_setCursor(1,4);
		  		  LCD1602_PrintInt(voltValue[6]%100);

		  		  LCD1602_setCursor(1,16);
		  		  LCD1602_PrintInt(7);

		  		LCD1602_setCursor(2,2);
		  				  		  LCD1602_PrintInt(tempValue[6]/1 );
		  				  		  LCD1602_setCursor(2,4);
		  				  		  LCD1602_print(".");
		  				  		  LCD1602_setCursor(2,5);
		  				  		  tempIntVal=tempValue[6];
		  				  		  tempIntVal %= 10;
		  				  		  LCD1602_PrintInt(tempIntVal);
		  				  		LCD1602_noBlink();
		  		  break;
		  	  default:


		  		  break;

		  	  }


	  }
		  	  else
		  	  {
		  		      LCD1602_clear();
		  		  	  LCD1602_setCursor(1,1);
		  			  LCD1602_print("PLEASE TOUCH");
		  			  LCD1602_setCursor(2,5);
		  			  LCD1602_print("BUTTON");
		  			  LCD1602_noCursor();
		  			  ClearStatus=1;
		  			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
		  			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);


		  			rgbAnimation();
		  	  }








  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 15;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 8;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 9;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 10;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 11;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 12;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = 13;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 14;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 15;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 60000-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 2000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1384-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 255-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 655;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 665;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 60-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 0xffff-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SD_OR_WIFI_Pin|LED_OFF_Pin|LED_ON_Pin|FANTRANSISTOR_Pin
                          |E_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D0_Pin|D1_Pin|D2_Pin|D3_Pin
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |BUZZER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE5
                           PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PE7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SD_OR_WIFI_Pin LED_OFF_Pin LED_ON_Pin FANTRANSISTOR_Pin
                           E_Pin RS_Pin */
  GPIO_InitStruct.Pin = SD_OR_WIFI_Pin|LED_OFF_Pin|LED_ON_Pin|FANTRANSISTOR_Pin
                          |E_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D3_Pin
                           PB6 */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin
                           BUZZER_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

	if (htim->Instance == TIM1)
	{
		// release the semaphore here
				 /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
				 it will get set to pdTRUE inside the interrupt safe API function if a
				 context switch is required. */
				BaseType_t xHigherPriorityTaskWoken = pdFALSE;

				// xSemaphoreGiveFromISR(DHT_SEM, &xHigherPriorityTaskWoken);  // ISR SAFE VERSION

				/* Pass the xHigherPriorityTaskWoken value into portEND_SWITCHING_ISR(). If
				 xHigherPriorityTaskWoken was set to pdTRUE inside xSemaphoreGiveFromISR()
				 then calling portEND_SWITCHING_ISR() will request a context switch. If
				 xHigherPriorityTaskWoken is still pdFALSE then calling
				 portEND_SWITCHING_ISR() will have no effect */

				portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
	}

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
