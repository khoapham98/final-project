#include "clock.h"
#include "uart.h"

static void UART_transmit(uint8_t data);
static uint32_t getlen(char* str)
{
	uint32_t cnt = 0; 
	while (str[cnt] != 0)
	{
		cnt++;
	}
	return cnt; 
}

void UART_send_string(char* str)
{
	uint32_t strlen = getlen(str);
	for (int i = 0; i < strlen; i++)
	{
		UART_transmit(str[i]);
	}
}

static void UART_transmit(uint8_t data)
{
	uint32_t* USART_SR = (uint32_t*) (USART1_BASE_ADDR + 0x00);
	uint8_t*  USART_DR = (uint8_t*)  (USART1_BASE_ADDR + 0x04);
	*USART_DR = data; 
	while (((*USART_SR >> 7) & 1) == 0);
}

void UART_Init()
{
	AHB1_CLK_EN(AHB1_GPIOB); 
	uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRL  = (uint32_t*) (GPIOB_BASE_ADDR + 0x20);	
	/* config PB6 & PB7 at AF mode */
	*GPIOB_MODER &= ~((0b11 << (6 * 2)) | (0b11 << (7 * 2))); 
	*GPIOB_MODER |= (0b10 << (6 * 2)) | (0b10 << (7 * 2)); 
	/* select AF07 */
	*GPIOB_AFRL &= ~((0xf << (6 * 4)) | (0xf << (7 * 4)));
	*GPIOB_AFRL |= (7 << (6 * 4)) | (7 << (7 * 4)); 

	APB2_CLK_EN(APB2_USART1);
	uint32_t* USART_CR1 = (uint32_t*) (USART1_BASE_ADDR + 0x0C);
	uint32_t* USART_BRR = (uint32_t*) (USART1_BASE_ADDR + 0x08);  
	/* word length = 9 data bits */
	*USART_CR1 |= 1 << 12; 
	/* enable parity */
	*USART_CR1 |= 1 << 10;
	/* enable transmitter & receiver */ 
	*USART_CR1 |= (1 << 2) | (1 << 3); 
	/* baud rate = 9600 bps */
	*USART_BRR  = (104 << 4) | ( 3 << 0);
	/* enable UART */
	*USART_CR1 |= 1 << 13;
} 
