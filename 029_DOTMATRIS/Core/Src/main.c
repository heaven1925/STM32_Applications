/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

typedef union
{
	uint8_t satir;
	struct
	{
		uint8_t r0;
		uint8_t r1;
		uint8_t r2;
		uint8_t r3;
		uint8_t r4;
		uint8_t r5;
		uint8_t r6;
		uint8_t r7;
	}row;
}linex_st;

typedef union
{
	uint8_t sutun;
	struct
	{
		uint8_t c0;
		uint8_t c1;
		uint8_t c2;
		uint8_t c3;
		uint8_t c4;
		uint8_t c5;
		uint8_t c6;
		uint8_t c7;
	}column;
}liney_st;

linex_st x_axis = { 0 };
liney_st y_axis = { 0 };

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

	uint8_t loopVal = 0;
	
	uint16_t selectPins = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		loopVal++ ;
		HAL_Delay(1000);
		if(loopVal >= 3 ) loopVal = 0;
		
		switch(loopVal)
		{
			case 0 :   // A HARFI
				x_axis.row.r0 = 0;	y_axis.column.c0 = 0;
				x_axis.row.r1 = 1;	y_axis.column.c1 = 0;
				x_axis.row.r2 = 0;	y_axis.column.c2 = 1;
				x_axis.row.r3 = 0;	y_axis.column.c3 = 0;
				x_axis.row.r4 = 1;	y_axis.column.c4 = 0;
				x_axis.row.r5 = 0;	y_axis.column.c5 = 0;
				x_axis.row.r6 = 0;	y_axis.column.c6 = 0;
				x_axis.row.r7 = 0;	y_axis.column.c7 = 0;		
			break;

			case 1 :  // B BURAYA DUZGUNCE EKLENECEK !
				x_axis.row.r0 = 0;	y_axis.column.c0 = 0;
				x_axis.row.r1 = 1;	y_axis.column.c1 = 1;
				x_axis.row.r2 = 0;	y_axis.column.c2 = 0;
				x_axis.row.r3 = 1;	y_axis.column.c3 = 1;
				x_axis.row.r4 = 0;	y_axis.column.c4 = 0;
				x_axis.row.r5 = 1;	y_axis.column.c5 = 1;
				x_axis.row.r6 = 0;	y_axis.column.c6 = 0;
				x_axis.row.r7 = 1;	y_axis.column.c7 = 0;		
			break;
			
			case 2 :  // C BURAYA DUZGUNCE EKLENECEK ! 
				x_axis.row.r0 = 1;	y_axis.column.c0 = 0;
				x_axis.row.r1 = 1;	y_axis.column.c1 = 0;
				x_axis.row.r2 = 0;	y_axis.column.c2 = 0;
				x_axis.row.r3 = 0;	y_axis.column.c3 = 1;
				x_axis.row.r4 = 0;	y_axis.column.c4 = 0;
				x_axis.row.r5 = 1;	y_axis.column.c5 = 0;
				x_axis.row.r6 = 1;	y_axis.column.c6 = 0;
				x_axis.row.r7 = 0;	y_axis.column.c7 = 1;		
			break;
	
			case 3 : // D BURAYA DUZGUNCE EKLENECEK !  
				x_axis.row.r0 = 0;	y_axis.column.c0 = 0;
				x_axis.row.r1 = 1;	y_axis.column.c1 = 0;
				x_axis.row.r2 = 1;	y_axis.column.c2 = 1;
				x_axis.row.r3 = 0;	y_axis.column.c3 = 0;
				x_axis.row.r4 = 1;	y_axis.column.c4 = 0;
				x_axis.row.r5 = 0;	y_axis.column.c5 = 1;
				x_axis.row.r6 = 0;	y_axis.column.c6 = 1;
				x_axis.row.r7 = 0;	y_axis.column.c7 = 0;	
			break;
			
			default : loopVal=0;	 break;
		}	
		
		selectPins = (uint16_t)x_axis.satir;
		HAL_GPIO_WritePin(GPIOB , selectPins , GPIO_PIN_SET );
		selectPins = 0;
		
		
		selectPins = (uint16_t)(y_axis.sutun << 8 );
		HAL_GPIO_WritePin(GPIOB , selectPins , GPIO_PIN_SET );
	
		//PB11 disariya verilmedigi icin pb11 set ise PC6 set edilecektir.
		if( ( selectPins & 0x0800 ) == 0x0800 ) // 0b0000100000000000
		{
			 HAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , GPIO_PIN_SET );
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC , GPIO_PIN_6 , GPIO_PIN_RESET );
		}
		selectPins = 0;
		
		
		
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart2.Init.BaudRate = 115200;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, R0_Pin|R1_Pin|R2_Pin|C2_Pin
                          |C4_Pin|C5_Pin|C6_Pin|C7_Pin
                          |R3_Pin|R4_Pin|R5_Pin|R6_Pin
                          |R7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : R0_Pin R1_Pin R2_Pin C2_Pin
                           C4_Pin C5_Pin C6_Pin C7_Pin
                           R3_Pin R4_Pin R5_Pin R6_Pin
                           R7_Pin */
  GPIO_InitStruct.Pin = R0_Pin|R1_Pin|R2_Pin|C2_Pin
                          |C4_Pin|C5_Pin|C6_Pin|C7_Pin
                          |R3_Pin|R4_Pin|R5_Pin|R6_Pin
                          |R7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : C3_Pin */
  GPIO_InitStruct.Pin = C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(C3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : C0_Pin C1_Pin */
  GPIO_InitStruct.Pin = C0_Pin|C1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
