/** ******************************************************
	* @file		cas_macaps15.c
	* @author	Tsai,Li-chun
	******************************************************
**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "cas_macaps15.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Variables ------------------------------------------------*/
/* Variables Begin */

/* all MACA 6 legs information obtained flag */
uint8_t maca_rx_flag = maca_all_rx_flag;
/* structure for the LDxxxEM22 Tx communication protocol */
LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_tx;
/* structure for the LDxxxEM22 Rx communication protocol */
LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_rx[number_of_legs];

// uint8_t tx_buff[1024];
// uint8_t rx_buff[1024];

/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

// /** * @brief  Program entry point.
//  	* @param argc(int) : Number of input parameters
//  	* @param argv(int) : input parameters
//  	* @return (int) Program Error.
// **	**/
// int main(int argc, char* argv[])
// {

// 	if(read_AbsolutePosition(leg_id1, &LDxxxE_protocol_struct_tx, tx_buff)==0)
// 	{
// 		printf("OK\n");
// 	}
// 	else
// 	{
// 		printf("ERROR\n");
// 	}

// 	return 0;
// }

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF cas_macaps15.C ***** */