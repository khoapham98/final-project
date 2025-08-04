#include <stdint.h>
#include "adc.h"

float get_mcu_temp()
{
	uint16_t tmp = ADC_read();
	float Vin = (tmp * 3.0) / 4095; 
	float temp = ((Vin - 0.76) / 2.5e-3) + 25; 
	return temp;
}
