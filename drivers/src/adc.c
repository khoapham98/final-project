#include <stdint.h>
#include "clock.h"
#include "adc.h"

uint16_t ADC_read()
{
	uint16_t* ADC_JDR1 = (uint16_t*) (ADC1_BASE_ADDR + 0x3C);
	uint32_t* ADC_SR   = (uint32_t*) (ADC1_BASE_ADDR + 0x00);
	uint32_t* ADC_CR2  = (uint32_t*) (ADC1_BASE_ADDR + 0x08);
	/* start conversion */
	*ADC_CR2 |= 1 << 22; 
	/* wait until the conversion is completed & clear flag */ 
	while (((*ADC_SR >> 2) & 1) == 0);
	*ADC_SR &= ~(1 << 2);
	/* return ADC value */ 
	return *ADC_JDR1;
}

void ADC_Init()
{
	APB2_CLK_EN(APB2_ADC1);
	uint32_t* ADC_SMPR1 = (uint32_t*) (ADC1_BASE_ADDR + 0x0C);
	uint32_t* ADC_CCR	= (uint32_t*) (ADC1_BASE_ADDR + 0x04 + 0x300);
	uint32_t* ADC_CR2	= (uint32_t*) (ADC1_BASE_ADDR + 0x08);
	uint32_t* ADC_JSQR	= (uint32_t*) (ADC1_BASE_ADDR + 0x38); 
	/* select 1 conversion */ 
	*ADC_JSQR &= ~(0b11 << 20);
	/* select channel 16 on 4th conversion */ 
	*ADC_JSQR |= 16 << 15;
	/* select ADC CLK = 15 cycles */ 
	*ADC_SMPR1 |= 0b001 << 18;
	/* wake up temperature sensor */ 
	*ADC_CCR |= 1 << 23; 
	/* enable ADC */ 
	*ADC_CR2 |= 1 << 0; 
}
