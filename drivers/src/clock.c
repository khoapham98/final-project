#include "clock.h"

void AHB1_CLK_EN(AHB1_periph_t periph)
{
    uint32_t* RCC_AHB1ENR = (uint32_t*) (RCC_BASE_ADDR + 0x30);
    *RCC_AHB1ENR |= 1 << periph; 
}

void AHB2_CLK_EN(AHB2_periph_t periph)
{
    uint32_t* RCC_AHB2ENR = (uint32_t*) (RCC_BASE_ADDR + 0x34);
    *RCC_AHB2ENR |= 1 << periph;
}

void APB1_CLK_EN(APB1_periph_t periph)
{
    uint32_t* RCC_APB1ENR = (uint32_t*) (RCC_BASE_ADDR + 0x40);
    *RCC_APB1ENR |= 1 << periph;
}  

void APB2_CLK_EN(APB2_periph_t periph)
{
    uint32_t* RCC_APB2ENR = (uint32_t*) (RCC_BASE_ADDR + 0x44);
    *RCC_APB2ENR |= 1 << periph;
}  
