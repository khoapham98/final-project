#include "clock.h"
#include "timer.h"
static uint16_t tim_cnt = 0; 

void delay_sec(uint16_t sec)
{
	tim_cnt = 0; 
	while (tim_cnt < sec); 
}

void TIM1_UP_TIM10_IRQHandler()
{
	tim_cnt++;
	uint16_t* TIM1_SR = (uint16_t*) (TIM1_BASE_ADDR + 0x10);
	*TIM1_SR &= ~(1 << 0); 
} 

void TIM_Init()
{
	APB2_CLK_EN(APB2_TIM1);
	uint16_t* TIM1_PSC  = (uint16_t*) (TIM1_BASE_ADDR + 0x28);
	uint16_t* TIM1_CR1  = (uint16_t*) (TIM1_BASE_ADDR + 0x00);
	uint16_t* TIM1_ARR  = (uint16_t*) (TIM1_BASE_ADDR + 0x2C);
	uint16_t* TIM1_DIER = (uint16_t*) (TIM1_BASE_ADDR + 0x0C);
	uint32_t* NVIC_ISER0 = (uint32_t*) (0xE000E100);
	/* set CK_CNT = 1kHz */
	*TIM1_PSC = 16000 - 1;
	/* set auto-reload value */
	*TIM1_ARR = 1000;
	/* enable update interrupt */
	*TIM1_DIER |= 1 << 0; 
	/* interrupt set-enable */
	*NVIC_ISER0 |= 1 << 25; 
	/* enable counter */
	*TIM1_CR1 |= 1 << 0;
}
