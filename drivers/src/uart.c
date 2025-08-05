#include <stdint.h>
#include "clock.h"
#include "uart.h"
#include "dma.h"
#include <stdarg.h>
#include <led.h>
#include <string.h>
#include <stdio.h>

extern int LED; 
extern int LED_stt;
extern int update;
extern char rx_buf[];

const char* color_name[] = {"green", "orange", "red", "blue",
							"Green", "Orange", "Red", "Blue", 
							"GREEN", "ORANGE", "RED", "BLUE"};
const char* stt_name[] = {"off", "on", "Off", "On", "OFF", "ON"}; 

static void led_handle_data()
{
	int clen = sizeof(color_name) / sizeof(color_name[0]); 
	for (int i = 0; i < clen; i++) 
	{ 
		if (strstr(rx_buf, color_name[i])) 
		{
			if (i < 4) { LED = i; } 
			else if (i < 8) { LED = i - 4; } 
			else { LED = i - 8; } 
			break; 
		} 
	} 

	int slen = sizeof(stt_name) / sizeof(stt_name[0]); 
	for (int i = 0; i < slen; i++) 
	{ 
		if (strstr(rx_buf, stt_name[i])) 
		{ 
			if (i < 2) { LED_stt = i; } 
			else if (i < 4) { LED_stt = i - 2; } 
			else { LED_stt = i - 4; } 
			break; 
		} 
	}
}

static void data_process()
{
	if (strstr(rx_buf, "update"))
	{
		UART_send_string("please upload firmware!\n");
	}
	else if (strstr(rx_buf, "led") || strstr(rx_buf, "LED") || strstr(rx_buf, "Led"))
	{
		led_handle_data();
	}
	else 
	{
		update = READY;
	}
}

void USART1_IRQHandler()
{
	uint32_t* USART_SR = (uint32_t*) (USART1_BASE_ADDR + 0x00);
	uint32_t* USART_DR = (uint32_t*) (USART1_BASE_ADDR + 0x04);
	uint32_t* DMA_S2CR = (uint32_t*) (DMA2_BASE_ADDR + 0x10 + 0x18 * 2); 
	uint32_t* DMA_S2M0AR = (uint32_t*) (DMA2_BASE_ADDR + 0x1C + 0x18 * 2);
	uint32_t* DMA_S2NDTR = (uint32_t*) (DMA2_BASE_ADDR + 0x14 + 0x18 * 2);
	uint32_t* DMA_LIFCR  = (uint32_t*) (DMA2_BASE_ADDR + 0x08);
	uint32_t tmp;
	tmp = *USART_SR;
	tmp = *USART_DR;
	(void)tmp; 
	/* disable DMA */
	*DMA_S2CR &= ~(1 << 0); 
	/* clear interrupt flag */ 
	*DMA_LIFCR |= 1 << 21; 
	/* data process */
	data_process();
	/* set number of data */
	*DMA_S2NDTR = 0xffff;
	/* set dest addr */
	*DMA_S2M0AR = (uint32_t) rx_buf;
	if (update != READY)
	{
		int data_len = strlen(rx_buf);
		memset(rx_buf, 0, data_len);
	}
	/* enable DMA */ 
	*DMA_S2CR |= 1 << 0; 
}

static void UART_transmit(uint8_t data)
{
	uint32_t* USART_SR = (uint32_t*) (USART1_BASE_ADDR + 0x00);
	uint8_t*  USART_DR = (uint8_t*)  (USART1_BASE_ADDR + 0x04);
	*USART_DR = data; 
	while (((*USART_SR >> 7) & 1) == 0);
}

void UART_send_string(char* str, ...)
{
	va_list args; 
	va_start(args, str);
	char buf[64] = {0}; 
	vsprintf(buf, str, args); 
	uint32_t slen = strlen(buf);
	for (int i = 0; i < slen; i++)
	{
		UART_transmit(buf[i]);
	}
	va_end(args);
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
	uint32_t* USART_CR3 = (uint32_t*) (USART1_BASE_ADDR + 0x14);  	
	uint32_t* NVIC_ISER1 = (uint32_t*) (0xE000E104);
	/* word length = 9 data bits */
	*USART_CR1 |= 1 << 12; 
	/* enable parity */
	*USART_CR1 |= 1 << 10;
	/* enable transmitter & receiver */ 
	*USART_CR1 |= (1 << 2) | (1 << 3); 
	/* baud rate = 9600 bps */
	*USART_BRR  = (104 << 4) | ( 3 << 0);
	/* enable DMA receiver */
	*USART_CR3 |= 1 << 6; 
	/* enable IDLE interrupt */ 
	*USART_CR1 |= 1 << 4;  
	/* enable UART */
	*USART_CR1 |= 1 << 13;
	/* interrupt set enable */
	*NVIC_ISER1 |= 1 << (37 - 32); 
} 
