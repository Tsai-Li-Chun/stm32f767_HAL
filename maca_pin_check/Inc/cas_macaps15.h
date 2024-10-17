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

/* declare the 6 legs as enum constants. */
typedef enum LEG
{
    leg_id1=0, leg_id2, leg_id3, leg_id4, leg_id5, leg_id6
} leg_id;

/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* all MACA 6 legs information obtained flag */
extern uint8_t maca_rx_flag;
/* structure for the LDxxxEM22 Tx communication protocol */
extern LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_tx;
/* structure for the LDxxxEM22 Rx communication protocol */
extern LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_rx[number_of_legs];

/* Extern Variables End */


/* Function ------------------ */
/* Function Begin */
/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __cas_macaps15_H */

/* ***** END OF cas_macaps15.H ***** */