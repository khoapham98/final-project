.PHONY: clean flash

FREERTOS_DIR=FreeRTOS
CC=arm-none-eabi-gcc
OBJ_DIR=build/obj
SRC_DIR=drivers/src
INC_DIR=drivers/inc
BIN_DIR=build/bin

OBJS=$(OBJ_DIR)/main.o $(OBJ_DIR)/startup.o \
	 $(OBJ_DIR)/uart.o $(OBJ_DIR)/led.o $(OBJ_DIR)/clock.o $(OBJ_DIR)/dma.o \
	 $(OBJ_DIR)/list.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/tasks.o $(OBJ_DIR)/port.o $(OBJ_DIR)/heap_4.o 

CFLAGS=-mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard -mcpu=cortex-m4 -std=gnu11 -I$(INC_DIR) -I$(FREERTOS_DIR)/include/ -I. -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/ -I$(FREERTOS_DIR)/config/

LDFLAGS=-T"STM32F411VETX_FLASH.ld" \
		-Wl,-Map="$(BIN_DIR)/output.map" -Wl,--gc-sections \
		-static -u _printf_float -specs=nano.specs -specs=nosys.specs 

all: $(BIN_DIR)/firmware.bin $(BIN_DIR)/firmware.elf

$(OBJ_DIR)/list.o: $(FREERTOS_DIR)/src/list.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/queue.o: $(FREERTOS_DIR)/src/queue.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/tasks.o: $(FREERTOS_DIR)/src/tasks.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/port.o: $(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/heap_4.o: $(FREERTOS_DIR)/portable/MemMang/heap_4.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/main.o: main.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/uart.o: $(SRC_DIR)/uart.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/led.o: $(SRC_DIR)/led.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/clock.o: $(SRC_DIR)/clock.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/dma.o: $(SRC_DIR)/dma.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_DIR)/startup.o: startup_stm32f411vetx.s
	$(CC) -c -x assembler-with-cpp $< -mcpu=cortex-m4 -std=gnu11 -o $@

$(BIN_DIR)/firmware.elf: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/firmware.elf
	arm-none-eabi-objcopy -O binary $(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.bin

clean:
	rm $(OBJ_DIR)/*.o 

flash:
	cmd.exe /c "STM32_Programmer_CLI -c port=SWD -e all -d $(BIN_DIR)/firmware.bin 0x08000000 -rst"
