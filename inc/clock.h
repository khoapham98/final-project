#define RCC_BASE_ADDR 0x40023800
#define uint32_t unsigned int
#define uint16_t unsigned short
#define uint8_t  unsigned char
typedef enum
{
    AHB1_GPIOA, AHB1_GPIOB, AHB1_GPIOC, AHB1_GPIOD, AHB1_GPIOE,
    AHB1_GPIOH = 7,
    AHB1_CRC   = 12,
    AHB1_DMA1  = 21,
    AHB1_DMA2  = 22
} AHB1_periph_t;

typedef enum
{
    AHB2_OTGFS = 7
} AHB2_periph_t;

typedef enum
{
    APB1_TIM2, APB1_TIM3, APB1_TIM4, APB1_TIM5,
    APB1_WWDG   = 11,
    APB1_SPI2   = 14, APB1_SPI3,
    APB1_USART2 = 17,
    APB1_I2C1   = 21, APB1_I2C2, APB1_I2C3,
    APB1_PWR    = 28
} APB1_periph_t;

typedef enum
{
    APB2_TIM1,
    APB2_USART1 = 4, APB2_USART6,
    APB2_ADC1   = 8,
    APB2_SDIO   = 11,
    APB2_SPI1   = 12, APB2_SPI4, APB2_SYSCFG,
    APB2_TIM9   = 16, APB2_TIM10, APB2_TIM11,
    APB2_SPI5   = 20
} APB2_periph_t;

void AHB1_CLK_EN(AHB1_periph_t periph);
void AHB2_CLK_EN(AHB2_periph_t periph);
void APB1_CLK_EN(APB1_periph_t periph);
void APB2_CLK_EN(APB2_periph_t periph);
