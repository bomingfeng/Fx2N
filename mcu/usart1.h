#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void USB2Serial_Init(uint8_t BaudRate);
static char *itoa(int value, char *string, int radix);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
uint8_t USART_Scanf(uint32_t value);

#endif /* __USART1_H */

