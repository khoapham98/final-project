#include "led.h"
#include "clock.h"

void LED_Ctrl(LED_color_t color, LED_state_t state)
{
    uint32_t* GPIOD_ODR = (uint32_t*) (GPIOD_BASE_ADDR + 0x14); 
    if (state == LED_ON)
    {
        *GPIOD_ODR |= 1 << (12 + color); 
    }
    else 
    {
        *GPIOD_ODR &= ~(1 << (12 + color)); 
    }    
}

void LED_Init()
{
    AHB1_CLK_EN(AHB1_GPIOD);
    uint32_t* GPIOD_MODER = (uint32_t*) (GPIOD_BASE_ADDR + 0x00);
    /* set PD12, PD13, PD14, PD15 as OUTPUT */
    *GPIOD_MODER &= ~((0b11 << (12 * 2)) | (0b11 << (13 * 2)) | (0b11 << (14 * 2)) | (0b11 << (15 * 2))); 
    *GPIOD_MODER |= (0b01 << (12 * 2)) | (0b01 << (13 * 2)) | (0b01 << (14 * 2)) | (0b01 << (15 * 2)); 
}   
