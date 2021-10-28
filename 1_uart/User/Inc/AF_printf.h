/** ******************************************************
	* @file		AF_printf.h
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __AF_printf_H__
#define __AF_printf_H__

#ifdef __cplusplus
extern "C" {
#endif


/* System Includes ------------------------------------------*/
/* System Includes Begin */
#include "uart.h"
#include "stdio.h"
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */

// #pragma import(__use_no_semihosting)

/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

int _write(int, char*, int);

/* Function End */



#ifdef __cplusplus
}
#endif
#endif /*__ AF_printf_H__ */

/* ***** END OF AF_printf.H ***** */