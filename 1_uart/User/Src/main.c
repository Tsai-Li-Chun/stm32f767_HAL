/** ******************************************************
	* @file		main.c
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
#include "gpio.h"
#include "tim.h"
#include "uart.h"
/* User Includes End */

/* Define ---------------------------------------------------*/
/* Define Begin */
/* Define End */

/* Typedef --------------------------------------------------*/
/* Typedef Begin */
/* Typedef End */

/* Variables ------------------------------------------------*/
/* Variables Begin */

/* 1ms delay 參數 */
int delay_time = 0;

/* Variables End */

/* Function -------------------------------------------------*/
/* Function Begin */

/* RCC時脈初始化函數 */
void systemClock_config(void);
/* 1ms delay函數 */
void delay_1ms(int);

/* Function End */

/* ---------------------------------------------------------*/
/* ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ Program ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩ ---------------------------*/
/* ---------------------------------------------------------*/
/* Program Begin */

/** * @brief  Program entry point.
 	* @param None
 	* @return (int) Program Error.
**	**/
int main(void)
{
	/* NVIC設定初始化 & systick初始化 */
	HAL_Init();
	/* RCC時脈初始化 */
	systemClock_config();
	/* GPIO初始化 */
	MX_GPIO_Init();
	/* TIM3初始化(尚未啟動) */
	MX_TIM3_Init();
	/* USART1初始化 */
	MX_USART1_Init();
	// /*  */
	HAL_UART_Receive_IT(&huart1, buf, uart1_rx_size);

	/* 啟動TIM3(連中斷一併啟動) */
	HAL_TIM_Base_Start_IT(&htim3);

	/* Infinite Loop */
	while (1)
	{		
		// for(int i=0;i<uart1_rx_size;i++)
		// 	buf[i] = 0;
		// HAL_UART_Receive(&huart1, buf, uart1_rx_size, 100);
		// HAL_UART_Transmit(&huart1, buf, uart1_rx_size, 100);
		HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED0);
		delay_1ms(100);
	}

	return 0;
}

/** * @brief  1ms delay 函數
 	* @param int n
 	* @return None
**	**/
void delay_1ms(int n)
{
	delay_time = n;
	while (delay_time > 0)
	{
	}
}

/** * @brief System Clock Configuration
	* @param None
	* @return None 
** */
void systemClock_config(void)
{
	/* 宣告OSC振盪器初始化用結構變數 */
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	/* 宣告AHB&APB時脈初始化用結構變數 */
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/* 啟動電源模組工作時脈 */
	__HAL_RCC_PWR_CLK_ENABLE();
	/* 設定電源模組穩壓輸出電壓等級(依照工作時脈不同) */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/* OSC振盪器初始化設定 */
	/* PLLCLK = (PLL_Source*N)/(M*P) */
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 192;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV8;
	// RCC_OscInitStruct.PLL.PLLQ = 2;
	/* 初始化並判斷若失敗進行錯誤處理 */
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		Error_Handler();

	/* 系統時脈初始化設定，AHB,APB等 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	/* 初始化並判斷若失敗進行錯誤處理 */
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
		Error_Handler();
}

/**	* @brief  This function is executed in case of error occurrence.
 * 	* @param None
	* @return None
**	**/
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

/* Program End */
/* ---------------------------------------------------------*/
/* ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ Program ⇧⇧⇧⇧⇧⇧⇧⇧⇧⇧ ---------------------------*/
/* ---------------------------------------------------------*/

/* --------------------------------------------------------- */
/* assert_failed De-Bag */
/* --------------------------------------------------------- */
#ifdef USE_FULL_ASSERT
/**	* @brief  Reports the name of the source file and the source line number
	*         where the assert_param error has occurred.
	* @param  file: pointer to the source file name
	* @param  line: assert_param error line source number
	* @return None
**	**/
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own imple mentation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* END USE_FULL_ASSERT */

/* ***** END OF MAIN.C ***** */