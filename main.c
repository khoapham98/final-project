#include "clock.h"
#include "led.h"
#include "timer.h"
#include "uart.h"

int main()
{
	TIM_Init();
	LED_Init();
	UART_Init();

	while (1)
	{		
		LED_Ctrl(BLUE_LED, LED_ON);
		delay_sec(2);
		UART_send_string("Blue led is on\n");
		LED_Ctrl(BLUE_LED, LED_OFF);
		delay_sec(2);
		UART_send_string("Blue led is off\n");
	}
	return 0; 
}

void SystemInit() 
{
	
}
