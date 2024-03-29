/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define E_Pin GPIO_PIN_4
#define E_GPIO_Port GPIOE
#define RS_Pin GPIO_PIN_5
#define RS_GPIO_Port GPIOE
#define AD9833SCK_Pin GPIO_PIN_5
#define AD9833SCK_GPIO_Port GPIOA
#define AD9833DATA_Pin GPIO_PIN_6
#define AD9833DATA_GPIO_Port GPIOA
#define AD9833SS_Pin GPIO_PIN_7
#define AD9833SS_GPIO_Port GPIOA
#define D0_Pin GPIO_PIN_12
#define D0_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_13
#define D1_GPIO_Port GPIOB
#define D2_Pin GPIO_PIN_14
#define D2_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_15
#define D3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_8
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_9
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_10
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_11
#define D7_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
