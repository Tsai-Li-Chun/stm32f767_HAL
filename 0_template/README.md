---
tags: ubuntu20, stm32
---
ubuntu20 STM32HAL庫開發2 模板建立&程式流程解說
===
此模板是先從cube建立的專案修改而來的，功能為GPIO+Timer3中斷做Delay。
本文的主要內容為針對程式流程做說明，因為模板的建立沒什麼難度。

**step1.文件樹說明**
---
STM32F767_HAL(工作資料夾)
> .vscode(設定檔)

> 0_Template(模板)
>> build(編譯二進制檔)
>> Makefile
>> README(說明，可無)
>> User
>>> Inc(.h資料夾)
>>> Src(.c資料夾)

> 1_GPIO(專案1)

> 2_XXXX(專案2)

> STM32F767_Library(STM系統函數庫)

STM32F767_Library裡的文件都不會更改到，可供程式開發者新增撰寫或更改的文件全都會放在專案資料夾裡的User資料夾。

**step2. 模板程式流程解說**
---

***標頭檔include事前說明***
有兩個.h檔需要注意，為stm32f7xx_hal.h和stm32f7xx_hal_conf.h。
每個會使用的stm32硬體的.h.c文件皆需要include"stm32f7xx_hal.h"這個標頭檔。
stm32f7xx_hal.h裡會再include"stm32f7xx_hal_conf.h"
stm32f7xx_hal_conf裡37-86行的程式應該長這樣
```c
#define HAL_MODULE_ENABLED
/* #define HAL_ADC_MODULE_ENABLED   */
/* #define HAL_CRYP_MODULE_ENABLED   */
        ..
        ..
        ..
#define HAL_PWR_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
```
```c
#ifdef HAL_ADC_MODULE_ENABLED
    #include "stm32f7xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */
```
從上面兩段可以看出要使用哪些外設只要把相對應的HAL_XXX_MODULE_ENABLED的註解打開就只會include相對應的.h檔進來。

stm32f7xx_hal.h是stm32本身的系統標頭檔，不可更改，故存放位置在STM32F767_Library(STM系統函數庫)裡。
stm32f7xx_hal_conf.h雖然是stm32官方提供的，但需要程式開發者自行決定HAL_XXX_MODULE_ENABLED註解是否打開，所以存放位置在User的Inc裡。

***流程解說***
與SPL庫不同，HAL庫預設開啟SysTick並1ms中斷作Delay。
基本啟動所需要開啟的外設與API也不同。

從main開始
```c
/* HAL基本系統初始化 */
HAL_Init(); (撰寫在stm32f7xx_hal.c裡)
    /* 設定中斷優先群組 */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    /* 初始化SysTick */
    HAL_InitTick(TICK_INT_PRIORITY);
    /* 初始化底層硬體相關 */
    /* 在stm32f7xx_hal.c裡使用__weak定義成弱函數 */
    /* stm32f7xx_hal_msp.c裡取代掉__weak的弱函數 */
    HAL_MspInit();
        /* HAL庫的外設時脈開啟方式改成如下這樣 */
        /* 一般外設都需要初始化，故會順便在該外設的初始化函數裡開啟時脈 */        
        /* 但PWR(電源管理)SYSCFG(外部中斷管理)不需要初始化卻預設關閉 */
        /* 故官方將這兩行另外在HAL_MspInit()裡單獨寫出，避免程式開發者忘記開啟 */
        /* 程式開發者日後有啥底層硬體相關的初始化可在HAL_MspInit()裡撰寫 */
        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_RCC_SYSCFG_CLK_ENABLE();
/* RCC初始化 */
SystemClock_Config();
/* 各種外設初始化 */
MX_GPIO_Init();
MX_TIM3_Init();
    .
    .
MX_XXXX_Init();
/* 有些外設需另外啟動(or+中斷) */
MX_XXXX_Start(); //(僅啟動)
    .
MX_XXXX_Start_IT(); //(連中斷一併啟動)
/* Infinite loop */
while(1){...}
```

**step3. SystemClock & GPIO初始設定解說**
---
SystemClock的設定很簡單的，就不說明了。
模板的GPIO只有設定輸入輸出，很簡單的，就不說明了。

**step4. Timer設定+計時中斷設定解說**
---
程式流程大概為
```c
設定timer計數參數(```MX_TIM3_Init()```裡)
　　　⬇
呼叫```HAL_TIM_Base_Init()```函數,進行計數參數初始化設定
ps 另外此函數內正式改寫暫存器前會先呼叫```HAL_TIM_Base_MspInit()```進行其他硬體相關設定
　　開啟timer工作時脈(```HAL_TIM_Base_MspInit()```裡)
　　　　　　　⬇
　　設定中斷優先級並開啟(```HAL_TIM_Base_MspInit()```裡)
　　　　　　　⬇
設定timer時脈來源(使用```HAL_TIM_ConfigClockSource()```)
　　　⬇
設定timer主從計數觸發(使用```HAL_TIMEx_MasterConfigSynchronization()```)
　　　⬇
啟動計時器or加中斷(使用```HAL_TIM_Base_Start()```or```HAL_TIM_Base_Start_IT()```)
```
**step5. Timer計時中斷程式**
---
程式流程大概為
新增中斷函數```TIM3_IRQHandler```(stm32f7xx_it.c裡)
```c
void TIM3_IRQHandler(void)
{
    /* 中斷請求處理函數 - 判斷中斷旗標來調用對應的callback */
    HAL_TIM_IRQHandler(&htim3);
}
```
中斷函數名稱```TIM3_IRQHandler```有規定,請從startup_stm32f767xx.s裡找出可使用的函數名稱。
接著```TIM3_IRQHandler```內部判斷中斷旗標,依中斷旗標來調用對應的callback函數。
　　　⬇
不同的中斷有不同的callback函數,計數中斷的callback函數為```HAL_TIM_PeriodElapsedCallback```,此callback函數才是真正中斷程式的撰寫位置。
```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* ht)
{
    if( ht->Instance == TIMx )
    {
        /* 中斷程式打在這裡 */
    }
}
```
需注意的是不管任何的TIMER的計數中斷產生都會進來這callback函數,所以要加上```if(ht->Instance==TIMx)```以防TIM2的計數中斷進到TIM3裡。

