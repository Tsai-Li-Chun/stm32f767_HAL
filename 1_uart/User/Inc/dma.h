/** ******************************************************
	* @file		dma.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __dma_H__
#define __dma_H__

#ifdef __cplusplus
extern "C" {
#endif


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "stm32f7xx_hal.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* DMA狀態結構變數 - uart1_rx用 */
extern DMA_HandleTypeDef hdma_uart1_rx;
/* DMA狀態結構變數 - uart1_tx用 */
extern DMA_HandleTypeDef hdma_uart1_tx;

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

/* UART1RX DMA Msp StartUp Configuration */
void DMA_UART1RX_Init(UART_HandleTypeDef*);
/* UART1TX DMA Msp StartUp Configuration */
void DMA_UART1TX_Init(UART_HandleTypeDef*);

/* Function End */


#ifdef __cplusplus
}
#endif
#endif /*__ dma_H__ */

/* ***** END OF dma.H ***** */