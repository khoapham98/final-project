#include <stdint.h>
#include "clock.h"
#include "uart.h"
#include "dma.h"
#include "adc.h"
#include "flash.h"
#include "led.h"
#include "temp_sensor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#define FW_SIZE	48036

TaskHandle_t task1;
TaskHandle_t task2; 
TaskHandle_t task3; 
SemaphoreHandle_t uart_lock; 

int LED = -1; 
int LED_stt = LED_OFF;
int update = IDLE; 
uint8_t rx_buf[50000] = {0};

void task3_update_fw_via_UART()
{
	while (1) 
	{
		if (update == READY)
		{
			if (xSemaphoreTake(uart_lock, 0xff) == pdTRUE)
			{
				update = IDLE;
				UART_send_string("Updating new firmware...\n");
				FLASH_update_fw(rx_buf, FW_SIZE);
			}
		}		
		vTaskDelay(1000);
	}
}

void task2_read_MCU_temp()
{
	TickType_t last_time = xTaskGetTickCount();
	while (1)
	{
		if (xSemaphoreTake(uart_lock, 500) == pdTRUE)
		{
			float temp = get_mcu_temp(); 
			UART_send_string("STM32 temperature: %.2f\n", temp); 
			xSemaphoreGive(uart_lock); 
		}
		vTaskDelayUntil(&last_time, 1000);
	}
}

void task1_LED_Ctrl_via_UART()
{
	while (1) 
	{
		if (LED != -1)
		{
			LED_Ctrl(LED, LED_stt); 
		}
		vTaskDelay(500);
	}
}

int main()
{
	UART_Init();
	DMA_Init();
	ADC_Init();
	LED_Init();
	UART_send_string("This is firmware ver 1.0\n");
	xTaskCreate(task1_LED_Ctrl_via_UART, "task 1", 512, NULL, 0, &task1);	
	xTaskCreate(task2_read_MCU_temp, "task 2", 512, NULL, 0, &task2);
	xTaskCreate(task3_update_fw_via_UART, "task 3", 512, NULL, 1, &task3);
	uart_lock = xSemaphoreCreateMutex();
	vTaskStartScheduler();	
	
	while (1)
	{		
		
	}
	return 0;
}

void SystemInit() 
{
	
}
