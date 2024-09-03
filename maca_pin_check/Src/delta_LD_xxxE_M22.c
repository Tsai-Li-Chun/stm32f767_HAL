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

uint8_t fc_tmp;
uint16_t adr_tmp;
uint16_t len_tmp;
uint16_t tx_buff_index;
uint16_t rx_buff_index;
/* all MACA 6 legs information obtained flag */
uint8_t maca_rx_flag;
/* loop variable for for-loop */
uint8_t for_i,for_j;
/* structure for the LDxxxEM22 Tx communication protocol */
LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_tx;
/* structure for the LDxxxEM22 Rx communication protocol */
LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_rx;

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
uint16_t read_AbsolutePosition(uint8_t id, LDxxxEM22_protocol_structTYPE* xxxE, uint8_t* buff)
{
	if(populate_LDxxxE_struct(id, __cmd_fc_read__, __adr_absolute_position__, 0, xxxE)!=0)
		return 1;

	if(populate_protocol(xxxE,buff)!=0)
		return 1;

	return 0;
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

/** * @brief set new ID for LD-xxxE-M22.
 	* @param old_id(uint8_t) old id
 	* @param new_id(uint8_t) new id
 	* @return none
**/
uint16_t set_DeviceID(uint8_t old_id, uint8_t new_id)
{
	// return populate_protocol(old_id, __cmd_fc_write__, __adr_deviceID__, new_id);
	return 0;
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
 	* @param data(uint16_t) data to be written
 	* @param xxxE(LDxxxEM22_protocol_structTYPE*) LDxxxEM22 structure ptr
 	* @return error code
**/
uint8_t populate_LDxxxE_struct(uint8_t id, uint8_t fc,
							   uint32_t adr, uint16_t data,
							   LDxxxEM22_protocol_structTYPE* xxxE)
{
	adr_tmp = (uint16_t)(adr>>16);
	fc_tmp =(uint8_t)(adr&0x00000007);
	len_tmp =(uint16_t)((adr&0x0000FF00)>>8);

	/* check if the specified legs id meets the requirements */
	if( id>number_of_legs ) return 1;
	/* check if fc meets the requirements */
	if( fc_tmp == 0 ) return 2;
	if( (fc_tmp&fc) == 0 ) return 2;

	xxxE->id = (id+1);
	xxxE->fc = fc;
	xxxE->start_adr = adr_tmp;
	xxxE->length = len_tmp;
	xxxE->data = data;
	xxxE->crc = 0xFFFF;
	return 0;
}
/** * @brief populate the protocol according to the LDxxxEM22 structure
 	* @param xxxE(LDxxxEM22_protocol_structTYPE*) LDxxxEM22 structure ptr
 	* @param buff(uint8_t*) data array for transmission ptr
 	* @return data length
**/
uint16_t populate_protocol(LDxxxEM22_protocol_structTYPE* xxxE, uint8_t* buff)
{
	/* populate byte0 id */
	*(buff+0) = xxxE->id;
	/* populate byte1 fc */
	*(buff+1) = xxxE->fc;
	/* populate byte2 start address H */
	*(buff+2) = (uint8_t)((xxxE->start_adr&0xFF00)>>8);
	/* populate byte3 start address L */
	*(buff+3) =  (uint8_t)(xxxE->start_adr&0x00FF);
	if( xxxE->fc == __cmd_fc_read__ )
	{
		/* populate byte4 data length H */
		*(buff+4) = (uint8_t)((xxxE->length&0xFF00)>>8);
		/* populate byte5 data length L */
		*(buff+5) =  (uint8_t)(xxxE->length&0x00FF);
	}
	else if( xxxE->fc == __cmd_fc_write__ )
	{
		/* populate byte4 data H */
		*(buff+4) = (uint8_t)((xxxE->data&0xFF00)>>8);
		/* populate byte5 data L */
		*(buff+5) =  (uint8_t)(xxxE->data&0x00FF);
	}
	/* populate byte6-7 CRC code */
	if(calculate_CRC(buff)==0xFFFF)
		return 1;

	return 0;
}
/** * @brief decode the data received via UART interrupt.
 	* @param leg_id(uint8_t) LD_xxxE_M22 id, byte1
 	* @return execution result code
**/
uint16_t decode_protocol(void)
{
	usb_tx_buff[0] = 'C';
	for( for_i=0; for_i<number_of_legs; for_i++ )
	{
		usb_tx_buff[for_i*4+1] = uart_rx_buff[for_i*response_max_length+3];
		usb_tx_buff[for_i*4+2] = uart_rx_buff[for_i*response_max_length+4];
		usb_tx_buff[for_i*4+3] = uart_rx_buff[for_i*response_max_length+5];
		usb_tx_buff[for_i*4+4] = uart_rx_buff[for_i*response_max_length+6];
	}
	usb_tx_buff[25] = 'A';
	usb_tx_buff[26] = 'S';

	return 0;
}
/** * @brief Generate the CRC code according to 
 * 			 Delta's LD-xxxE-M22 CRC calculation rules
 	* @param buff(uint8_t*) original data without the appended CRC code
	* @param buff_index(uint16_t) start buff index
 	* @return uint8_t CRC code according to the calculate data
**/
uint16_t calculate_CRC(uint8_t* buff)
{
	uint16_t crc = 0xFFFF;
	uint8_t buff_index = 0;
	uint8_t buff_crc_index = command_length - 2;

	while( buff_index < buff_crc_index )
	{
		crc = crc ^ (*(buff+buff_index));
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
		buff_index++;
	}
	*(buff+buff_crc_index) = (uint8_t)(crc&0x00FF);
	*(buff+buff_crc_index+1) = (uint8_t)((crc&0xFF00)>>8);
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