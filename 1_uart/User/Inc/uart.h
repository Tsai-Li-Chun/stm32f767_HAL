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
#define uart1_rx_size 10
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
extern UART_HandleTypeDef huart1;
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