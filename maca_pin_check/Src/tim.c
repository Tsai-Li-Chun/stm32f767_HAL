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
#include "gpio.h"
#include "usbd_cdc_if.h"
#include "cas_macaps15.h"

uint8_t for_tim3 = 0;
uint8_t for_tim4 = 0;
/* USER CODE END 0 */

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

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
/* TIM4 init function */
void MX_TIM4_Init(void)
{

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 83;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 99;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */

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
		HAL_NVIC_SetPriority(TIM3_IRQn, 14, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	/* USER CODE BEGIN TIM3_MspInit 1 */

	/* USER CODE END TIM3_MspInit 1 */
	}
	else if(tim_baseHandle->Instance==TIM4)
	{
	/* USER CODE BEGIN TIM4_MspInit 0 */

	/* USER CODE END TIM4_MspInit 0 */
		/* TIM4 clock enable */
		__HAL_RCC_TIM4_CLK_ENABLE();

		/* TIM4 interrupt Init */
		HAL_NVIC_SetPriority(TIM4_IRQn, 13, 0);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
	/* USER CODE BEGIN TIM4_MspInit 1 */

	/* USER CODE END TIM4_MspInit 1 */
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
	else if(tim_baseHandle->Instance==TIM4)
	{
	/* USER CODE BEGIN TIM4_MspDeInit 0 */

	/* USER CODE END TIM4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM4_CLK_DISABLE();

		/* TIM4 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM4_IRQn);
	/* USER CODE BEGIN TIM4_MspDeInit 1 */

	/* USER CODE END TIM4_MspDeInit 1 */
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

	/* if an interrupt occurs in TIM3 */
	if( htim->Instance == TIM3 )
	{
		if( maca_rx_flag!=0x3F )
			HAL_GPIO_WritePin(debug_lack_GPIO_Port, debug_lack_Pin, GPIO_PIN_SET);
		maca_rx_flag = 0;
		if(delay_time_1ms>0) delay_time_1ms--;
		HAL_GPIO_TogglePin(debug_tim3_GPIO_Port, debug_tim3_Pin);
		HAL_GPIO_WritePin(debug_allOK_GPIO_Port, debug_allOK_Pin, GPIO_PIN_RESET);
		/* send command to read absolute position of six legs */
		// HAL_UART_Transmit_IT(&huart1, read_absolute_position, 8);
		for(for_tim3=0; for_tim3<number_of_legs; for_tim3++)
		{
			uart_tx_buff_index = uart_tx_buff+(for_tim3*command_length);
			if(read_AbsolutePosition(for_tim3, &LDxxxE_protocol_struct_tx, uart_tx_buff_index)==0)
			{
				HAL_UART_Transmit_IT(huartX[for_tim3], uart_tx_buff_index, command_length);
				HAL_GPIO_WritePin(tx_gpio_debug_port[for_tim3], tx_gpio_debug_pin[for_tim3], GPIO_PIN_SET);
				// HAL_GPIO_WritePin(rx_gpio_debug_port[for_tim3], rx_gpio_debug_pin[for_tim3], GPIO_PIN_RESET);
			}
			else
			{
				/* To be added */
				// HAL_GPIO_WritePin(debug_lack_GPIO_Port, debug_lack_Pin, GPIO_PIN_SET);
			}
		}
	}

	/* if an interrupt occurs in TIM4 */
	if( htim->Instance == TIM4 )
	{
		HAL_GPIO_TogglePin(debug_tim4_GPIO_Port, debug_tim4_Pin);
		if( maca_rx_flag == maca_all_rx_flag )
		{
			HAL_TIM_Base_Stop_IT(htim);
			HAL_GPIO_WritePin(debug_allOK_GPIO_Port, debug_allOK_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(debug_tim4_GPIO_Port, debug_tim4_Pin, GPIO_PIN_RESET);
			decode_protocol();
			CDC_Transmit_FS(usb_tx_buff,27);
			// for(for_tim4=0; for_tim4<number_of_legs; for_tim4++)
			// 	CDC_Transmit_FS(&for_tim4,1);
		}
	}
}

/* USER CODE END 1 */
