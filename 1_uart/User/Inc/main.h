/** ******************************************************
	* @file		main.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __MAIN_H
#define __MAIN_H

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
extern int delay_time;
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
void Error_Handler(void);
/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/* ***** END OF MAIN.H ***** */