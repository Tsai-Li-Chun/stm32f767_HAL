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

/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "stm32f7xx_hal.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define_gpio_nickname.h"
/* User Includes End */

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
	*		 RCC_CLK,NVIC etc...
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
		/* 設定TIM3計數更新中斷優先度 */
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
		/* 開啟TIM3中斷 */
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
}

/** * @brief USART1 Msp StartUp Configuration
	*		 RCC_CLK,GPIO,NVIC etc...
	* @param TIM_HandleTypeDef*(pointer) 
	* @return None 
** */
void HAL_UART_MspInit(UART_HandleTypeDef* hu)
{
	/* 宣告GPIO(uart)初始化用結構變數 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* USART1 Msp StartUp */
	if( hu->Instance == USART1 )
	{
		/* 開啟USART1工作時脈 */
		__HAL_RCC_USART1_CLK_ENABLE();

		/* 設定輸出模式-推挽映射 */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		/* 設定輸出翻轉速度 */
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		/* 設定無上下拉電阻 */
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		/* 設定接腳 */
		GPIO_InitStruct.Pin = GPIO_Pin_usart1_rx | GPIO_Pin_usart1_tx;
		/* 設定映射功能 */
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		/* 載入設定 */
		HAL_GPIO_Init(GPIO_Port_usart1, &GPIO_InitStruct);

		// /* 設定USART1接收中斷優先度 */
		// HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
		// /* 開啟USART1中斷 */
		// HAL_NVIC_EnableIRQ(USART1_IRQn);
	}
}

/** * @brief USART1 Msp ShatDown Configuration
	*		 RCC_CLK,GPIO,NVIC etc...
	* @param TIM_HandleTypeDef*(pointer) 
	* @return None 
** */
void HAL_UART_MspDeInit(UART_HandleTypeDef* hu)
{
	/* USART1 Msp ShatDown */
	if( hu->Instance == USART1 )
	{
		/* 關閉USART1工作時脈 */
		__HAL_RCC_USART1_CLK_DISABLE();
		/*  */
		HAL_UART_DeInit(hu);
		/* 關閉USART1實際TxRx接腳 */
		HAL_GPIO_DeInit(GPIO_Port_usart1, GPIO_Pin_usart1_rx|GPIO_Pin_usart1_tx);
		/* 關閉USART1中斷 */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
	}
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF stm32f7xx_hal_msp.c ***** */
