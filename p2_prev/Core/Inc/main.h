/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define EN_SIGNAL_Pin GPIO_PIN_0
#define EN_SIGNAL_GPIO_Port GPIOA
#define KBD_OUT0_Pin GPIO_PIN_1
#define KBD_OUT0_GPIO_Port GPIOA
#define KBD_OUT1_Pin GPIO_PIN_2
#define KBD_OUT1_GPIO_Port GPIOA
#define KBD_OUT2_Pin GPIO_PIN_3
#define KBD_OUT2_GPIO_Port GPIOA
#define KBD_OUT3_Pin GPIO_PIN_4
#define KBD_OUT3_GPIO_Port GPIOA
#define KBD_IN0_Pin GPIO_PIN_5
#define KBD_IN0_GPIO_Port GPIOA
#define KBD_IN1_Pin GPIO_PIN_6
#define KBD_IN1_GPIO_Port GPIOA
#define KBD_IN2_Pin GPIO_PIN_7
#define KBD_IN2_GPIO_Port GPIOA
#define KBD_IN3_Pin GPIO_PIN_0
#define KBD_IN3_GPIO_Port GPIOB
#define BLUE_Pin GPIO_PIN_10
#define BLUE_GPIO_Port GPIOB
#define RED_Pin GPIO_PIN_15
#define RED_GPIO_Port GPIOA
#define GREEN_Pin GPIO_PIN_3
#define GREEN_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */