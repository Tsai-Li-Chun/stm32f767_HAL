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
extern int delay_time_1ms;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void delay_1ms(int);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define user_Pin GPIO_PIN_0
#define user_GPIO_Port GPIOA
#define u1_tx_Pin GPIO_PIN_0
#define u1_tx_GPIO_Port GPIOB
#define u1_rx_Pin GPIO_PIN_1
#define u1_rx_GPIO_Port GPIOB
#define u2_tx_Pin GPIO_PIN_2
#define u2_tx_GPIO_Port GPIOB
#define u2_rx_Pin GPIO_PIN_7
#define u2_rx_GPIO_Port GPIOE
#define u3_tx_Pin GPIO_PIN_8
#define u3_tx_GPIO_Port GPIOE
#define u3_rx_Pin GPIO_PIN_9
#define u3_rx_GPIO_Port GPIOE
#define u4_tx_Pin GPIO_PIN_10
#define u4_tx_GPIO_Port GPIOE
#define u4_rx_Pin GPIO_PIN_11
#define u4_rx_GPIO_Port GPIOE
#define u5_tx_Pin GPIO_PIN_12
#define u5_tx_GPIO_Port GPIOE
#define u5_rx_Pin GPIO_PIN_13
#define u5_rx_GPIO_Port GPIOE
#define u6_tx_Pin GPIO_PIN_14
#define u6_tx_GPIO_Port GPIOE
#define u6_rx_Pin GPIO_PIN_15
#define u6_rx_GPIO_Port GPIOE
#define led_green_Pin GPIO_PIN_12
#define led_green_GPIO_Port GPIOD
#define led_orange_Pin GPIO_PIN_13
#define led_orange_GPIO_Port GPIOD
#define led_red_Pin GPIO_PIN_14
#define led_red_GPIO_Port GPIOD
#define led_blue_Pin GPIO_PIN_15
#define led_blue_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
