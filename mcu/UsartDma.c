#include "usartdma.h"

extern uint8_t PLC_UART_T_BUFFER[0x8f];
extern uint8_t PLC_UART_BUFFER[0x8f];	
extern  uint8_t PLC_UART_RECEIVE_CNT;

void DMA_Uart_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 开启DMA1时钟
	
	//=DMA_Configuration==============================================================================//
 
 	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
 	DMA_Cmd(DMA1_Channel4, DISABLE);                           // 关DMA通道
	DMA_DeInit(DMA1_Channel4);                                 // 恢复缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);// 设置串口发送数据寄存器
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)PLC_UART_T_BUFFER;         // 设置发送缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // 设置外设位目标，内存缓冲区 -> 外设寄存器
	DMA_InitStructure.DMA_BufferSize = 0X8F;                     // 需要发送的字节数，这里其实可以设置为0，因为在实际要发送的时候，会重新设置次值
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设地址不做增加调整，调整不调整是DMA自动实现的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存缓冲区地址增加调整
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度8位，1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存数据宽度8位，1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // 单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // 优先级设置
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 关闭内存到内存的DMA模式
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);               // 写入配置
	DMA_ClearFlag(DMA1_FLAG_GL4);                                 // 清除DMA所有标志
	DMA_Cmd(DMA1_Channel4, DISABLE); // 关闭DMA
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
    
	/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
	DMA_Cmd(DMA1_Channel5, DISABLE);                           // 关DMA通道
	DMA_DeInit(DMA1_Channel5);                                 // 恢复缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);// 设置串口接收数据寄存器
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)PLC_UART_BUFFER;         // 设置接收缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // 设置外设为数据源，外设寄存器 -> 内存缓冲区
	DMA_InitStructure.DMA_BufferSize = 0x8f;                     // 需要最大可能接收到的字节数
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // 外设地址不做增加调整，调整不调整是DMA自动实现的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 内存缓冲区地址增加调整
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度8位，1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 内存数据宽度8位，1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // 单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // 优先级设置
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // 关闭内存到内存的DMA模式
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);               // 写入配置
	DMA_ClearFlag(DMA1_FLAG_GL5);                                 // 清除DMA所有标志
	DMA_Cmd(DMA1_Channel5, ENABLE);                            // 开启接收DMA通道，等待接收数据
}

//============================================================//
//DMA 发送应用源码
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_FLAG_TC4))
	{
		LumMod_Uart_DAM_Tx_Over();
	}
}
void LumMod_Uart_DAM_Tx_Over(void)
{
	DMA_ClearFlag(DMA1_FLAG_GL4);         // 清除标志
	DMA_Cmd(DMA1_Channel4, DISABLE);   // 关闭DMA通道
}
	
//============================================================//
//DMA 接收应用源码
 void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  // 空闲中断
	{
		LumMod_Uart_DMA_Rx_Data();
		USART_ReceiveData( USART1 ); // Clear IDLE interrupt flag bit
	}
}
void LumMod_Uart_DMA_Rx_Data(void)
{
	uint8_t i;
	DMA_Cmd(DMA1_Channel5, DISABLE);       // 关闭DMA ，防止干扰
	DMA_ClearFlag( DMA1_FLAG_GL5 );           // 清DMA标志位
	PLC_UART_RECEIVE_CNT = 0x8F - DMA_GetCurrDataCounter(DMA1_Channel5); //获得接收到的字节数
	DMA1_Channel5->CNDTR = 0x8f;    //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目;
	for(i=0;i<PLC_UART_RECEIVE_CNT;i++)
		PLC_UART_BUFFER[i] &= 0x7f;
 /*	DMA_Cmd(DMA1_Channel5, ENABLE);      	 //DMA 开启，等待数据。注意，如果中断发送数据帧的速率很快，MCU来不及处理此次接收到的数据，中断又发来数据的话，这里不能开启，否则数据会被覆盖。有2种方式解决。
	1. 在重新开启接收DMA通道之前，将LumMod_Rx_Buf缓冲区里面的数据复制到另外一个数组中，然后再开启DMA，然后马上处理复制出来的数据。
	2. 建立双缓冲，在LumMod_Uart_DMA_Rx_Data函数中，重新配置DMA_MemoryBaseAddr 的缓冲区地址，那么下次接收到的数据就会保存到新的缓冲区中，不至于被覆盖。*/
}
