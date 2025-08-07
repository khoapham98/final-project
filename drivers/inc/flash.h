#pragma once
#include <stdint.h>
#define FLASH_INTF_BASE_ADDR 0x40023C00
#define FLASH_BASE_ADDR 	 0x08000000
#define RAM_FUNC			 __attribute__((section(".RamFunc")))
RAM_FUNC void FLASH_update_fw(uint8_t* fw, uint32_t fw_len);
