/** ******************************************************
	* @file		gpio.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

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
#define GPIO_Pin_WAUP GPIO_PIN_0
#define GPIO_Port_WAUP GPIOA
#define GPIO_Pin_LED0 GPIO_PIN_1
#define GPIO_Pin_LED1 GPIO_PIN_0
#define GPIO_Port_LED GPIOB

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

void MX_GPIO_Init(void);

/* Function End */


#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/* ***** END OF GPIO.H ***** */