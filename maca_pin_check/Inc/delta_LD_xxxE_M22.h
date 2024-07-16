/** ******************************************************
	* @file		delta_LD_xxxE_M22.h
	* @author	Tsai,Li-chun
	******************************************************
**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __delta_LD_xxxE_M22_H
#define __delta_LD_xxxE_M22_H

#ifdef __cplusplus
extern "C" {
#endif


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "stm32f4xx_hal_uart.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define __Model__ LD_100E_M22
#define __Reference_Distance__ 100
#define __Measurement_Rang__ 35
#define __BuatRate__ 115200
#define __DataLength__ UART_WORDLENGTH_8B
#define __StopBits__ UART_STOPBITS_1
#define __Parity__ UART_PARITY_NONE
#define __Mode__ UART_MODE_TX_RX

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */

void delta_LD_xxxE_M22_uart_setup(UART_HandleTypeDef *huart);
uint16_t calculate_CRC(uint8_t* data, uint16_t size);

/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __delta_LD_xxxE_M22_H */

/* ***** END OF delta_LD_xxxE_M22.H ***** */