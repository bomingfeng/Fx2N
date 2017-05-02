#ifndef __usartdma_H__
#define __usartdma_H__

#include "stm32f10x.h"

//USART 和 DMA 硬件初始化配置
 
void DMA_Uart_Init(void);
void LumMod_Uart_DAM_Tx_Over(void);
void LumMod_Uart_DMA_Rx_Data(void);


#endif

