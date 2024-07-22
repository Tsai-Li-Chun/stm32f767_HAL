/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file    tim.c
	* @brief   This file provides code for the configuration
	*          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
#include "delta_LD_xxxE_M22.h"

uint8_t for_i = 0;
/* USER CODE END 0 */

TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 83;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 4999;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

	if(tim_baseHandle->Instance==TIM3)
	{
	/* USER CODE BEGIN TIM3_MspInit 0 */

	/* USER CODE END TIM3_MspInit 0 */
		/* TIM3 clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();

		/* TIM3 interrupt Init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 10, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM3_MspInit 1 */

	/* USER CODE END TIM3_MspInit 1 */
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

	if(tim_baseHandle->Instance==TIM3)
	{
	/* USER CODE BEGIN TIM3_MspDeInit 0 */

	/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();

		/* TIM3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM3_MspDeInit 1 */

	/* USER CODE END TIM3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/**
	* @brief  Period elapsed callback in non-blocking mode
			  * Period elapsed : 5ms
	* @param  htim TIM handle
	* @retval None
	*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(htim);

	/* If an interrupt occurs in TIM3 */
	if( htim->Instance == TIM3 )
	{
		if(delay_time_1ms>0) delay_time_1ms--;
		HAL_GPIO_TogglePin(GPIOD, led_blue_Pin);
		/* send command to read absolute position of six legs */
		// HAL_UART_Transmit_IT(&huart1, read_absolute_position, 8);
		for(for_i=0; for_i<6; for_i++)
		{
			tx_buff_size = read_AbsolutePosition(for_i);
			if((tx_buff_size%command_length)==0)
				HAL_UART_Transmit_IT(huartX[for_i], uart_tx_buff+tx_buff_size, command_length);
			else
			{
				/* To be added */
			}
		}
	}
}

/* USER CODE END 1 */
