/** ******************************************************
	* @file		uart.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __uart_H__
#define __uart_H__

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
#define uart1_rx_max_size 255
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* uart1設定用結構體 */
extern UART_HandleTypeDef huart1;
/* uart資料接收陣列 */
extern uint8_t buf[uart1_rx_max_size];
/* uart1實際接收到的有效資料數 */
extern uint16_t uart1_rx_effective_size;

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

void MX_USART1_Init(void);

/* Function End */


#ifdef __cplusplus
}
#endif
#endif /*__ uart_H__ */

/* ***** END OF uart.H ***** */