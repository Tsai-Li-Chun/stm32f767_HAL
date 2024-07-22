/** ******************************************************
	* @file		delta_LD_xxxE_M22.c
	* @author	Tsai,Li-chun
	******************************************************
**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
 #include <assert.h>
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
 	* @param huart(UART_HandleTypeDef*)
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

void read_DeviceID(void)
{

}
void read_BaudRate(void)
{

}
void read_Format(void)
{

}

/** * @brief read the absolute position
 	* @param id(uint8_t) LD_xxxE_M22 id
 	* @return  Non 8 is fail, 8 is success indicates data length
**/
uint16_t read_AbsolutePosition(uint8_t id)
{
	return populate_protocol(id, __cmd_fc_read__, __adr_absolute_position__, 2);
}

void read_RelativePosition(void)
{

}
void read_SetZeroSW(void)
{

}
void read_SetZeroPos(void)
{

}
void read_LowerLimit(void)
{

}
void read_UpperLimit(void)
{

}
void read_PDWeightPos(void)
{

}
void read_ExposureClass(void)
{

}
void read_ReactionSpeed(void)
{

}
void read_MovingAverage(void)
{

}
void read_MedianFilter(void)
{

}
void read_OutDelayMode(void)
{

}
void read_OutDelayTime(void)
{

}
void read_OutAction(void)
{

}
void read_ExternalIn(void)
{

}
void read_Hysteresis(void)
{

}
void read_ExposureMode(void)
{

}
void read_ExposureHierarchy(void)
{

}
void read_DetectionOut(void)
{

}
void read_FirmwareVer(void)
{

}
void read_DOStatus(void)
{

}
void read_DIStatus(void)
{

}

void set_DeviceID(void)
{

}
void set_BaudRate(void)
{

}
void set_Format(void)
{

}
void set_SetZeroSW(void)
{

}
void set_LowerLimit(void)
{

}
void set_UpperLimit(void)
{

}
void set_ReactionSpeed(void)
{

}
void set_MovingAverage(void)
{

}
void set_MedianFilter(void)
{

}
void set_OutDelayMode(void)
{

}
void set_OutDelayTime(void)
{

}
void set_OutAction(void)
{

}
void set_ExternalIn(void)
{

}
void set_Hysteresis(void)
{

}
void set_ExposureMode(void)
{

}
void set_ExposureHierarchy(void)
{

}
void set_DetectionOut(void)
{

}
void set_RestoreFactory(void)
{

}

/** * @brief populate the protocol according to the input parameters.
 	* @param id(uint8_t) LD_xxxE_M22 id, byte1
 	* @param fc(uint8_t) function code, read 0x03, write 0x06, byte2
 	* @param adr(uint32_t) start address, byte3-4
 	* @param len_or_data(uint16_t) whem read it's len, when write it's data, byte5-6
 	* @return Non 8 is fail, 8 is success indicates data length
**/
uint16_t populate_protocol(uint8_t id, uint8_t fc, uint32_t adr, uint16_t len_or_data)
{
	uint8_t adr_H = (uint8_t)((adr&0xFF000000)>>24);
	uint8_t adr_L = (uint8_t)((adr&0x00FF0000)>>16);
	uint8_t fc_tmp =(uint8_t)(adr&0x00000005);
	uint16_t len_tmp =(uint16_t)((adr&0x0000FF00)>>8);

	// /* check if the specified legs id meets the requirements */
	// if( (id<1) || (id>Number_of_LDxxxEM22) ) return 0;
	// /* check if fc meets the requirements */
	// if( ((fc!=__cmd_fc_read__)&&(fc!=__cmd_fc_write__)) || !(fc&fc_tmp) ) return 1;
	// /* check if len meets the requirements */
	// if( (fc==__cmd_fc_read__) && (len_or_data!=len_tmp) )  return 2;

	/* populate uart_tx_buff(protocol) */
	uart_tx_buff[0] = (uint8_t)(id+1);
	uart_tx_buff[1] = fc;
	uart_tx_buff[2] = adr_H;
	uart_tx_buff[3] = adr_L;
	uart_tx_buff[4] = (uint8_t)((len_or_data&0xFF00)>>8);
	uart_tx_buff[5] = (uint8_t)(len_or_data&0x00FF);
	calculate_CRC(uart_tx_buff, 6);
	// HAL_UART_Transmit_IT(&huart1, uart_tx_buff, 8);
	return command_length;
}

/** * @brief Generate the CRC code according to 
 * 			 Delta's LD-xxxE-M22 CRC calculation rules
 	* @param data(uint8_t*) original data without the appended CRC code
	* @param size(uint16_t) data length
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
	uart_tx_buff[6] = (uint8_t)(crc&0x00FF);
	uart_tx_buff[7] = (uint8_t)((crc&0xFF00)>>8);
	return crc;
}
/** * @brief 
 	* @param
 	* @return
**/
void verify_CRC(void)
{

}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF delta_LD_xxxE_M22.C ***** */