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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "STM_MY_LCD16X2.h"
#include "math.h"
#include "string.h"

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
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc2;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

#define VOLTSIZE 12
#define ADCSIZE 13
#define DATASIZE 12	// /f space data(5) space /n /r

#define MEMORY 10

// Loop variables

int i=0, j=0, d=0;
int adc_buffer[ADCSIZE];
int countFlag=0;

float tmp=0;

int testNumber=0;
int selectItem=0;

int redData=0;
int blueData=0;
int greenData=0;

int lowestVoltageIndexDummy = 0;



// Main variables

int adcValues[ADCSIZE] = {0};

double voltVal[VOLTSIZE] = {0};

int voltintVal[VOLTSIZE] = {0};

char voltData[VOLTSIZE][DATASIZE];
char voltValueArray[DATASIZE];

int lowestVoltageIndex = 0;
int highestVoltageIndex = 0;

float softTemp = 0;

int tempValue = 0;
int tempValueOndalik = 0;
int currentValue = 0;
int currentValueOndalik = 0;
int currentValueYuzdelik = 0;

uint8_t getData[MEMORY];
uint8_t mData[MEMORY];

uint8_t testText[]="usart test edildi. \r\n ";


int lowestcellVoltage = 0;
int highestcellVoltage = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void adcRead(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC2)
	{
		for(d=0; d<=ADCSIZE; d++)
		{
			adcValues[d] = adc_buffer[d];

		}
	}
}



void adctoArray(void)
{
	int k=0;
	while(k<VOLTSIZE)
	{
		voltVal[k]= ( adcValues[k] * 4.2 / 4096 ) ;
		k++;
	}

	float Rt=0;
	float Rp=10000;
	float T2=273.15+25;
	float Bx=3950;
	float Ka=273.15;
	float vol=0;
	vol=(float)((adcValues[12])*(3.3/4096));
	Rt=(3.3-vol)*10000/vol;
	softTemp =1/(1/T2+log(Rt/Rp)/Bx)-Ka+0.5;

	tempValue = softTemp ;
	int tempValueOndalikDummy = softTemp*10 ;
	tempValueOndalik = tempValueOndalikDummy %10;

	currentValue = adcValues[13];
}

void doublevoltValtoInteger(void)
{
		int k=0;
		while(k<VOLTSIZE)
		{
			int voltDummy;
			voltDummy = voltVal[k] * 100 ;
			voltintVal[k] = voltDummy ;
			k++;
		}
}


void voltstoDigit(void)
{
	int digitBindebirler;
	int digitBindeonlar;
	int digitBindeyuzler;
	int digitTamkisim;

	for(i=0; i<=VOLTSIZE ; i++)
	{
		digitTamkisim = voltVal[i] ; // double to float
		voltData[i][0] = digitTamkisim +48;

		voltData[i][1]='.';

		digitBindeyuzler = voltVal[i] * 1000;
		digitBindeyuzler = digitBindeyuzler % 1000 / 100 ;
		voltData[i][2] =  digitBindeyuzler +48;

		digitBindeonlar = voltVal[i] * 1000;
		digitBindeonlar = digitBindeonlar % 100 / 10 ;
		voltData[i][3] =  digitBindeonlar +48;

		digitBindebirler = voltVal[i] * 1000;
		digitBindebirler = digitBindebirler % 10;
		voltData[i][4] =  digitBindebirler +48;
	}

}

void datatoArray(int dataNumber)
{
		voltValueArray[0]= 12;
		voltValueArray[1]= 32;
		voltValueArray[7]= 32;
		voltValueArray[8]= 10;
		voltValueArray[9]= 13;

		for(i=0 ; i<=4; i++)
		{
			voltValueArray[i+2]=voltData[dataNumber][i];
		}

}

int lowestVoltage_Conf(int *voltValues)
{
	int lowestVoltage = voltValues[0] ;
	int indexLow=0;
	for(i=0; i<VOLTSIZE ; i++ )
	{
		if( voltValues[i] <  lowestVoltage )
		{
			 lowestVoltage = voltValues[i];
			 indexLow=i;
		}
	}
	lowestVoltageIndex = indexLow ;
	return lowestVoltage;
}

int highestVoltage_Conf(int *voltValues)
{
	int highestVoltage = voltValues[0] ;
	int indexHigh=0;
	for(i=0; i<VOLTSIZE ; i++ )
	{
		if( voltValues[i] >  highestVoltage )
		{
			highestVoltage = voltValues[i];
			indexHigh=i;
		}
	}
	highestVoltageIndex = indexHigh ;
	return highestVoltage;
}

void dataSend(void)
{
			sprintf(mData,"\f TEMPERATURE : %d.%d \n\r",tempValue,tempValueOndalik); // sıcaklık degiskeni dataya aktarıldı
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);

			sprintf(mData,"\f CURRENT : %d.%d%d \n\r",currentValue%10,currentValueOndalik,currentValueYuzdelik); // sıcaklık degiskeni dataya aktarıldı
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);

			HAL_Delay(10);

			for(j=0; j<VOLTSIZE; j++)
			{
				sprintf(mData,"\f CELL %d : \r",j+1);
				HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
				datatoArray(j);
				HAL_UART_Transmit(&huart2, (char*)voltValueArray , strlen(voltValueArray), 1000);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				HAL_Delay(25);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
			}

			sprintf(mData,"\f HCVI : %d \n\r",highestVoltageIndex + 1);
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
			sprintf(mData,"\f HCVV : %d.%d \n\r",highestcellVoltage/100,highestcellVoltage%100);
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
			sprintf(mData,"\f LCVI : %d \n\r",lowestVoltageIndex + 1 );
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
			sprintf(mData,"\f LCVV : %d.%d \n\r",lowestcellVoltage/100,lowestcellVoltage%100);
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
			sprintf(mData,"\f RGBCOLOR RED:%d BLUE:%d GREEN:%d \n\r",redData, blueData, greenData);
			HAL_UART_Transmit(&huart2, (uint8_t*)mData , strlen(mData), 1000);
}

void dataprintLCD(void)
{
	int selectedData = 0;
	selectedData = selectItem ;
	if(selectedData>12)
	{
		selectedData=0;
		selectItem=0;
	}
	switch(selectedData)
	{
	case 0:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 1=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[0]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 1:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 2=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[1]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 2:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 3=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[2]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 3:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 4=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[3]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 4:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 5=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[4]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 5:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 6=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[5]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 6:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 7=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[6]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 7:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 8=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[7]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 8:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE 9=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[8]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 9:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE10=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[9]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 10:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE11=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[10]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;
	case 11:
		LCD1602_setCursor(1, 1);
		LCD1602_print("HUCRE12=");
		LCD1602_setCursor(1, 10);
		LCD1602_print(voltData[11]);
		LCD1602_setCursor(1, 15);
		LCD1602_print("V");
		break;

	default:
		LCD1602_clear();
	}

	LCD1602_setCursor(2, 1);
	LCD1602_print("T=");
	LCD1602_setCursor(2, 3);
	LCD1602_PrintInt(tempValue);
	LCD1602_setCursor(2, 5);
	LCD1602_print(".");
	LCD1602_setCursor(2, 6);
	LCD1602_PrintInt(tempValueOndalik);
	LCD1602_setCursor(2, 7);
	LCD1602_print("C");

	LCD1602_setCursor(2, 9);
	LCD1602_print("I=");
	LCD1602_setCursor(2, 11);
	LCD1602_PrintInt(currentValue%10);
	LCD1602_setCursor(2, 12);
	LCD1602_print(".");
	LCD1602_setCursor(2, 13);
	LCD1602_PrintInt(currentValueOndalik);
	LCD1602_setCursor(2, 14);
	LCD1602_PrintInt(currentValueYuzdelik);
	LCD1602_setCursor(2, 15);
	LCD1602_print("A");

	LCD1602_noBlink();
	LCD1602_noCursor();
}


void rgbSet(uint8_t red,uint8_t blue,uint8_t green)
{
	htim4.Instance->CCR1=red;
	htim4.Instance->CCR2=blue;
	htim4.Instance->CCR3=green;
}

void rgbConfig(int rawTemp)
{
	if(rawTemp>=40)
	{
		redData=255;
		blueData=0;
		greenData=0;
	}
	else if(rawTemp>0 && rawTemp<40)
	{
		for(i=1; i<=39;i++)
		{
			if(rawTemp==i)
			{
				redData = i*6;
				blueData = 255 - i*6;
				greenData = 123 - i*3;
			}
		}
	}
	else
	{
		redData=0;
		blueData=  255;
		greenData = 123;
	}


	rgbSet(redData, blueData, greenData);
}

void cellBalancing(int lowestVoltageIndex, int* voltintVal)
{

	if(lowestVoltageIndexDummy != lowestVoltageIndex )
	{

		for(i=2; i<VOLTSIZE; i++)	// REV
			{
				if(i==lowestVoltageIndex)
				{
					HAL_GPIO_WritePin(GPIOE, 0x0001 << i, GPIO_PIN_RESET);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOE, 0x0001 << i, GPIO_PIN_SET);
				}
			}

			lowestVoltageIndexDummy = lowestVoltageIndex ;

	}


	int voltValTOPvalue = voltintVal[lowestVoltageIndex]+40 ;
	int voltValBOTvalue = voltintVal[lowestVoltageIndex]-40 ;

	for(i=0; i<VOLTSIZE; i++)
	{
		if((voltintVal[i] <= voltValTOPvalue) && (voltintVal[i] >= voltValBOTvalue))
			{
				HAL_GPIO_WritePin(GPIOE, 0x0001 << i+2, GPIO_PIN_RESET);
			}
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
  MX_ADC2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  LCD1602_Begin8BIT(RS_GPIO_Port, RS_Pin, E_Pin, D0_GPIO_Port, D0_Pin, D1_Pin, D2_Pin, D3_Pin, D4_GPIO_Port, D4_Pin, D5_Pin, D6_Pin, D7_Pin);
  LCD1602_setCursor(1, 1);
  LCD1602_print("BMS");
  LCD1602_setCursor(2, 1);
  LCD1602_print("4.06.2021");

  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

  HAL_ADC_Start_DMA(&hadc2, adc_buffer, 13);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


		adcRead(&hadc2);
		adctoArray();
		doublevoltValtoInteger();
		voltstoDigit();

		lowestcellVoltage = lowestVoltage_Conf(voltintVal);
		highestcellVoltage = highestVoltage_Conf(voltintVal);

		cellBalancing(lowestVoltageIndex, voltintVal);

		rgbConfig(tempValue);
		dataSend();
		dataprintLCD();



		/*
		 *
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
		HAL_Delay(100);
		 *
		 */


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
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ENABLE;
  hadc2.Init.ContinuousConvMode = ENABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 13;
  hadc2.Init.DMAContinuousRequests = ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 6;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 7;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 8;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 9;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 10;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 11;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 12;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 13;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1383;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 254;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MOS_CELL1_Pin|MOS_CELL2_Pin|MOS_CELL3_Pin|MOS_CELL4_Pin
                          |MOS_CELL5_Pin|MOS_CELL6_Pin|MOS_CELL7_Pin|MOS_CELL8_Pin
                          |MOS_CELL9_Pin|MOS_CELL10_Pin|MOS_CELL11_Pin|MOS_CELL12_Pin
                          |MOS_CHARGE_Pin|MOS_DISCHARGE_Pin|RS_Pin|E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D0_Pin|D1_Pin|D2_Pin|D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin|LEDA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MOS_CELL1_Pin MOS_CELL2_Pin MOS_CELL3_Pin MOS_CELL4_Pin
                           MOS_CELL5_Pin MOS_CELL6_Pin MOS_CELL7_Pin MOS_CELL8_Pin
                           MOS_CELL9_Pin MOS_CELL10_Pin MOS_CELL11_Pin MOS_CELL12_Pin
                           MOS_CHARGE_Pin MOS_DISCHARGE_Pin RS_Pin E_Pin */
  GPIO_InitStruct.Pin = MOS_CELL1_Pin|MOS_CELL2_Pin|MOS_CELL3_Pin|MOS_CELL4_Pin
                          |MOS_CELL5_Pin|MOS_CELL6_Pin|MOS_CELL7_Pin|MOS_CELL8_Pin
                          |MOS_CELL9_Pin|MOS_CELL10_Pin|MOS_CELL11_Pin|MOS_CELL12_Pin
                          |MOS_CHARGE_Pin|MOS_DISCHARGE_Pin|RS_Pin|E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D3_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LEDA_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LEDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BUZZER_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
