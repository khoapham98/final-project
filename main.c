#include <stdint.h>
#include "clock.h"
#include "uart.h"
#include "dma.h"
#include "adc.h"
#include "led.h"
#include "temp_sensor.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t task1;
TaskHandle_t task2; 

extern uint8_t LED;
extern uint8_t LED_stt;
extern const char* color_name[];
extern const char* stt_name[];

void task2_read_MCU_temp()
{
	while (1)
	{
		float temp = get_mcu_temp();
		UART_send_string("STM32 temperature: %.2f\n", temp);
		vTaskDelay(1000);
	}
}

void task1_LED_Ctrl_via_UART()
{
	while (1) 
	{
		if (LED != 4) 
		{
			UART_send_string("%s led is %s\n", color_name[LED], stt_name[LED_stt]);
			LED_Ctrl(LED, LED_stt);
		}
		vTaskDelay(1000);
	}
}

int main()
{
	UART_Init();
	DMA_Init();
	ADC_Init();
	LED_Init();
	xTaskCreate(task1_LED_Ctrl_via_UART, "task 1", 512, NULL, 0, &task1);	
	xTaskCreate(task2_read_MCU_temp, "task 2", 128, NULL, 0, &task2);
	vTaskStartScheduler();	
	
	while (1)
	{		
		
	}
	return 0;
}

void SystemInit() 
{
	
}
