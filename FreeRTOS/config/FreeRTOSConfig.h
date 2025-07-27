#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// Core FreeRTOS configuration
#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define configUSE_PREEMPTION                1
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0
#define configCPU_CLOCK_HZ                  16000000
#define configTICK_RATE_HZ                  ((TickType_t)1000)
#define configUSE_16_BIT_TICKS              0
#define configMAX_PRIORITIES                5
#define configMINIMAL_STACK_SIZE            ((unsigned short)512)
#define configTOTAL_HEAP_SIZE               ((size_t)(40*1024))
#define configMAX_TASK_NAME_LEN             10
#define configIDLE_SHOULD_YIELD             1

// Synchronization objects
#define configUSE_MUTEXES                   1
#define configUSE_RECURSIVE_MUTEXES         1
#define configUSE_COUNTING_SEMAPHORES       1
#define configQUEUE_REGISTRY_SIZE           8

// Debug and safety (disabled for simplicity)
#define configCHECK_FOR_STACK_OVERFLOW      0
#define configUSE_MALLOC_FAILED_HOOK        0
#define configUSE_APPLICATION_TASK_TAG      0
#define configUSE_TRACE_FACILITY            1
#define configGENERATE_RUN_TIME_STATS       0

// Software timers (disabled)
#define configUSE_TIMERS                    0

// Co-routines (disabled)
#define configUSE_CO_ROUTINES               0
#define configMAX_CO_ROUTINE_PRIORITIES     2

// Include functions
#define INCLUDE_vTaskPrioritySet            1
#define INCLUDE_uxTaskPriorityGet           1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskCleanUpResources       1
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_vTaskDelayUntil             1
#define INCLUDE_vTaskDelay                  1

// ARM Cortex-M4 specific settings
#ifdef __NVIC_PRIO_BITS
#define configPRIO_BITS                     __NVIC_PRIO_BITS
#else
#define configPRIO_BITS                     4
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY     0xf
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5
#define configKERNEL_INTERRUPT_PRIORITY     (configLIBRARY_LOWEST_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY<<(8-configPRIO_BITS))

// Assertion macro
#define configASSERT(x) if((x)==0){taskDISABLE_INTERRUPTS();for(;;);}

// Map FreeRTOS handlers to CMSIS names
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
