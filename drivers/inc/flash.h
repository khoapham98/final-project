#pragma once
#include <stdint.h>
#define FLASH_INTF_BASE_ADDR 0x40023C00
#define FLASH_BASE_ADDR 	 0x08000000

void FLASH_program(uint8_t* fw, uint32_t fw_len);
void FLASH_mass_erase();
