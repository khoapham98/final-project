#pragma once
#include <stdint.h>
#define ADC1_BASE_ADDR 0x40012000
uint16_t ADC_read();
void ADC_Init();
