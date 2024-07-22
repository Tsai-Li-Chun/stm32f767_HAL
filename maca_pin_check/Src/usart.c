/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file    usart.c
	* @brief   This file provides code for the configuration
	*          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "gpio.h"
#include "usbd_cdc_if.h"
#include "delta_LD_xxxE_M22.h"

uint16_t tx_buff_size = 0;
uint16_t rx_buff_size = 0;
uint8_t usb_tx_buff[tx_buff_max_size];
uint8_t uart_tx_buff[tx_buff_max_size];
uint8_t uart_rx_buff[rx_buff_max_size];
uint8_t read_absolute_position[8] = {0x01, 0x03, 0x10, 0x04, 0x00, 0x02, 0x81, 0x0A};
// uint8_t read_absolute_position[8] = {0x01, 0x06, 0x10, 0x00, 0x00, 0x01, 0x1D, 0x0A};
/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
UART_HandleTypeDef* huartX[Number_of_LDxxxEM22]={&huart1, &huart2, &huart3, &huart4, &huart5, &huart6};
// UART_HandleTypeDef* huartX[Number_of_LDxxxEM22];

/* UART4 init function */
void MX_UART4_Init(void)
{

	/* USER CODE BEGIN UART4_Init 0 */

	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */

	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart4);
	if (HAL_UART_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	// huartX[leg4] = &huart4;
	/* USER CODE END UART4_Init 2 */

}
/* UART5 init function */
void MX_UART5_Init(void)
{

	/* USER CODE BEGIN UART5_Init 0 */

	/* USER CODE END UART5_Init 0 */

	/* USER CODE BEGIN UART5_Init 1 */

	/* USER CODE END UART5_Init 1 */
	huart5.Instance = UART5;
	huart5.Init.BaudRate = 115200;
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.Mode = UART_MODE_TX_RX;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart5) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART5_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart5);
	if (HAL_UART_Init(&huart5) != HAL_OK)
	{
		Error_Handler();
	}
	// huartX[leg5] = &huart5;
	/* USER CODE END UART5_Init 2 */

}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart1);
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart2);
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart3);
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* USER CODE END USART3_Init 2 */

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 115200;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* use general settings within "delta_LD_xxxE_M22.h" to override,
	   without needing to open MX for rechanges. */
	delta_LD_xxxE_M22_uart_setup(&huart6);
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* USER CODE END USART6_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(uartHandle->Instance==UART4)
	{
	/* USER CODE BEGIN UART4_MspInit 0 */

	/* USER CODE END UART4_MspInit 0 */
		/* UART4 clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**UART4 GPIO Configuration
		PC10     ------> UART4_TX
		PC11     ------> UART4_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* UART4 interrupt Init */
		HAL_NVIC_SetPriority(UART4_IRQn, 8, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
	/* USER CODE BEGIN UART4_MspInit 1 */

	/* USER CODE END UART4_MspInit 1 */
	}
	else if(uartHandle->Instance==UART5)
	{
	/* USER CODE BEGIN UART5_MspInit 0 */

	/* USER CODE END UART5_MspInit 0 */
		/* UART5 clock enable */
		__HAL_RCC_UART5_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**UART5 GPIO Configuration
		PC12     ------> UART5_TX
		PD2     ------> UART5_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* UART5 interrupt Init */
		HAL_NVIC_SetPriority(UART5_IRQn, 9, 0);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
	/* USER CODE BEGIN UART5_MspInit 1 */

	/* USER CODE END UART5_MspInit 1 */
	}
	else if(uartHandle->Instance==USART1)
	{
	/* USER CODE BEGIN USART1_MspInit 0 */

	/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PB6     ------> USART1_TX
		PB7     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 4, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* USER CODE BEGIN USART1_MspInit 1 */

	/* USER CODE END USART1_MspInit 1 */
	}
	else if(uartHandle->Instance==USART2)
	{
	/* USER CODE BEGIN USART2_MspInit 0 */

	/* USER CODE END USART2_MspInit 0 */
		/* USART2 clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART2 interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	/* USER CODE BEGIN USART2_MspInit 1 */

	/* USER CODE END USART2_MspInit 1 */
	}
	else if(uartHandle->Instance==USART3)
	{
	/* USER CODE BEGIN USART3_MspInit 0 */

	/* USER CODE END USART3_MspInit 0 */
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART3 interrupt Init */
		HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
	/* USER CODE BEGIN USART3_MspInit 1 */

	/* USER CODE END USART3_MspInit 1 */
	}
	else if(uartHandle->Instance==USART6)
	{
	/* USER CODE BEGIN USART6_MspInit 0 */

	/* USER CODE END USART6_MspInit 0 */
		/* USART6 clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
	/* USER CODE BEGIN USART6_MspInit 1 */

	/* USER CODE END USART6_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==UART4)
	{
	/* USER CODE BEGIN UART4_MspDeInit 0 */

	/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
		PC10     ------> UART4_TX
		PC11     ------> UART4_RX
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

		/* UART4 interrupt Deinit */
		HAL_NVIC_DisableIRQ(UART4_IRQn);
	/* USER CODE BEGIN UART4_MspDeInit 1 */

	/* USER CODE END UART4_MspDeInit 1 */
	}
	else if(uartHandle->Instance==UART5)
	{
	/* USER CODE BEGIN UART5_MspDeInit 0 */

	/* USER CODE END UART5_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART5_CLK_DISABLE();

		/**UART5 GPIO Configuration
		PC12     ------> UART5_TX
		PD2     ------> UART5_RX
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

		/* UART5 interrupt Deinit */
		HAL_NVIC_DisableIRQ(UART5_IRQn);
	/* USER CODE BEGIN UART5_MspDeInit 1 */

	/* USER CODE END UART5_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART1)
	{
	/* USER CODE BEGIN USART1_MspDeInit 0 */

	/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PB6     ------> USART1_TX
		PB7     ------> USART1_RX
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
	/* USER CODE BEGIN USART1_MspDeInit 1 */

	/* USER CODE END USART1_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART2)
	{
	/* USER CODE BEGIN USART2_MspDeInit 0 */

	/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

		/* USART2 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART2_IRQn);
	/* USER CODE BEGIN USART2_MspDeInit 1 */

	/* USER CODE END USART2_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART3)
	{
	/* USER CODE BEGIN USART3_MspDeInit 0 */

	/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

		/* USART3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
	/* USER CODE BEGIN USART3_MspDeInit 1 */

	/* USER CODE END USART3_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART6)
	{
	/* USER CODE BEGIN USART6_MspDeInit 0 */

	/* USER CODE END USART6_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

		/* USART6 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);
	/* USER CODE BEGIN USART6_MspDeInit 1 */

	/* USER CODE END USART6_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/**
	* @brief  Tx Transfer completed callbacks.
	* @param  huart  Pointer to a UART_HandleTypeDef structure that contains
	*                the configuration information for the specified UART module.
	* @retval None
	*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);
	if( huart->Instance == USART1 )
	{
		HAL_GPIO_TogglePin(GPIOD, led_green_Pin);
	}
	else if( huart->Instance == USART2 )
	{
		HAL_GPIO_TogglePin(GPIOD, led_orange_Pin);
	}
	else if( huart->Instance == USART3 )
	{
		HAL_GPIO_TogglePin(GPIOD, led_red_Pin);
	}

	HAL_UARTEx_ReceiveToIdle_IT(huart, uart_rx_buff, rx_buff_max_size);
}
/**
	* @brief  Rx Transfer completed callbacks.
	* @param  huart  Pointer to a UART_HandleTypeDef structure that contains
	*                the configuration information for the specified UART module.
	* @retval None
	*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);
	if( huart->Instance == USART1 )
	{
		HAL_GPIO_TogglePin(GPIOD, led_orange_Pin);
		// HAL_UART_Receive_IT(&huart4, uart_rx_buff, rx_buff_size);
	}
}
/**
	* @brief  Reception Event Callback (Rx event notification called after use of advanced reception service).
	* @param  huart UART handle
	* @param  Size  Number of data available in application reception buffer (indicates a position in
	*               reception buffer until which, data are available)
	* @retval None
*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);
	UNUSED(Size);
	if( huart->Instance==USART1 )
	{
		if( (Size<rx_buff_max_size) )
		{
			// HAL_GPIO_TogglePin(GPIOD, led_orange_Pin);
			// CDC_Transmit_FS(usb_tx_buff, 7);
			// HAL_UARTEx_ReceiveToIdle_IT(&huart4, uart_rx_buff, rx_buff_max_size);
		}
	}
}

/* USER CODE END 1 */
