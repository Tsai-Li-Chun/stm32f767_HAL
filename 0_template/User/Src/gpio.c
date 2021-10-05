/** ******************************************************
	* @file		gpio.c
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "gpio.h"
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

/** * @brief GPIO Configuration
	* @param None
	* @return None 
** */
void MX_GPIO_Init(void)
{
	/* 宣告GPIO初始化用結構變數 */
	GPIO_InitTypeDef GPIO_InitStruct={0};
	/* 開啟GPIOx工作時脈 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	// __HAL_RCC_GPIOH_CLK_ENABLE();

	/* 設定輸入模式 */
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	/* 設定下拉電阻 */
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	/* 設定接腳 */
	GPIO_InitStruct.Pin = GPIO_Pin_WAUP;
	/* 載入設定 */
	HAL_GPIO_Init(GPIO_Port_WAUP,&GPIO_InitStruct);

	/* 設定輸出模式 */
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	/* 設定輸出翻轉速度 */
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	/* 設定接腳 */
	GPIO_InitStruct.Pin = GPIO_Pin_LED0|GPIO_Pin_LED1;
	/* 載入設定 */
	HAL_GPIO_Init(GPIO_Port_LED,&GPIO_InitStruct);

	/* 設定輸出接腳初始電位 */
	HAL_GPIO_WritePin(GPIO_Port_LED,GPIO_Pin_LED0|GPIO_Pin_LED1,GPIO_PIN_SET);
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF GPIO.C ***** */