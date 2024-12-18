/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define UART3_RX_Pin GPIO_PIN_11
#define UART3_RX_GPIO_Port GPIOC
#define TIM8_CH3_Pin GPIO_PIN_7
#define TIM8_CH3_GPIO_Port GPIOI
#define TIM8_CH2_Pin GPIO_PIN_6
#define TIM8_CH2_GPIO_Port GPIOI
#define TIM8_CH1_Pin GPIO_PIN_6
#define TIM8_CH1_GPIO_Port GPIOC
#define PF10_CH1_Pin GPIO_PIN_6
#define PF10_CH1_GPIO_Port GPIOF
#define LED_R_Pin GPIO_PIN_12
#define LED_R_GPIO_Port GPIOH
#define ADC_BAT_Pin GPIO_PIN_10
#define ADC_BAT_GPIO_Port GPIOF
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOH
#define LED__B_Pin GPIO_PIN_10
#define LED__B_GPIO_Port GPIOH
#define TIM4_CH3_Pin GPIO_PIN_14
#define TIM4_CH3_GPIO_Port GPIOD
#define KEY_Pin GPIO_PIN_0
#define KEY_GPIO_Port GPIOA
#define CS1_Accel_Pin GPIO_PIN_4
#define CS1_Accel_GPIO_Port GPIOA
#define TIM1_CH3_Pin GPIO_PIN_13
#define TIM1_CH3_GPIO_Port GPIOE
#define TIM1_CH4_Pin GPIO_PIN_14
#define TIM1_CH4_GPIO_Port GPIOE
#define CS1_Gyro_Pin GPIO_PIN_0
#define CS1_Gyro_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
