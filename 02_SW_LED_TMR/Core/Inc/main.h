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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

#define GRN_LED_ON() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, GPIO_PIN_SET)
#define GRN_LED_OFF() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, GPIO_PIN_RESET)
#define ORN_LED_ON() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13, GPIO_PIN_SET)
#define ORN_LED_OFF() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13, GPIO_PIN_RESET)
#define RED_LED_ON() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14, GPIO_PIN_SET)
#define RED_LED_OFF() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14, GPIO_PIN_RESET)
#define BLU_LED_ON() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15, GPIO_PIN_SET)
#define BLU_LED_OFF() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15, GPIO_PIN_RESET)
#define BLU_LED_TOGGLE() HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15)
#define RED_LED_TOGGLE() HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GRN_LED_Pin GPIO_PIN_12
#define GRN_LED_GPIO_Port GPIOD
#define ORN_LED_Pin GPIO_PIN_13
#define ORN_LED_GPIO_Port GPIOD
#define RED_LED_Pin GPIO_PIN_14
#define RED_LED_GPIO_Port GPIOD
#define BLU_LED_Pin GPIO_PIN_15
#define BLU_LED_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
