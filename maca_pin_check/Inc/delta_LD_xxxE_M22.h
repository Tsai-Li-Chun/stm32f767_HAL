/** ******************************************************
	* @file		delta_LD_xxxE_M22.h
	* @author	Tsai,Li-chun
	******************************************************
**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __delta_LD_xxxE_M22_H
#define __delta_LD_xxxE_M22_H

#ifdef __cplusplus
extern "C" {
#endif


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "stm32f4xx_hal_uart.h"
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */

#define command_length 8
#define response_max_length 100

/* define Delta LD-xxxE-M22 communication parameter */
#define __Model__ LD_100E_M22
#define __Reference_Distance__ 100
#define __Measurement_Rang__ 35
#define __BuatRate__ 115200
#define __DataLength__ UART_WORDLENGTH_8B
#define __StopBits__ UART_STOPBITS_1
#define __Parity__ UART_PARITY_NONE
#define __Mode__ UART_MODE_TX_RX

/* define Delta LD-xxxE-M22 communication address */
/* high 2byte is address, low 2byte is length and R/W */
#define __adr_deviceID__ 			(uint32_t)0x10000107
#define __adr_baud_rate__ 			(uint32_t)0x10020107
#define __adr_format__ 				(uint32_t)0x10030107
#define __adr_absolute_position__ 	(uint32_t)0x10040203
#define __adr_relative_position__ 	(uint32_t)0x10060203
#define __adr_set_zero_sw__ 		(uint32_t)0x10080107
#define __adr_set_zero_pos__ 		(uint32_t)0x10090203
#define __adr_lower_limit__			(uint32_t)0x100B0107
#define __adr_upper_limit__			(uint32_t)0x100D0107
#define __adr_PDweight_pos__		(uint32_t)0x100F0103
#define __adr_exposure_class__		(uint32_t)0x10100103
#define __adr_reaction_speed__		(uint32_t)0x10110107
#define __adr_moving_average__		(uint32_t)0x10120107
#define __adr_median_filter__		(uint32_t)0x10130107
#define __adr_out_delay_mode__		(uint32_t)0x10140107
#define __adr_out_delay_time__		(uint32_t)0x10150107
#define __adr_out_action__			(uint32_t)0x10160107
#define __adr_external_in__			(uint32_t)0x10170107
#define __adr_hysteresis__			(uint32_t)0x10180107
#define __adr_exposure_mode__		(uint32_t)0x10190107
#define __adr_exposure_hierarchy__	(uint32_t)0x101A0107
#define __adr_detection_out__		(uint32_t)0x101B0107
#define __adr_firmware_ver__		(uint32_t)0x101C0203
#define __adr_DO_status__			(uint32_t)0x101E0103
#define __adr_DI_status__			(uint32_t)0x101F0103
#define __adr_restore_factory__		(uint32_t)0x10C70106

/* define Delta LD-xxxE-M22 communication command */
#define __cmd_fc_read__		(uint8_t)0x03
#define __cmd_fc_write__	(uint8_t)0x06
#define __cmd_format_A8N1__ (uint8_t)0x01
#define __cmd_format_A8O1__ (uint8_t)0x02
#define __cmd_format_A8E1__ (uint8_t)0x03
#define __cmd_format_A8N2__ (uint8_t)0x04
#define __cmd_format_A8O2__ (uint8_t)0x05
#define __cmd_format_A8E2__ (uint8_t)0x06
#define __cmd_format_R8N1__ (uint8_t)0x07
#define __cmd_format_R8O1__ (uint8_t)0x08
#define __cmd_format_R8E1__ (uint8_t)0x09
#define __cmd_format_R8N2__ (uint8_t)0x0A
#define __cmd_format_R8O2__ (uint8_t)0x0B
#define __cmd_format_R8E2__ (uint8_t)0x0C
#define __cmd_format_A7O1__ (uint8_t)0x0D
#define __cmd_format_A7O2__ (uint8_t)0x0E
#define __cmd_format_A7E1__ (uint8_t)0x0F
#define __cmd_format_A7E2__ (uint8_t)0x10
#define __cmd_set_zero_OFF__ (uint8_t)0x00
#define __cmd_set_zero_ON__  (uint8_t)0x01
#define __cmd_reaction_speed_15__ (uint8_t)0x01
#define __cmd_reaction_speed_30__ (uint8_t)0x03
#define __cmd_reaction_speed_50__ (uint8_t)0x05
#define __cmd_moving_average_no__ (uint16_t)0x001
#define __cmd_moving_average_2__	(__cmd_moving_average_no__ <<1)
#define __cmd_moving_average_4__	(__cmd_moving_average_2__  <<1)
#define __cmd_moving_average_8__	(__cmd_moving_average_4__  <<1)
#define __cmd_moving_average_16__	(__cmd_moving_average_8__  <<1)
#define __cmd_moving_average_32__	(__cmd_moving_average_16__ <<1)
#define __cmd_moving_average_64__	(__cmd_moving_average_32__ <<1)
#define __cmd_moving_average_128__	(__cmd_moving_average_64__ <<1)
#define __cmd_moving_average_256__	(__cmd_moving_average_128__<<1)
#define __cmd_moving_average_512__	(__cmd_moving_average_256__<<1)
#define __cmd_median_filter_1__		(uint8_t)0x01
#define __cmd_median_filter_3__		(uint8_t)0x03
#define __cmd_median_filter_5__		(uint8_t)0x05
#define __cmd_median_filter_7__		(uint8_t)0x07
#define __cmd_median_filter_9__		(uint8_t)0x09
#define __cmd_median_filter_B__		(uint8_t)0x0B
#define __cmd_median_filter_D__		(uint8_t)0x0D
#define __cmd_out_delay_Nor__	(uint8_t)0x01
#define __cmd_out_delay_off__	(uint8_t)0x02
#define __cmd_out_delay_on__	(uint8_t)0x03
#define __cmd_out_delay_one__	(uint8_t)0x04
#define __cmd_out_action_NC__	(uint8_t)0x01
#define __cmd_out_action_NO__	(uint8_t)0x02
#define __cmd_external_in_no__		(uint8_t)0x01
#define __cmd_external_in_zero__	(uint8_t)0x02
#define __cmd_external_in_turn__	(uint8_t)0x03
#define __cmd_external_in_trigger__	(uint8_t)0x04
#define __cmd_exposure_mode_auto__	(uint8_t)0x01
#define __cmd_exposure_mode_manu__	(uint8_t)0x02
#define __cmd_Detection_General__	(uint8_t)0x00
#define __cmd_Detection_1point__	(uint8_t)0x01
#define __cmd_Detection_2point__	(uint8_t)0x02
#define __cmd_Detection_3point__	(uint8_t)0x03
#define __cmd_Restore_factory__		(uint8_t)0x01
/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */

/* declare the 6 legs as enum constants. */
typedef enum LEG
{
    leg_id1=0, leg_id2, leg_id3, leg_id4, leg_id5, leg_id6
} leg_id;

/* structure for the LDxxxEM22 communication protocol */
typedef struct
{
	uint8_t  id;
	uint8_t  fc;
	uint16_t length;
	uint16_t start_adr;
	uint16_t data;
	uint16_t crc;
}LDxxxEM22_protocol_structTYPE;

/* Extern Typedef End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */

/* all MACA 6 legs information obtained flag */
extern uint8_t maca_rx_flag;
/* structure for the LDxxxEM22 Tx communication protocol */
extern LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_tx;
/* structure for the LDxxxEM22 Rx communication protocol */
extern LDxxxEM22_protocol_structTYPE LDxxxE_protocol_struct_rx;

/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */

void delta_LD_xxxE_M22_uart_setup(UART_HandleTypeDef *huart);

void read_DeviceID(void);
void read_BaudRate(void);
void read_Format(void);
uint16_t  read_AbsolutePosition(uint8_t id, LDxxxEM22_protocol_structTYPE* xxxE, uint8_t* buff);
void read_RelativePosition(void);
void read_SetZeroSW(void);
void read_SetZeroPos(void);
void read_LowerLimit(void);
void read_UpperLimit(void);
void read_PDWeightPos(void);
void read_ExposureClass(void);
void read_ReactionSpeed(void);
void read_MovingAverage(void);
void read_MedianFilter(void);
void read_OutDelayMode(void);
void read_OutDelayTime(void);
void read_OutAction(void);
void read_ExternalIn(void);
void read_Hysteresis(void);
void read_ExposureMode(void);
void read_ExposureHierarchy(void);
void read_DetectionOut(void);
void read_FirmwareVer(void);
void read_DOStatus(void);
void read_DIStatus(void);

uint16_t set_DeviceID(uint8_t old_id, uint8_t new_id);
void set_BaudRate(void);
void set_Format(void);
void set_SetZeroSW(void);
void set_LowerLimit(void);
void set_UpperLimit(void);
void set_ReactionSpeed(void);
void set_MovingAverage(void);
void set_MedianFilter(void);
void set_OutDelayMode(void);
void set_OutDelayTime(void);
void set_OutAction(void);
void set_ExternalIn(void);
void set_Hysteresis(void);
void set_ExposureMode(void);
void set_ExposureHierarchy(void);
void set_DetectionOut(void);
void set_RestoreFactory(void);

uint8_t populate_LDxxxE_struct(uint8_t id,
							   uint8_t fc,
							   uint32_t adr,
							   uint16_t data,
							   LDxxxEM22_protocol_structTYPE* xxxE);
uint16_t populate_protocol(LDxxxEM22_protocol_structTYPE* xxxE, uint8_t* buff);
uint16_t decode_protocol(void);
uint16_t calculate_CRC(uint8_t* buff);
void verify_CRC(void);

/* Function End */


#ifdef __cplusplus
}
#endif

#endif /* __delta_LD_xxxE_M22_H */

/* ***** END OF delta_LD_xxxE_M22.H ***** */