/** ******************************************************
	* @file		gpio.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusion --------------------*/
#ifndef __TIM_H__
#define __TIM_H__

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
extern TIM_HandleTypeDef htim3;
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

void MX_TIM3_Init(void);

/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/* ***** END OF TIM.H ***** */