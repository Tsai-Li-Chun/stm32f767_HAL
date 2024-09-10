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

GPIO_TypeDef* tx_gpio_debug_port[number_of_legs] = {
	debug_tx1_GPIO_Port, debug_tx2_GPIO_Port, debug_tx3_GPIO_Port,
	debug_tx4_GPIO_Port, debug_tx5_GPIO_Port, debug_tx6_GPIO_Port	};
GPIO_TypeDef* rx_gpio_debug_port[number_of_legs] = {
	debug_rx1_GPIO_Port, debug_rx2_GPIO_Port, debug_rx3_GPIO_Port,
	debug_rx4_GPIO_Port, debug_rx5_GPIO_Port, debug_rx6_GPIO_Port	};

uint16_t      tx_gpio_debug_pin[number_of_legs] = {
	debug_tx1_Pin,	/* leg1 -> usart1, B0 B1 */
	debug_tx2_Pin,	/* leg2 -> usart2, B2 E7 */
	debug_tx3_Pin,	/* leg3 -> usart3, E8 E9 */
	debug_tx4_Pin,	/* leg4 -> uart4, E10 E11 */
	debug_tx5_Pin,	/* leg5 -> uart5, E12 E13 */
	debug_tx6_Pin,	/* leg6 -> usart6,E14 E15 */
};
uint16_t      rx_gpio_debug_pin[number_of_legs] = {
	debug_rx1_Pin,	/* leg1 -> usart1, B0 B1 */
	debug_rx2_Pin,	/* leg2 -> usart2, B2 E7 */
	debug_rx3_Pin,	/* leg3 -> usart3, E8 E9 */
	debug_rx4_Pin,	/* leg4 -> uart4, E10 E11 */
	debug_rx5_Pin,	/* leg5 -> uart5, E12 E13 */
	debug_rx6_Pin	/* leg6 -> usart6,E14 E15 */
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
	PA2   ------> USART2_TX
	PA3   ------> USART2_RX
	PB10   ------> USART3_TX
	PB11   ------> USART3_RX
	PC6   ------> USART6_TX
	PC7   ------> USART6_RX
	PA9   ------> USB_OTG_FS_VBUS
	PA10   ------> USB_OTG_FS_ID
	PA11   ------> USB_OTG_FS_DM
	PA12   ------> USB_OTG_FS_DP
	PC10   ------> UART4_TX
	PC11   ------> UART4_RX
	PC12   ------> UART5_TX
	PD2   ------> UART5_RX
*/
void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, debug_tx1_Pin|debug_tx2_Pin|debug_tx3_Pin|debug_tx4_Pin
							|debug_tx5_Pin|debug_tx6_Pin|debug_rx1_Pin|user1_Pin
							|user2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, debug_rx2_Pin|debug_rx3_Pin|user3_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, debug_rx4_Pin|debug_rx5_Pin|debug_rx6_Pin|debug_tim3_Pin
							|debug_tim4_Pin|debug_allOK_Pin|debug_lack_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : PCPin PCPin PCPin */
	GPIO_InitStruct.Pin = debug_tx1_Pin|debug_tx2_Pin|debug_tx3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PCPin PCPin PCPin PCPin */
	GPIO_InitStruct.Pin = debug_tx4_Pin|debug_tx5_Pin|debug_tx6_Pin|debug_rx1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PAPin PAPin */
	GPIO_InitStruct.Pin = debug_rx2_Pin|debug_rx3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin
							PBPin PBPin PBPin */
	GPIO_InitStruct.Pin = debug_rx4_Pin|debug_rx5_Pin|debug_rx6_Pin|debug_tim3_Pin
						 |debug_tim4_Pin|debug_allOK_Pin|debug_lack_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PCPin PCPin */
	GPIO_InitStruct.Pin = user1_Pin|user2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = user3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(user3_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = LD100E_ID1_in_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(LD100E_ID1_in_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin
							PBPin */
	GPIO_InitStruct.Pin = LD100E_ID2_in_Pin|LD100E_ID3_in_Pin|LD100E_ID4_in_Pin|LD100E_ID5_in_Pin
						  |LD100E_ID6_in_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
