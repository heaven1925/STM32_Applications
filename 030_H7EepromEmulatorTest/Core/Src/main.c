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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FLASH_OBProgramInitTypeDef OBInit;

uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555, 0x6666, 0x7777};
uint16_t VarDataTab[NB_OF_VAR] = {0xDEAD, 0xBEEF, 0xEFFE};
uint16_t VarValue = 0xABCD;
uint16_t VarDataTmp = 0x1234;


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
  /* USER CODE BEGIN 2 */

  HAL_FLASH_Unlock();

  if( EE_Init() != EE_OK)
  {
      Error_Handler();
  }

  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

  /* --- Store successively many values of the three variables in the EEPROM ---*/
    /* Store 0x1000 values of Variable1 in EEPROM */
    for (VarValue = 1; VarValue <= 0x1000; VarValue++)
    {
      /* Sequence 1 */
      if((EE_WriteVariable(VirtAddVarTab[0],  VarValue)) != HAL_OK)
      {
        Error_Handler();
      }

      if((EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0])) != HAL_OK)
      {
        Error_Handler();
      }
      if (VarValue != VarDataTab[0])
      {
        Error_Handler();
      }

      /* Sequence 2 */
      if(EE_WriteVariable(VirtAddVarTab[1], ~VarValue) != HAL_OK)
      {
        Error_Handler();
      }

      if(EE_ReadVariable(VirtAddVarTab[1],  &VarDataTab[1]) != HAL_OK)
      {
        Error_Handler();
      }
      if(((uint16_t)~VarValue) != VarDataTab[1])
      {
        Error_Handler();
      }
      /* Toggle LED3 */
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
      /* Sequence 3 */
      if(EE_WriteVariable(VirtAddVarTab[2],  VarValue << 1) != HAL_OK)
      {
        Error_Handler();
      }

      if(EE_ReadVariable(VirtAddVarTab[2],  &VarDataTab[2]) != HAL_OK)
      {
        Error_Handler();
      }
      if ((VarValue << 1) != VarDataTab[2])
      {
        Error_Handler();
      }
      /* Toggle LED3 */
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    }


    /* read the last stored variables data*/
    if(EE_ReadVariable(VirtAddVarTab[0], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }

    if (VarDataTmp != VarDataTab[0])
    {
      Error_Handler();
    }

    if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }

    if (VarDataTmp != VarDataTab[1])
    {
      Error_Handler();
    }

    if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }

    if (VarDataTmp != VarDataTab[2])
    {
      Error_Handler();
    }
    /* Toggle LED3 */
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);


    /* Store 0x3000 values of Variable3 in EEPROM */
    for (VarValue = 1; VarValue <= 0x3000; VarValue++)
    {
      if(EE_WriteVariable(VirtAddVarTab[2], VarValue) != HAL_OK)
      {
        Error_Handler();
      }

      if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTab[2]) != HAL_OK)
      {
        Error_Handler();
      }
      if(VarValue != VarDataTab[2])
      {
        Error_Handler();
      }
      /* Toggle LED3 */
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }

    /* read the last stored variables data*/
    if(EE_ReadVariable(VirtAddVarTab[0], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }

    if (VarDataTmp != VarDataTab[0])
    {
      Error_Handler();
    }

    if(EE_ReadVariable(VirtAddVarTab[1], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }
    if (VarDataTmp != VarDataTab[1])
    {
      Error_Handler();
    }

    /* Toggle LED3 */
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    if(EE_ReadVariable(VirtAddVarTab[2], &VarDataTmp) != HAL_OK)
    {
      Error_Handler();
    }
    if (VarDataTmp != VarDataTab[2])
    {
      Error_Handler();
    }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 4096;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
