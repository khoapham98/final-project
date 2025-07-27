FREERTOS_DIR=FreeRTOS
HEADER=-u _printf_float -specs=nano.specs -specs=nosys.specs -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard -mcpu=cortex-m4 -std=gnu11 -Idrivers/inc/ -I$(FREERTOS_DIR)/include/ -I. -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/ -I$(FREERTOS_DIR)/config/

all:
# build freeRTOS kernel
	arm-none-eabi-gcc -c $(FREERTOS_DIR)/src/list.c $(HEADER) -o build/obj/list.o
	arm-none-eabi-gcc -c $(FREERTOS_DIR)/src/queue.c $(HEADER) -o build/obj/queue.o
	arm-none-eabi-gcc -c $(FREERTOS_DIR)/src/tasks.c $(HEADER) -o build/obj/tasks.o
	arm-none-eabi-gcc -c $(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c $(HEADER) -o build/obj/port.o
	arm-none-eabi-gcc -c $(FREERTOS_DIR)/portable/MemMang/heap_4.c $(HEADER) -o build/obj/heap_4.o

# build application
	arm-none-eabi-gcc -c main.c $(HEADER) -o build/obj/main.o
	arm-none-eabi-gcc -c drivers/src/uart.c $(HEADER) -o build/obj/uart.o
	arm-none-eabi-gcc -c drivers/src/led.c $(HEADER) -o build/obj/led.o
	arm-none-eabi-gcc -c drivers/src/clock.c $(HEADER) -o build/obj/clock.o
	arm-none-eabi-gcc -c -x assembler-with-cpp startup_stm32f411vetx.s -mcpu=cortex-m4 -std=gnu11 -o build/obj/startup.o
	arm-none-eabi-gcc build/obj/*.o $(HEADER) -T"STM32F411VETX_FLASH.ld" -Wl,-Map="build/bin/output.map" -Wl,--gc-sections -static -o build/bin/firmware.elf
	arm-none-eabi-objcopy -O ihex build/bin/firmware.elf build/bin/firmware.hex
	arm-none-eabi-objcopy -O binary build/bin/firmware.elf build/bin/firmware.bin

clean:
	rm build/obj/*

flash:
	cmd.exe /c "STM32_Programmer_CLI -c port=SWD -e all -d build/bin/firmware.bin 0x08000000 -rst"
