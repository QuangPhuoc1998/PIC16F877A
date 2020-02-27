#ifndef _USART_H_
#define _USART_H_

void UART_Init(int baudRate);
void UART_TxChar(char ch);
char UART_RxChar();

#endif