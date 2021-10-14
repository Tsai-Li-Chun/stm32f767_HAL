/** ******************************************************
	* @file		define_gpio_nickname.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __define_gpio_nickname_H__
#define __define_gpio_nickname_H__

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

/* wake-up PA0 */
#define GPIO_Pin_WAUP GPIO_PIN_0
#define GPIO_Port_WAUP GPIOA

/* LED0(red) PB1, LED1(green) PB0 */
#define GPIO_Pin_LED0 GPIO_PIN_1
#define GPIO_Pin_LED1 GPIO_PIN_0
#define GPIO_Port_LED GPIOB

/* TTLtoUSB(USART1) PA9(Tx) PA10(Rx) */
#define GPIO_Pin_usart1_tx GPIO_PIN_9
#define GPIO_Pin_usart1_rx GPIO_PIN_10
#define GPIO_Port_usart1 GPIOA

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


#ifdef __cplusplus
}
#endif
#endif /*__ define_gpio_nickname_H__ */

/* ***** END OF define_gpio_nickname.H ***** */