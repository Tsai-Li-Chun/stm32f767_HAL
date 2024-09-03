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
#define debug_tx1_Pin GPIO_PIN_13
#define debug_tx1_GPIO_Port GPIOC
#define debug_tx2_Pin GPIO_PIN_14
#define debug_tx2_GPIO_Port GPIOC
#define debug_tx3_Pin GPIO_PIN_15
#define debug_tx3_GPIO_Port GPIOC
#define debug_tx4_Pin GPIO_PIN_0
#define debug_tx4_GPIO_Port GPIOC
#define debug_tx5_Pin GPIO_PIN_1
#define debug_tx5_GPIO_Port GPIOC
#define debug_tx6_Pin GPIO_PIN_2
#define debug_tx6_GPIO_Port GPIOC
#define debug_rx1_Pin GPIO_PIN_3
#define debug_rx1_GPIO_Port GPIOC
#define debug_rx2_Pin GPIO_PIN_0
#define debug_rx2_GPIO_Port GPIOA
#define debug_rx3_Pin GPIO_PIN_1
#define debug_rx3_GPIO_Port GPIOA
#define debug_rx4_Pin GPIO_PIN_0
#define debug_rx4_GPIO_Port GPIOB
#define debug_rx5_Pin GPIO_PIN_1
#define debug_rx5_GPIO_Port GPIOB
#define debug_rx6_Pin GPIO_PIN_2
#define debug_rx6_GPIO_Port GPIOB
#define debug_tim3_Pin GPIO_PIN_12
#define debug_tim3_GPIO_Port GPIOB
#define debug_tim4_Pin GPIO_PIN_13
#define debug_tim4_GPIO_Port GPIOB
#define debug_allOK_Pin GPIO_PIN_14
#define debug_allOK_GPIO_Port GPIOB
#define debug_lack_Pin GPIO_PIN_15
#define debug_lack_GPIO_Port GPIOB
#define user1_Pin GPIO_PIN_8
#define user1_GPIO_Port GPIOC
#define user2_Pin GPIO_PIN_9
#define user2_GPIO_Port GPIOC
#define user3_Pin GPIO_PIN_8
#define user3_GPIO_Port GPIOA
#define LD100E_ID1_in_Pin GPIO_PIN_15
#define LD100E_ID1_in_GPIO_Port GPIOA
#define LD100E_ID2_in_Pin GPIO_PIN_3
#define LD100E_ID2_in_GPIO_Port GPIOB
#define LD100E_ID3_in_Pin GPIO_PIN_4
#define LD100E_ID3_in_GPIO_Port GPIOB
#define LD100E_ID2_inB5_Pin GPIO_PIN_5
#define LD100E_ID2_inB5_GPIO_Port GPIOB
#define LD100E_ID5_in_Pin GPIO_PIN_8
#define LD100E_ID5_in_GPIO_Port GPIOB
#define LD100E_ID6_in_Pin GPIO_PIN_9
#define LD100E_ID6_in_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
