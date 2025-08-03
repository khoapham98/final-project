#include <stdint.h>
#include "clock.h"
#include "led.h"
#include "uart.h"
#include "dma.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t task1;
extern uint8_t LED;
extern uint8_t LED_stt;
extern const char* color_name[];
extern const char* stt_name[];

void task1_LED_Ctrl_via_UART()
{
	while (1) 
	{
		if (LED != 4) 
		{
			UART_send_string("%s led is %s\n", color_name[LED], stt_name[LED_stt]);
			LED_Ctrl(LED, LED_stt);
			vTaskDelay(1000);
		}
	}
}

int main()
{
	LED_Init();
	UART_Init();
	DMA_Init();
	xTaskCreate(task1_LED_Ctrl_via_UART, "task 1", 512, NULL, 0, &task1);	
	vTaskStartScheduler();	
	
	while (1)
	{		
		
	}
	return 0;
}

void SystemInit() 
{
	
}
