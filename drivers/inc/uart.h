#pragma once
#define USART1_BASE_ADDR 0x40011000
#define GPIOB_BASE_ADDR  0x40020400

void UART_send_string(char* str, ...);
void UART_Init();
