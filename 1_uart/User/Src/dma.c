/** ******************************************************
	* @file		dma.c.c
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define_gpio_nickname.h"
#include "main.h"
#include "dma.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Variables ------------------------------------------------*/
/* Variables Begin */

/* DMA狀態結構變數 - uart1_rx用 */
DMA_HandleTypeDef hdma_uart1_rx;
/* DMA狀態結構變數 - uart1_tx用 */
DMA_HandleTypeDef hdma_uart1_tx;

/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief UART1RX DMA Msp StartUp Configuration
	*		 RCC_CLK,UartLink,NVIC etc...
	* @param UART_HandleTypeDef*(pointer)
	* @return None 
** */
void DMA_UART1RX_Init(UART_HandleTypeDef* hu)
{
	/* 開啟DMA2工作時脈 */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* 設定DMA2的來源與通道為2-4 */
	hdma_uart1_rx.Instance = DMA2_Stream2;
	hdma_uart1_rx.Init.Channel = DMA_CHANNEL_4;
	/* 設定DMA2S2C4工作模式為循環模式 */
	hdma_uart1_rx.Init.Mode = DMA_CIRCULAR;
	/* 設定DMA2S2C4傳輸方向為外設to記憶體 */
	hdma_uart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	/* 設定S2C4外設地址不加1 */
	hdma_uart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	/* 設定S2C4記憶體地址每次加1 */
	hdma_uart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	/* 設定DMA2S2C4的來源外設的資料長度-8bit(byte) */
	hdma_uart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	/* 設定DMA2S2C4的目標記憶體的資料長度-8bit(byte) */
	hdma_uart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	/* 設定DMA2S2C4優先級為低 */
	hdma_uart1_rx.Init.Priority = DMA_PRIORITY_LOW;
	/* 關閉DMA2S2C4的FIFO */
	hdma_uart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	/* 載入設定到DMA2S2C4,若有錯進行錯誤處理 */
	if( HAL_DMA_Init(&hdma_uart1_rx) != HAL_OK )
		Error_Handler();

	/* UART1&DMA2S2C4-Rx結構變數連結 */
	__HAL_LINKDMA(hu,hdmarx,hdma_uart1_rx);

	/* 設定CPU的DMA2_Stream2(UART1-Rx)接收中斷優先度 */
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn,0,1);
	/* 開啟CPU的DMA2_Stream2(UART1-Rx)中斷 */
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}
/** * @brief UART1TX DMA Msp StartUp Configuration
	*		 RCC_CLK,UartLink,NVIC etc...
	* @param UART_HandleTypeDef*(pointer)
	* @return None 
** */
void DMA_UART1TX_Init(UART_HandleTypeDef* hu)
{
	/* 開啟DMA2工作時脈 */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* 設定DMA2的來源與通道為S7C4 */
	hdma_uart1_tx.Instance = DMA2_Stream7;
	hdma_uart1_tx.Init.Channel = DMA_CHANNEL_4;
	/* 設定DMA2S7C4工作模式為循環模式 */
	hdma_uart1_tx.Init.Mode = DMA_CIRCULAR;
	/* 設定DMA2S7C4傳輸方向為外設to記憶體 */
	hdma_uart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	/* 設定S7C4外設地址不加1 */
	hdma_uart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	/* 設定S7C4記憶體地址每次加1 */
	hdma_uart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	/* 設定DMA2S7C4的來源外設的資料長度-8bit(byte) */
	hdma_uart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	/* 設定DMA2S7C4的目標記憶體的資料長度-8bit(byte) */
	hdma_uart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	/* 設定DMA2S7C4優先級為低 */
	hdma_uart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	/* 關閉DMA2S7C4的FIFO */
	hdma_uart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	/* 載入設定到DMA2S7C4,若有錯進行錯誤處理 */
	if( HAL_DMA_Init(&hdma_uart1_tx) != HAL_OK )
		Error_Handler();

	/* UART1&DMA2S7C4-Tx結構變數連結 */
	__HAL_LINKDMA(hu,hdmatx,hdma_uart1_tx);

	/* 設定CPU的DMA2_Stream7(UART1-Tx)接收中斷優先度 */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn,0,2);
	/* 開啟CPU的DMA2_Stream7(UART1-Tx)中斷 */
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF dma.c.C ***** */