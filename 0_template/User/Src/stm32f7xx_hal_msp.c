/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file         stm32f7xx_hal_msp.c
	* @brief        This file provides code for the MSP Initialization
	*               and de-Initialization codes.
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
/* USER CODE BEGIN Includes */
#include "stm32f7xx_hal.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */
/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */
/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */
/* USER CODE END ExternalFunctions */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief Initializes the Global MSP.
	* @param None 
	* @return None 
** */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */
	/* USER CODE END MspInit 0 */

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	/* System interrupt init*/

	/* USER CODE BEGIN MspInit 1 */
	/* USER CODE END MspInit 1 */
}


/** * @brief TIM Msp StartUp Configuration
	*		 RCC_CLK,GPIO,NVIC etc...
	* @param TIM_HandleTypeDef*(pointer) 
	* @return None 
** */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* ht)
{
	/* TIM3 Msp StartUp */
	if( ht->Instance == TIM3 )
	{
		/* 開啟TIM3工作時脈 */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* 設定中斷優先度 */
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
		/* 開啟中斷 */
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
}


/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF stm32f7xx_hal_msp.c ***** */
