---
tags: ubuntu20, stm32, vscode, uart
---
ubuntu20 STM32HAL庫開發4 UART通訊
===


step1. 無中斷,最一般的阻塞式輪詢詢問旗標
---
程式流程大概為：
```c
設定UART工作參數(```MX_USART1_Init()```裡),鮑率,資料數,停止位元,奇偶檢查等
　　　⬇
呼叫```HAL_UART_Init()```函數,進行工作參數初始化設定
ps 另外此函數內正式改寫暫存器前會先呼叫```HAL_UART_MspInit()```進行其他硬體相關設定
　　開啟usart1工作時脈(```HAL_UART_MspInit()```裡)
　　　　　　　⬇
　　設定uart1的GPIO接腳參數(```HAL_UART_MspInit()```裡)
　　　　　　　⬇
　　呼叫```HAL_GPIO_Init()```函數進行uart1的GPIO接腳初始化
```

與之前[STM32HAL庫開發2](https://hackmd.io/VjA4kaMCR36zVAhcntwDaw)不一樣的是
Timer的話,初始化函數```HAL_TIM_Base_Init()```執行完後僅改變Timer暫存器值,並不會啟動Timer開始工作,還需額外下```HAL_TIM_Base_Start()```等啟動函數Timer才會正式工作。
Uart的話則與GPIO同樣,函數```HAL_UART_Init()```執行完後uart1就會啟動開始工作。

step2. 接收中斷,無DMA
---
step1步驟中所撰寫的UART工作參數設定函數```MX_USART1_Init()```無需更改,只需在```HAL_UART_MspInit()```裡新增開啟UART中斷的程式,然後在UART中斷callback函數裡撰寫中斷程式。

程式流程為：
2-1
```c
已step1的程式專案為基礎
先在HAL_UART_MspInit()裡結尾處新增以下兩行開啟中斷的程式，原程式原設定要保留
void HAL_UART_MspInit(UART_HandleTypeDef* hu) (撰寫在stm32f7xx_hal_msp.c裡)
   /* 設定CPU的USART1接收中斷優先度 */
　　HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
　　/* 開啟CPU的USART1中斷 */
　　HAL_NVIC_EnableIRQ(USART1_IRQn);
　　　⬇
回到main裡,在進入main-loop前開啟UART接收中斷
/* 開啟UART接收中斷函數 */
HAL_UART_Receive_IT(&huart1,buf,uart1_rx_size,100);
　　　⬇
在stm32f7xx_it.c裡新增如下中斷服務函數USART1_IRQHandler(),USART1_IRQHandler的名子可從.s檔裡尋得
void USART1_IRQHandler(void)
{
	/* USART1中斷請求處理函數 */
	HAL_UART_IRQHandler(&huart1);
}
HAL_UART_IRQHandler()裡會自動依據旗標來進入對應的callback。
```
HAL_UART_IRQHandler()裡的判斷順序有點複雜,在此另外拉出來說明
番外，經過一番"go to Definition"，一般情況下(無錯誤等)，```HAL_UART_IRQHandler()```會進入如下的if
```c
/* UART in mode Receiver ------------------------------------------*/
if (((isrflags & USART_ISR_RXNE) != 0U) && ((cr1its & USART_CR1_RXNEIE) != 0U))
{
    if (huart->RxISR != NULL)
        huart->RxISR(huart);    /* 若無錯誤會進入這函數(這函數被寫成指標型式) */
    return;
}
　　　⬇
huart->RxISR()是指標型式，指定過程如下
/* 首先從main的開啟UART接收中斷函數開始 */
HAL_UART_Receive_IT();
/* 再進入Start的啟動函數 */
return( UART_Start_Receive_IT() );
/* Start的啟動函數裡會依照資料bit數來指定對應的接收函數 */
if ( huart->Init.WordLength == UART_WORDLENGTH_9B )
    huart->RxISR = UART_RxISR_16BIT;
else
    huart->RxISR = UART_RxISR_8BIT; /* 8bit接收函數 */
　　　⬇
所以當UART接收中斷程式成立時，程式會自動跳到UART_RxISR_8BIT()裡
再來看看UART_RxISR_8BIT()裡幹了那些事情
static void UART_RxISR_8BIT(UART_HandleTypeDef *huart)
{
　　　.
    if (huart->RxXferCount == 0U)
    {
        /* 關閉各種中斷開關旗標 */
        CLEAR_BIT(USART_CR1_RXNEIE | USART_CR1_PEIE);
　　　　　　.
        /* 真正的中斷callback函數 */
        HAL_UART_RxCpltCallback(huart);
    }
　　　.
}
```
可以發現```UART_RxISR_8BIT()```裡會先關閉各種中斷開關旗標
然後跳到```HAL_UART_RxCpltCallback()```
所以```HAL_UART_RxCpltCallback()```才是我們要自行撰寫的中斷callback函數
而且因為```UART_RxISR_8BIT()```關閉了中斷開關旗標
所以我們要在中斷callback函數```HAL_UART_RxCpltCallback()```裡重新開啟
不然接收中斷只會進去第1次而已...
開啟方法就是重新呼叫開啟UART接收中斷函數```HAL_UART_Receive_IT()```。

重新回到2-1，並從2-1接續下去，知道中斷callback函數為```HAL_UART_RxCpltCallback()```之後，在**uart.c**裡新增```HAL_UART_RxCpltCallback()```函數，並撰寫中斷程式
```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hu)
{
    /* 因所有的UART接收中斷都會進到這函數，所以要加判斷是UARTx的if式 */
    if( hu->Instance == USART1 )
    {
	    HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED1);
    }
    /* 重新啟動MCU的UART接收中斷 */
    HAL_UART_Receive_IT();
}
```
從流程圖來看的話，大概像是這樣
![](https://i.imgur.com/3636qEy.png)





step2需要注意的是，目前使用的HAL的API是有固定長度的，資料數不到時不會進中斷，待下次的串列資料補足資料數之後才會進中斷，而多餘的資料則捨棄or觸發溢位錯誤。

step3. DMA接收中斷
---

step2步驟中所撰寫的UART工作參數設定函數```MX_USART1_Init()```無需更改，
```HAL_UART_MspInit()```裡新增DMA設定,然後在main中啟動DMA。

程式流程為：
3-1
```c
從step2的程式專案為基礎進行修改
先在HAL_UART_MspInit()裡新增以DMA設定函數，原程式原設定要保留
/* 因為Rx與Tx的DMA通道不一樣，所以要分開設定 */
DMA_UART1RX_Init(UART_HandleTypeDef*);
DMA_UART1TX_Init(UART_HandleTypeDef*);

以上兩個DMA設定函數撰寫在dma.c裡，內容以Rx舉例
void DMA_UART1RX_Init(UART_HandleTypeDef* hu)
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    hdma_uart1_rx.Instance = DMA2_Stream2;
    hdma_uart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_uart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_uart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_uart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if( HAL_DMA_Init(&hdma_uart1_rx) != HAL_OK )
        Error_Handler();
    __HAL_LINKDMA(hu,hdmarx,hdma_uart1_rx);
    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn,0,2);
    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}
Tx內容與Rx差不多，大致步驟為
開啟DMA2時脈 > DMA通道相關參數設定 > Init初始化 > UART&DMA結構變數連結 > CPU中斷設定啟動
```
3-2 在main-loop之前，啟動MCU的DMA中斷
```c
HAL_UART_Receive_DMA(&huart1,buf,uart1_rx_size);
```
3-3 經過一番"go to Definition"，發現DMA傳輸UART資料完畢後的的中斷callback就是step2裡的```HAL_UART_RxCpltCallback()```函數，而且因為3-1裡DMAmode設置為**DMA_CIRCULAR(循環模式)**，所以不需要在callback函數裡重新啟動。
```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hu)
{
    /* 因所有的UART接收中斷都會進到這函數，所以要加判斷是UARTx的if式 */
    if( hu->Instance == USART1 )
    {
	    HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED1);
    }
}
```
這裡解說一下"go to Definition"之後理解的MCU的UART中斷函數跳躍過程
3-番外-1
```c
DMA_UART1RX_Init(); > HAL_DMA_Init(); >設定Over
　　　⬇
/* 從main的啟動MCU的DMA中斷開始 */
HAL_UART_Receive_DMA(&huart1,buf,uart1_rx_size);
/* 呼叫啟動MCU的DMA中斷函數 */
UART_Start_Receive_DMA(huart, pData, Size)
    /* UART_Start_Receive_DMA()裡部分內容 */
    if (huart->hdmarx != NULL)
    {
        /* 指定DMA傳輸完成時的中斷函數的指標 */
        huart->hdmarx->XferCpltCallback = UART_DMAReceiveCplt;
        /* 指定DMA傳輸完成一半時的中斷函數的指標 */
        huart->hdmarx->XferHalfCpltCallback = UART_DMARxHalfCplt;
                .
                .
        /* 正式啟動MCU的DMA中斷 */
        if(HAL_DMA_Start_IT() != HAL_OK){...}
                .
                .
    }
```
上述可發現```huart->hdmarx->XferCpltCallback```被指向了函數```UART_DMAReceiveCplt()```的位址，接下來若是當UART的DMA傳輸完成後，函數的跳躍過程如下，3-番外-2
```c
/* DMA2-Stream2中斷服務函數 > DMA2-Stream2中斷處理函數 */
DMA2_Stream2_IRQHandler() > HAL_DMA_IRQHandler()
　　　⬇
    /* HAL_DMA_IRQHandler()裡部分內容 */
    if(hdma->XferCpltCallback != NULL)
    {   /* 當傳輸完成時 */
        /* Transfer complete callback */
        hdma->XferCpltCallback(hdma);
    }
```
從3-番外-1得知```hdma->XferCpltCallback``` **=** ```UART_DMAReceiveCplt()```
所以接下來我們來看看```UART_DMAReceiveCplt()```內容，3-番外-3
```c
static void UART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
                .
                .
    /* 如果DMA模式非循環模式時 */
    if (hdma->Init.Mode != DMA_CIRCULAR)
    {
                    .
                    .
        CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
        CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);
        CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);
                    .
                    .
    }

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
    {    /* 若有啟動空閒中斷 */
                    .
                    .
    }
    else
    {    /* 若無啟動空閒中斷 */
                    .
                    .
        HAL_UART_RxCpltCallback(huart);
                    .
    }
}
```
上述程式可以發現DMA的Mode設定成DMA_CIRCULAR的話不會進第1個if也就不會清除MCU的中斷旗標也就不需要重新啟動且最後的中斷callback函數又回到了MCU的UART的接收中斷callback函數```HAL_UART_RxCpltCallback()```了。所以```HAL_UART_RxCpltCallback()```可改成
```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hu)
{
	if( hu->Instance == USART1 )
		HAL_GPIO_TogglePin(GPIO_Port_LED, GPIO_Pin_LED1);
}
```
從流程圖來看的話，大概像是這樣
![](https://i.imgur.com/VuO24dc.png)

---
目前step1-3為固定長度收發

---
step4. UART1-DMA2，不定長度收發
---

STM官方HAL庫已經有提供相關API，不過位置放在較不常用的**stm32f7xx_hal_xxxx_ex.h**裡，有帶EX字樣的API都是較進階較不常用的。

設定初始化方面與step3的設定一模一樣，這樣稍微注意一下DMA中斷和UART中斷都要開啟，同時注意一下中斷優先級的設定不要設成同樣等級，以下程式片段參考

**stm32f7xx_hal_msp.c** 的 ```HAL_UART_MspInit()```裡，開啟CPU的UART中斷
```c
/* 設定CPU的USART1接收中斷優先度 */
HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
/* 開啟CPU的USART1中斷 */
HAL_NVIC_EnableIRQ(USART1_IRQn);
```
**dma.c** 的 ```DMA_UART1RX_Init()```裡，開啟CPU的DMA2-S2中斷
```c
/* 設定CPU的DMA2-S2接收中斷優先度 */
HAL_NVIC_SetPriority(DMA2_Stream2_IRQn,0,2);
/* 開啟CPU的DMA2-S2中斷 */
HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
```
**dma.c** 的 ```DMA_UART1TX_Init()```裡，開啟CPU的DMA2-S7中斷
```c
/* 設定CPU的DMA2-S7接收中斷優先度 */
HAL_NVIC_SetPriority(DMA2_Stream7_IRQn,0,2);
/* 開啟CPU的DMA2-S7中斷 */
HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
```
因為step3步驟中關閉UART中斷也能正常工作，所以為節省CPU資源有時會把UART中斷關閉，故若是偵測不定長度資料的話，要開啟UART中斷才能使用UART的IDLE中斷。

偵測不定長度的資料的方法主要利用STM32UART的IDLE中斷，IDLE中斷只有在資料傳輸後偵測到約1Byte的空閒信號後才會立起，相關開啟過程HAL庫包裝的差不多了，使用的API變成```HAL_UARTEx_ReceiveToIdle_DMA()```，**注意該副程式名子帶有Ex字樣！！！**

關於IDLE中斷的API的運作跳躍過程可參考 [STM32-UART接收不定长数据的三种方法](https://zhuanlan.zhihu.com/p/400728566)，裡面還實測了收完資料後觸發DMA中斷與觸發IDLE中斷的時間差！

來看一下main裡的UART-DMA-IDLE啟動函數```HAL_UARTEx_ReceiveToIdle_DMA``` 一些重點片段

```c
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
            .
            .
    /* 重點1，設定類型旗標成TOIDLE，step1-3都是STANDARD */
    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    /* step3裡也有出現的 啟動MCU-DMA函數 */
    status =  UART_Start_Receive_DMA(huart, pData, Size);
            .
    if (status == HAL_OK)
    {
        /* 這if重點2，上幾行剛設成TOIDLE，所以幾乎必進這if */
        if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
        {    /* 清除IDLE旗標 */
            __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_IDLEF);
            /* 啟動IDLE中斷 */
            SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
        }
        else
        {
                .
                .
        }
    }
    return status;
  }
        .
        .
}
```
在step3裡的```HAL_UART_Receive_DMA```也是呼叫```UART_Start_Receive_DMA()```這個函數來啟動DMA，這裡也是，只是```HAL_UARTEx_ReceiveToIdle_DMA()```多了重點1(設定類型旗標成TOIDLE)和重點2(清除IDLE旗標,啟動IDLE中斷)，然後就可以跳出函數進入main-loop了，事後後臺運行就會自動進入中斷了。

中斷成立的函數跳躍要分成2條線來看
1. 如果資料數有滿足規定，觸發DMA中斷
2. 如果資料數不足規定，觸發UART-IDLE中斷

先來看**資料數有滿足規定**，觸發DMA中斷時的情況，這裡和step3分析的一樣一陸進到```UART_DMAReceiveCplt()```函數裡，我們重新看一次step3的3-番外-3的程式段落
```c
/* DMA2-Stream2中斷服務函數 > DMA2-Stream2中斷處理函數 */
DMA2_Stream2_IRQHandler() > HAL_DMA_IRQHandler()
  　　　⬇  
static void UART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
                .
                .
    /* 如果DMA模式非循環模式時，關閉各種旗標 */
    if (hdma->Init.Mode != DMA_CIRCULAR)
    {
                    .
                    .
    }

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
    {    /* 這次進這裡，有啟動空閒中斷 */
                    .
        HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
                    .
    }
    else
    {    /* step3進的是這裡，無啟動空閒中斷 */
                    .
                    .
    }
}
```
若資料數有滿足規定，最後的進的callback函數是```HAL_UARTEx_RxEventCallback()```

再來看若**資料數不足規定**，傳送完畢後等到UART-IDLE觸發啟動的情況，這時觸發的是UART中斷，
```c
/* UART1中斷服務函數 > UART1中斷處理函數 */
USART1_IRQHandler()
  　　　⬇  
HAL_UART_IRQHandler()
{
                .
                .
    /* 重點if，若有啟動IDLE中斷 + 有起動DMA傳輸 */
    if ((huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) && ((isrflags & USART_ISR_IDLE) != 0U) && ((cr1its & USART_ISR_IDLE) != 0U))
    {
                    .
                    .
        if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
        {
                        .
                        .   
            /* 重點，關閉DMA */
            (void)HAL_DMA_Abort(huart->hdmarx);
            /* callback */
            HAL_UARTEx_RxEventCallback();
        }
    }
}
```
在重點if裡穿插著各種關閉旗標等有的沒的操作後，發現首先會關閉DMA控制器，然後才進callback函數，而且資料數不足規定的callback函數跟資料數有滿足規定進的callback函數一樣都是```HAL_UARTEx_RxEventCallback()```

所以得知```HAL_UARTEx_RxEventCallback()```就是我們這step4所使用的最終callback函數！！！

從流程圖來看的話，大概像是這樣
![](https://i.imgur.com/f0K1sD7.png)



http://lihgong.blogspot.com/2021/03/stm32-uart-dmahaltxrx.html

step5. 支援printf打印
---
直接參考下列網址
https://zhuanlan.zhihu.com/p/78986115
我的環境是ubuntu20 + gcc 所以要改造的函數是 **_write**！！
