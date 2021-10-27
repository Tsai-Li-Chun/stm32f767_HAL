/** ******************************************************
	* @file		tim.c
	* @author	Tsai,Li-chun
	******************************************************
**	**/


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
#include "define_gpio_nickname.h"
#include "main.h"
#include "tim.h"
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

/* 宣告設定tim3計數參數用結構體 */
TIM_HandleTypeDef htim3;

/* Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */



/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief TIM3 Configuration
	*		 1ms Timer interrupt
	* @param None
	* @return None 
** */
void MX_TIM3_Init(void)
{
	/* 指定TIMx */
	htim3.Instance = TIM3;
	/* 設定計數模式-上數 */
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	/* 設定重裝載數值 */
	htim3.Init.Period = 9;
	/* 設定預分頻數值(除頻) */
	htim3.Init.Prescaler = 2399;
	/* 設定分頻因子(此參數在執行輸入捕獲才需使用,此外預設1即可) */
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	/* 設定是否自動重新填入重裝載值 */
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	/* 載入設定,若有錯進行錯誤處理 */
	if( HAL_TIM_Base_Init(&htim3) != HAL_OK )
		Error_Handler();

	/* 宣告設定tim3時脈用結構體 */
	TIM_ClockConfigTypeDef htim3_ClockStruct;
	/* 設定tim3時脈使用內部時脈來源(APB1) */
	htim3_ClockStruct.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	/* 載入設定,若有錯進行錯誤處理 */
	if( HAL_TIM_ConfigClockSource(&htim3, &htim3_ClockStruct) != HAL_OK )
		Error_Handler();

	/* 宣告設定tim3主從模式用結構體 */
	TIM_MasterConfigTypeDef htim3_MasterConfigStruct;
	/* 設定主從模式為關閉(獨立運作) */
	htim3_MasterConfigStruct.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	// /* 設定事件輸出為關閉(此輸出僅晶片內部使用,如ADC啟動觸發,其他計數器時脈等) */
	// htim3_MasterConfigStruct.MasterOutputTrigger = TIM_TRGO_RESET;
	/* 載入設定,若有錯進行錯誤處理 */
	if( HAL_TIMEx_MasterConfigSynchronization(&htim3, &htim3_MasterConfigStruct) != HAL_OK )
		Error_Handler();
}	

/** * @brief  Timer3 Period-Elapsed callback in non-blocking mode
	* @param TIM_HandleTypeDef*(pointer) 
	* @return None 
** */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* ht)
{
	/* 若tim3產生計數中斷 */
	if( ht->Instance == TIM3 )
	{
		/* delay_time減1 */
		if( delay_time>0 ) delay_time--;

		// /* 依按鈕狀態來點亮LED1 */
		// if( !(HAL_GPIO_ReadPin(GPIO_Port_WAUP,GPIO_Pin_WAUP)) )
		// 	HAL_GPIO_WritePin(GPIO_Port_LED,GPIO_Pin_LED1,GPIO_PIN_SET);
		// else
		// 	HAL_GPIO_WritePin(GPIO_Port_LED,GPIO_Pin_LED1,GPIO_PIN_RESET);
	}
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/


/* ***** END OF TIM.C ***** */
