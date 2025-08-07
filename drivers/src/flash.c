#include <stdint.h>
#include <string.h>
#include "flash.h"
RAM_FUNC static void FLASH_lock();
RAM_FUNC static void FLASH_unlock();
RAM_FUNC static void FLASH_program(uint8_t* fw, uint32_t fw_len);
RAM_FUNC static void FLASH_mass_erase();

RAM_FUNC static void software_reset()
{
	uint32_t* AIRCR = (uint32_t*) (0xE000ED0C);
	/* write to VECTKEY ortherwise the write is ignored */ 
	*AIRCR |= 0x5FA << 16; 
	/* force software reset */ 
	*AIRCR |= 1 << 2; 
}

RAM_FUNC void FLASH_update_fw(uint8_t* fw, uint32_t fw_len)
{
	__asm("CPSID i");
	/* FLASH_unlock(); */
	FLASH_mass_erase();
	FLASH_program(fw, fw_len);
	/* FLASH_lock(); */
	software_reset();
}

RAM_FUNC static void FLASH_program(uint8_t* fw, uint32_t fw_len)
{
	FLASH_unlock();
	uint32_t* FLASH_SR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x0C);
	uint32_t* FLASH_CR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x10);
	uint8_t* flash = (uint8_t*) (FLASH_BASE_ADDR);
	/* wait until flash is free */ 
	while (((*FLASH_SR >> 16) & 1) == 1);
	/* set program size 1 byte */ 
	*FLASH_CR &= ~(0b11 << 8);
	/* active flash programming */
	*FLASH_CR |= 1 << 0; 
	/* write new firmware to flash */ 
	for (int i = 0; i < fw_len; i++)
	{
		flash[i] = fw[i];
		while (((*FLASH_SR >> 16) & 1) == 1);
	}
	/* unactive flash programming */
	*FLASH_CR &= ~(1 << 0);
	FLASH_lock();
}

RAM_FUNC static void FLASH_mass_erase()
{
	FLASH_unlock();
	uint32_t* FLASH_SR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x0C);
	uint32_t* FLASH_CR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x10);
	/* wait until flash is free */ 
	while (((*FLASH_SR >> 16) & 1) == 1);
	/* activate mass erase */ 
	*FLASH_CR |= 1 << 2; 
	/* start erase operation */ 
	*FLASH_CR |= 1 << 16; 
	/* wait until flash is free */ 
	while (((*FLASH_SR >> 16) & 1) == 1);
	/* unactive mass erase */
	*FLASH_CR &= ~(1 << 2);
	FLASH_lock();
}

RAM_FUNC static void FLASH_lock()
{
	uint32_t* FLASH_CR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x10);
	*FLASH_CR |= 1 << 31; 
}

RAM_FUNC static void FLASH_unlock()
{
	uint32_t* FLASH_KEYR = (uint32_t*) (FLASH_INTF_BASE_ADDR + 0x04);
	*FLASH_KEYR = 0x45670123;
	*FLASH_KEYR = 0xCDEF89AB;
}
