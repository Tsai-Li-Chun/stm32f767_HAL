/** ******************************************************
	* @file		cas_macaps15.h
	* @author	Tsai,Li-chun
	******************************************************
**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __cas_macaps15_H
#define __cas_macaps15_H

#ifdef __cplusplus
extern "C" {
#endif


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "stm32f4xx.h"
#include "delta_LD_xxxE_M22.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define number_of_legs 6
#define maca_all_rx_flag (uint8_t)0x3F

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* if any of six legs of the maca receive an error flag */
extern uint8_t error_flag;

/* Extern Variables End */


/* Function ------------------ */
/* Function Begin */
/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __cas_macaps15_H */

/* ***** END OF cas_macaps15.H ***** */