#define GPIOD_BASE_ADDR 0x40020C00
typedef enum
{
    GREEN_LED, ORANGE_LED, RED_LED, BLUE_LED
} LED_color_t; 

typedef enum
{
    LED_OFF, LED_ON
} LED_state_t; 
void LED_toggle(LED_color_t color);
void LED_Ctrl(LED_color_t color, LED_state_t state); 
void LED_Init();
