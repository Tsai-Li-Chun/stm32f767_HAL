/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file    gpio.c
	* @brief   This file provides code for the configuration
	*          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "main.h"

GPIO_TypeDef* tx_gpio_debug_port[Number_of_LDxxxEM22] = {
	u1_tx_GPIO_Port, u2_tx_GPIO_Port, u3_tx_GPIO_Port, u4_tx_GPIO_Port, u5_tx_GPIO_Port, u6_tx_GPIO_Port	};
GPIO_TypeDef* rx_gpio_debug_port[Number_of_LDxxxEM22] = {
	u1_rx_GPIO_Port, u2_rx_GPIO_Port, u3_rx_GPIO_Port, u4_rx_GPIO_Port, u5_rx_GPIO_Port, u6_rx_GPIO_Port	};
uint16_t      tx_gpio_debug_pin[Number_of_LDxxxEM22] = {
	u1_tx_Pin,	/* leg1 -> usart1, B0 B1 */
	u2_tx_Pin,	/* leg2 -> usart2, B2 E7 */
	u3_tx_Pin,	/* leg3 -> usart3, E8 E9 */
	u4_tx_Pin,	/* leg4 -> uart4, E10 E11 */
	u5_tx_Pin,	/* leg5 -> uart5, E12 E13 */
	u6_tx_Pin,	/* leg6 -> usart6,E14 E15 */
};
uint16_t      rx_gpio_debug_pin[Number_of_LDxxxEM22] = {
	u1_rx_Pin,	/* leg1 -> usart1, B0 B1 */
	u2_rx_Pin,	/* leg2 -> usart2, B2 E7 */
	u3_rx_Pin,	/* leg3 -> usart3, E8 E9 */
	u4_rx_Pin,	/* leg4 -> uart4, E10 E11 */
	u5_rx_Pin,	/* leg5 -> uart5, E12 E13 */
	u6_rx_Pin	/* leg6 -> usart6,E14 E15 */
};
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
	* Analog
	* Input
	* Output
	* EVENT_OUT
	* EXTI
*/
void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, u1_tx_Pin|u1_rx_Pin|u2_tx_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, u2_rx_Pin|u3_tx_Pin|u3_rx_Pin|u4_tx_Pin
							|u4_rx_Pin|u5_tx_Pin|u5_rx_Pin|u6_tx_Pin
							|u6_rx_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, led_green_Pin|led_orange_Pin|led_red_Pin|led_blue_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = user_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(user_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin */
	GPIO_InitStruct.Pin = u1_tx_Pin|u1_rx_Pin|u2_tx_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PEPin PEPin PEPin PEPin
							PEPin PEPin PEPin PEPin
							PEPin */
	GPIO_InitStruct.Pin = u2_rx_Pin|u3_tx_Pin|u3_rx_Pin|u4_tx_Pin
						 |u4_rx_Pin|u5_tx_Pin|u5_rx_Pin|u6_tx_Pin
						 |u6_rx_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : PDPin PDPin PDPin PDPin */
	GPIO_InitStruct.Pin = led_green_Pin|led_orange_Pin|led_red_Pin|led_blue_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
