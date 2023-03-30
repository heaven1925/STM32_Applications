/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

uint16_t adc_value=0;
int adc_value_last=0;
int adcDummy;
int menuItem=0;
int frekansItem=0;
int frekansValue=0;


int dutyValue;

int waveValue=0;
int selectedWaveForm;
int selectedFreq;

int checkLed=0;
int setSignal=0;
int resetDummy=0;
int freqDummy=0;
int nextStep=0;
int errorFlag=0;


int i=0;
char waveChar='X';


int extTest=0;
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
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */




/*
 * void AD9833_SetWave(uint16_t Wave);                      // Sets Output Wave Type
void AD9833_SetWaveData(float Frequency,float Phase);    // Sets Wave Frequency & Phase
void AD9833_Init(uint16_t Wave,float FRQ,float Phase);   // Initializing AD9833
 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Read_ADC()
{
	HAL_ADC_Start(&hadc1);

	if(HAL_ADC_PollForConversion(&hadc1, 100000) == HAL_OK)
	{
		adc_value = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);
	return adc_value;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	void LCD_FreqUnit(void)
	{
		if(frekansItem>0)
		{
			LCD1602_setCursor(2,15);
			LCD1602_print("  ");
			LCD1602_setCursor(2,15);
			LCD1602_print("Hz");
		}
		else
		{
			LCD1602_setCursor(2,15);
			LCD1602_print("  ");
		}
	}

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

	AD9833_Init(0,0,0);

	LCD1602_Begin8BIT(RS_GPIO_Port, RS_Pin, E_Pin, D0_GPIO_Port, D0_Pin, D1_Pin, D2_Pin, D3_Pin, D4_GPIO_Port, D4_Pin, D5_Pin, D6_Pin, D7_Pin);


	LCD1602_setCursor(1,3);
	LCD1602_print("f=");
	LCD1602_setCursor(1,11);
	LCD1602_print("Hz");

	/*
	 * LCD1602_print("Hz");
	 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		adc_value = Read_ADC();

		// 0 sine 1 sq 3 tri

		if(waveValue==2)
					{
						waveChar='S';
					}
					else if(waveValue==3)
					{
						waveChar='K';
					}
					else if(waveValue==4)
								{
						waveChar='T';
								}
					else if(waveValue<2 || waveValue>4 || waveValue==0)
								{
						waveChar='X';
								}


		if(extTest==1)
		{

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);	// MENU 3 KOMUTLARI

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // BUZZER
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // BUZZER

			// START

			selectedFreq = frekansValue;
			selectedWaveForm = waveValue; // 1 sine , 2 kare , 3 ücgen, 4 nosignal

			// KAYIT EDİLDİ
			checkLed++;
			extTest=0;
		}

		if(selectedFreq!=frekansValue && checkLed==1)
		{

			if(selectedWaveForm==2)
			{
				waveChar='S';
			}
			else if(selectedWaveForm==3)
			{
				waveChar='K';
			}
			else if(selectedWaveForm==4)
						{
				waveChar='T';
						}
			else if(selectedWaveForm<2 || selectedWaveForm>4 )
						{
				waveChar='X';
						}

			LCD1602_setCursor(1,5);
			LCD1602_PrintInt(selectedFreq);

			LCD1602_setCursor(1,1);
			LCD1602_print("  ");
			LCD1602_setCursor(1,1);
			LCD1602_writeData(waveChar);

			LCD1602_setCursor(2,1);
			LCD1602_print("              ");
			LCD1602_setCursor(2,16);
			LCD1602_print(" ");
		}

			if(selectedWaveForm==2 && checkLed==1 && selectedFreq != 0) // SINE ANIMASYON
			{
				for(i=0;i<15;i++)
								{
									LCD1602_setCursor(2,i);
									if(i%2==0)
									{

										LCD1602_writeData(1);
									}
									else
									{

										LCD1602_writeData(2);
									}
									HAL_Delay(100);
								}
			}
			else if(selectedWaveForm==4 && checkLed==1 && selectedFreq != 0) // TRG ANIMASYON
			{

				for(i=0;i<15;i++)
				{
					LCD1602_setCursor(2,i);
					if(i%2==0)
					{

						LCD1602_print("/");
					}
					else
					{

						LCD1602_writeData(0);
					}
					HAL_Delay(100);
				}

			}

			else if(selectedWaveForm==3 && checkLed==1 && selectedFreq != 0) // SQR ANIMASYON
			{
				for(i=0;i<15;i++)
								{
									LCD1602_setCursor(2,i);
									if(i%2==0)
									{

										LCD1602_print("_");
									}
									else
									{

										LCD1602_print("-");
									}
									HAL_Delay(100);
								}
			}
			else if(checkLed!=1)
			{
				LCD1602_setCursor(2,16);
				LCD1602_print("                ");
			}
			else
			{
				if(errorFlag==1)
				{
					LCD1602_noBlink();
											for(i=0; i<=5;i++)
											{
												LCD1602_setCursor(2,1);
												LCD1602_print("                ");
												HAL_Delay(15);

												LCD1602_setCursor(2,6);
												LCD1602_print("ERROR");
												HAL_Delay(100);
												LCD1602_setCursor(2,6);
												LCD1602_print("     ");
												HAL_Delay(100);
				}

						}


					}



		if(selectedFreq==0 && selectedWaveForm==0 && checkLed==1)
		{
			errorFlag=1;
		}
		else if(selectedFreq==0 && checkLed==1)
		{
			errorFlag=1;
		}
		else if(selectedWaveForm==0 && checkLed==1)
		{
			errorFlag=1;
		}
		else
		{
			errorFlag=0;
		}


		if(menuItem<0)
		{
			menuItem=1;
			LCD1602_setCursor(1,1);
			LCD1602_setCursor(1,1);
			LCD1602_writeData(waveChar);
		}

		else if((selectedWaveForm!=waveValue ||selectedFreq!=frekansValue) && checkLed!=1)
		{
			LCD1602_setCursor(1,5);
			LCD1602_PrintInt(frekansValue);


			LCD1602_setCursor(1,1);
			LCD1602_writeData(waveChar);
		}


		// BUTON İ�?LEMLERİ //

		if(adcDummy>5 || adcDummy<-5)
		{


			if(adc_value>=180 && adc_value<200)
			{
				if(checkLed!=1)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);	// MENU 1 KOMUTLARI
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // BUZZER
				}


				HAL_Delay(250); // HEMEN ARKA ARKAYA BASILAMASIN

				// SINYAL FORM
				menuItem++;
				if(menuItem==1 && checkLed!=1)
				{
					// SINE


					waveValue=2; // Sine dalga seçildi
				}
				else if(menuItem==2 && checkLed!=1)
				{

					// KARE
					waveValue=3; // Kare dalga seçildi
				}
				else if(menuItem==3 && checkLed!=1)
				{
					// ÜÇGEN

					waveValue=4; // Üçgen dalga seçildi
				}
				else if(menuItem>3 || menuItem<0)
				{
					menuItem=0;
				}
				else if(checkLed!=1)
				{
					menuItem=0;

					waveValue=4; // Sinyal yok
				}

			}
			else if(adc_value>= 200 && adc_value<210)
			{
				if(checkLed!=1)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); // MENU 2 KOMUTLARI
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // BUZZER
				}

				HAL_Delay(250); // HEMEN ARKA ARKAYA BASILAMASIN



				// Frekans ++
				LCD1602_setCursor(1,5);
				LCD1602_print("     ");
				frekansItem++;



				switch(frekansItem)
				{
				case 1 :
					// FOSFOR Dİ�?
					frekansValue=79;
					break;
				case 2 :
					// BO�?LUK
					frekansValue=700;
					break;
				case 3 :
					// ALTIN-14
					frekansValue=4830;
					break;
				case 4 :
					// ALTIN-1

					frekansValue=4900;
					break;
				case 5 :
					// ALTIN-2

					frekansValue=5000;
					break;
				case 6 :
					// ALTIN-3

					frekansValue=5100;
					break;
				case 7 :
					// ALTIN-4

					frekansValue=5200;
					break;
				case 8 :
					// ALTIN-5

					frekansValue=5252;
					break;
				case 9 :
					// ALTIN-6

					frekansValue=5300;
					break;
				case 10 :
					// MÜCEHVER-1

					frekansValue=5400;
					break;
				case 11 :
					// ALTIN-7

					frekansValue=5621;
					break;
				case 12 :
					// FOSFOR KEMİK

					frekansValue=7000;
					break;
				case 13 :
					// ALIMINYUM-2

					frekansValue=7097;
					break;
				case 14 :
					// GÜMÜ�?-1

					frekansValue=8700;
					break;
				case 15 :
					// GÜMÜ�?-2

					frekansValue=8950;
					break;
				case 16 :
					// SU

					frekansValue=10000;
					break;
				case 17 :
					// BRONZ-1

					frekansValue=11311;
					break;
				case 18 :
					// BRONZ-2

					frekansValue=11700;
					break;
				case 19 :
					// BAKIR

					frekansValue=11947;
					break;
				case 20 :
					// ELMAS

					frekansValue=12700;
					break;
				case 21 :
					// KUR�?UN 1

					frekansValue=14000;
					break;
				case 22 :
					// KUR�?UN2

					frekansValue=24250;
					break;
				case 23 :
					// GENEL 1

					frekansValue=55000;
					break;

				default :

					frekansItem = 0;
					frekansValue=0;
					break;
				}

				if(menuItem>3 || menuItem<0)
				{
					menuItem=0;
				}

			}
			else if(adc_value>= 210 && adc_value<254 && adc_value!=225)
			{

				if(checkLed!=1)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); // MENU 2 KOMUTLARI
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // BUZZER
				}

				HAL_Delay(250); // HEMEN ARKA ARKAYA BASILAMASIN



				// Frekans --
				LCD1602_setCursor(1,5);
				LCD1602_print("     ");
				frekansItem--;



				switch(frekansItem)
				{
				case 1 :
					// FOSFOR Dİ�?

					frekansValue=79;
					break;
				case 2 :
					// BO�?LUK

					frekansValue=700;
					break;
				case 3 :
					// ALTIN-14

					frekansValue=4830;
					break;
				case 4 :
					// ALTIN-1

					frekansValue=4900;
					break;
				case 5 :
					// ALTIN-2

					frekansValue=5000;
					break;
				case 6 :
					// ALTIN-3

					frekansValue=5100;
					break;
				case 7 :
					// ALTIN-4

					frekansValue=5200;
					break;
				case 8 :
					// ALTIN-5

					frekansValue=5252;
					break;
				case 9 :
					// ALTIN-6

					frekansValue=5300;
					break;
				case 10 :
					// MÜCEHVER-1
					frekansValue=5400;
					break;
				case 11 :
					// ALTIN-7

					frekansValue=5621;
					break;
				case 12 :
					// FOSFOR KEMİK

					frekansValue=7000;
					break;
				case 13 :
					// ALIMINYUM-2

					frekansValue=7097;
					break;
				case 14 :
					// GÜMÜ�?-1
					frekansValue=8700;
					break;
				case 15 :
					// GÜMÜ�?-2

					frekansValue=8950;
					break;
				case 16 :
					// SU

					frekansValue=10000;
					break;
				case 17 :
					// BRONZ-1

					frekansValue=11311;
					break;
				case 18 :
					// BRONZ-2

					frekansValue=11700;
					break;
				case 19 :
					// BAKIR

					frekansValue=11947;
					break;
				case 20 :
					// ELMAS

					frekansValue=12700;
					break;
				case 21 :
					// KUR�?UN 1

					frekansValue=14000;
					break;
				case 22 :
					// KUR�?UN2

					frekansValue=24250;
					break;
				case 23 :
					// GENEL 1

					frekansValue=55000;
					break;

				default :

					frekansItem = 0;
					frekansValue=0;
					break;
				}
				if(menuItem>3 || menuItem<0)
				{
					menuItem=0;
				}


			}
			else if(adc_value>= 255)
			{
				// MENU 3 KOMUTLARI

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // BUZZER

				// BUTON HATA ERROR
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);	// BUTONA BASILMADI�?I ZAMAN
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
			}

		}
		adcDummy = adc_value - adc_value_last;
		adc_value_last = adc_value;


		// ÇIKI�? LEDİ

		if(checkLed == 1 )
		{
			// SİSTEM AYARLARI KAYDEDİLDİ

			nextStep++;

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
			LCD1602_setCursor(1,15);
			LCD1602_print("+");

			frekansItem=0;
			frekansValue=0;
			waveValue=0;


		}
		else
		{
			LCD1602_setCursor(1,15);
			LCD1602_print("-");
				if(nextStep!=0)
				{
					LCD1602_setCursor(1,1);
					LCD1602_writeData(waveChar);
					LCD1602_setCursor(1,6);
					LCD1602_print("     ");
					LCD1602_setCursor(1,5);
					LCD1602_PrintInt(frekansValue);
					LCD1602_setCursor(2,1);
					LCD1602_print("                ");

				}


			// SİSTEM AYARLARI SIFIRLANDI.
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
			checkLed=0;
		}


		if(selectedWaveForm==2)
		{
			// SINE
			if(setSignal==0)
			{
				AD9833_SetWave(0);
				AD9833_SetWaveData(selectedFreq,0);
				setSignal=1;
				resetDummy=0;
			}
		}
		else if(selectedWaveForm==3)
		{
			// KARE
			if(setSignal==0)
			{
				AD9833_SetWave(1);
				AD9833_SetWaveData(selectedFreq,0);
				setSignal=1;
				resetDummy=0;
			}
		}
		else if(selectedWaveForm==4)
		{
			// UCGEN
			if(setSignal==0)
			{
				AD9833_SetWave(2);
				AD9833_SetWaveData(selectedFreq,0);
				setSignal=1;
				resetDummy=0;
			}


		}
		else if(selectedWaveForm==0 || selectedWaveForm>4 && resetDummy!=1)
		{
			setSignal=0;
			AD9833_Reset();
			resetDummy=1;
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  HAL_GPIO_WritePin(GPIOE, E_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, AD9833SCK_Pin|AD9833DATA_Pin|AD9833SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D0_Pin|D1_Pin|D2_Pin|D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : E_Pin RS_Pin */
  GPIO_InitStruct.Pin = E_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : AD9833SCK_Pin AD9833DATA_Pin AD9833SS_Pin */
  GPIO_InitStruct.Pin = AD9833SCK_Pin|AD9833DATA_Pin|AD9833SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

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
