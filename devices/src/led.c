#include <stdint.h>
#include "led.h"
#include "clock.h"
#include "uart.h"

LED_state_t stt[4] = { LED_OFF };
void LED_toggle(LED_color_t color)
{
	if (color == GREEN_LED) 
	{
		LED_Ctrl(color, stt[0]);
		stt[0] = (stt[0] == LED_ON) ? LED_OFF : LED_ON;
	}
	else if (color == ORANGE_LED) 
	{
		LED_Ctrl(color, stt[1]);
		stt[1] = (stt[1] == LED_ON) ? LED_OFF : LED_ON;
	}
	else if (color == RED_LED) 
	{
		LED_Ctrl(color, stt[2]);
		stt[2] = (stt[2] == LED_ON) ? LED_OFF : LED_ON;
	}
	else if (color == BLUE_LED) 
	{
		LED_Ctrl(color, stt[3]);
		stt[3] = (stt[3] == LED_ON) ? LED_OFF : LED_ON;
	}
}

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
