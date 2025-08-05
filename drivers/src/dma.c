#include <stdint.h>
#include "clock.h"
#include "dma.h"

extern char rx_buf[];
void DMA_Init()
{
	AHB1_CLK_EN(AHB1_DMA2);
	uint32_t* DMA_S2CR   = (uint32_t*) (DMA2_BASE_ADDR + 0x10 + 0x18 * 2);
	uint32_t* DMA_S2PAR  = (uint32_t*) (DMA2_BASE_ADDR + 0x18 + 0x18 * 2);
	uint32_t* DMA_S2M0AR = (uint32_t*) (DMA2_BASE_ADDR + 0x1C + 0x18 * 2);
	uint32_t* DMA_S2NDTR = (uint32_t*) (DMA2_BASE_ADDR + 0x14 + 0x18 * 2);
	/* set number of data */
	*DMA_S2NDTR = RX_BUF_SIZE;
	/* set src addr */
	*DMA_S2PAR = 0x40011000 + 0x04;
	/* set dest addr */
	*DMA_S2M0AR = (uint32_t) rx_buf;
	/* select channel 4 stream 2 */
	*DMA_S2CR |= 4 << 25;
	/* enable memory increment */
	*DMA_S2CR |= 1 << 10;
	/* enable stream */
	*DMA_S2CR |= 1 << 0;
}
