/** ******************************************************
	* @file		delta_LD_xxxE_M22.c
	* @author	Tsai,Li-chun
	******************************************************
**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "usart.h"
#include "usbd_cdc_if.h"
#include "delta_LD_xxxE_M22.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */


/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */


/* Variables ------------------------------------------------*/
/* Variables Begin */
/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief set UART-related communication interface parameters
 	* @param None
 	* @return None
**/
void delta_LD_xxxE_M22_uart_setup(UART_HandleTypeDef *huart)
{
	huart->Init.BaudRate = __BuatRate__;
	huart->Init.WordLength = __DataLength__;
	huart->Init.StopBits = __StopBits__;
	huart->Init.Parity = __Parity__;
	huart->Init.Mode = __Mode__;
}

/** * @brief Generate the CRC code according to 
 * 			 Delta's LD-xxxE-M22 CRC calculation rules
 	* @param uint8_t* original data without the appended CRC code
	* @param uint8_t data length
 	* @return uint8_t CRC code according to the calculate data
**/
uint16_t calculate_CRC(uint8_t* data, uint16_t size)
{
	uint16_t crc=0xFFFF;
	uint16_t size_tmp=0;

	while( size_tmp < size )
	{
		crc = crc ^ data[size_tmp];
		for(uint8_t i=0; i<8; i++)
		{
			if( crc & 0x0001 )
			{
				crc = crc >> 1;
				crc = crc ^ 0xA001;
			}
			else
				crc = crc >> 1;
		}
		size_tmp++;
	}	
	HAL_UART_Transmit(&huart4, (uint8_t*)&crc, 2, 100);
	return crc;
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF delta_LD_xxxE_M22.C ***** */