.PHONY: clean flash

all: obj/main.o obj/led.o obj/clock.o obj/timer.o obj/uart.o obj/startup.o bin/firmware.elf  

obj/main.o: src/main.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -Iinc -c src/main.c -o obj/main.o

obj/led.o: src/led.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -Iinc -c src/led.c -o obj/led.o

obj/clock.o: src/clock.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -Iinc -c src/clock.c -o obj/clock.o

obj/timer.o: src/timer.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -Iinc -c src/timer.c -o obj/timer.o

obj/uart.o: src/uart.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -std=gnu11 -Iinc -c src/uart.c -o obj/uart.o

obj/startup.o: startup_stm32f411vetx.s 
	arm-none-eabi-gcc -mcpu=cortex-m4 -x assembler-with-cpp -c startup_stm32f411vetx.s -o obj/startup.o

bin/firmware.elf: obj/main.o obj/led.o obj/clock.o obj/timer.o obj/startup.o  
	arm-none-eabi-gcc -mcpu=cortex-m4 -T"STM32F411VETX_FLASH.ld" -Wl,-Map="map/output.map" -Wl,--gc-sections -static obj/main.o obj/led.o obj/clock.o obj/timer.o obj/uart.o obj/startup.o -o bin/firmware.elf

clean: 
	rm -f obj/*.o

flash: bin/firmware.elf 
	STM32_Programmer_CLI -c port=SWD -e 0 -d bin/firmware.elf -rst
