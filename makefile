.PHONY: all clean flash

SRC_DIR := .
DRIVERS_SRC := drivers/src
INCLUDES := -Idrivers/inc
OBJ_DIR := build/obj
BIN_DIR := build/bin

C_SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(DRIVERS_SRC)/*.c)
ASM_SOURCE := startup_stm32f411vetx.s

C_OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(C_SOURCES)))
ASM_OBJECT := $(OBJ_DIR)/startup.o
OBJECTS := $(C_OBJECTS) $(ASM_OBJECT)

ELF := $(BIN_DIR)/firmware.elf
BIN := $(BIN_DIR)/firmware.bin

all: $(ELF) $(BIN)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/startup.o: $(ASM_SOURCE)
	@mkdir -p $(OBJ_DIR)
	arm-none-eabi-gcc -mcpu=cortex-m4 -x assembler-with-cpp -c $< -o $@

$(ELF): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	arm-none-eabi-gcc -mcpu=cortex-m4 -TSTM32F411VETX_FLASH.ld -Wl,-Map=$(BIN_DIR)/output.map -Wl,--gc-sections -static $^ -o $@

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -f $(OBJ_DIR)/*.o $(ELF) $(BIN)

flash: $(BIN)
	cmd.exe /c "STM32_Programmer_CLI -c port=SWD -e all -d $(BIN) 0x08000000 -rst"
