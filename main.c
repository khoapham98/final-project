#include <stdint.h>
#include "clock.h"
#include "led.h"
#include "projdefs.h"
#include "uart.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t task1;
TaskHandle_t task2; 

void task1_blink_red_led()
{
	int stt = LED_ON;
	UART_send_string("Task 1 khoi tao thanh cong\n");
	while (1) 
	{
		LED_toggle(RED_LED);
		vTaskDelay(1000);
	}
}

void task2_blink_blue_led()
{
	int stt = LED_ON;
	UART_send_string("Task 2 khoi tao thanh cong\n");
	while (1) 
	{
		LED_toggle(BLUE_LED);
		vTaskDelay(3000);
	}
}

int main()
{
	LED_Init();
	UART_Init();
	xTaskCreate(task1_blink_red_led, "task 1", 512, NULL, 0, &task1);	
	xTaskCreate(task2_blink_blue_led, "task 2", 512, NULL, 0, &task2);	
	UART_send_string("Tao 2 task thanh cong\n");
	vTaskStartScheduler();	
	while (1)
	{		
	
	}
}

void SystemInit() 
{
	
}
