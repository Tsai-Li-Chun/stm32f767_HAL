/** ******************************************************
	* @file		uart.c
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "main.h"
#include "uart.h"
#include "define_gpio_nickname.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Variables ------------------------------------------------*/
/* Variables Begin */

/* usart1設定用結構體 */
UART_HandleTypeDef huart1;
/* uart資料接收陣列 */
uint8_t buf[uart1_rx_max_size] = {0};
/* uart1實際接收到的有效資料數 */
uint16_t uart1_rx_effective_size = 0;

/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief UART1 Configuration
	*		 TxRx,115200,8N1
	* @param None
	* @return None 
** */
void MX_USART1_Init(void)
{
	/* 指定USARTx */
	huart1.Instance = USART1;
	/* 指定USART1鮑率 */
	huart1.Init.BaudRate = 115200;
	/* 設定無硬體流控 */
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	/* 設定傳輸模式-TxRx都需 */
	huart1.Init.Mode = UART_MODE_TX_RX;
	/* 關閉雜訊偵測(打開的話1bit的16次採樣裡有1次電位不同就會跳錯) */
	huart1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
	/* 指定採樣頻率為1bit16次 */
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	/* 關閉奇偶校驗 */
	huart1.Init.Parity = UART_PARITY_NONE;
	/* 設定停止位1位 */
	huart1.Init.StopBits = UART_STOPBITS_1;
	/* 設定資料長度8bit */
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	/* 載入設定,若有錯進行錯誤處理 */
	if( HAL_UART_Init(&huart1)!=HAL_OK )
		Error_Handler();
}

/** * @brief  UART1 Rx Transfer completed callback.
	* @param UART_HandleTypeDef*(pointer) 
	* @return None 
** */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hu)
{
	/* 若USART1產生計數中斷 */
	if( hu->Instance == USART1 )
	{
		/* LED1反相，方便觀察 */
		HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED1);
	}
}

/** * @brief  UART1 Rx Event Callback.
	* @param hu UART_HandleTypeDef*
	* @param size uint16_t,Number of data available
	* @return None 
** */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* hu, uint16_t size)
{
	/* 若USART1產生計數中斷 */
	if( hu->Instance == USART1 )
	{
		/* 若資料數無超出最大數值-1 */
		if( size < (uart1_rx_max_size-1) )
		{
			/* 有效資料數賦值 */
			uart1_rx_effective_size = size;
			/* 資料串結尾補上字串結束符 */
			buf[uart1_rx_effective_size+1] = '\0';
			/* LED1反相，方便觀察 */
			HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED1);
			/* 重新啟動MCU的UART1-DMA2傳輸+傳輸完成中斷+IDLE中斷 */
			HAL_UARTEx_ReceiveToIdle_DMA(&huart1,buf,uart1_rx_max_size);
		}
	}	
}



/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF uart.C ***** */