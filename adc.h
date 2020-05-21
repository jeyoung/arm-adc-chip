#define RCC             0x40023800
#define RCC_AHB1ENR     (*((volatile unsigned long *)((RCC) + 0x30)))
#define RCC_APB1ENR     (*((volatile unsigned long *)((RCC) + 0x40)))
#define RCC_APB2ENR     (*((volatile unsigned long *)((RCC) + 0x44)))

#define GPIOA           0x40020000
#define GPIOA_MODER     (*((volatile unsigned long *)((GPIOA) + 0x00)))
#define GPIOA_OTYPER    (*((volatile unsigned long *)((GPIOA) + 0x04)))
#define GPIOA_OSPEEDER  (*((volatile unsigned long *)((GPIOA) + 0x08)))
#define GPIOA_ODR       (*((volatile unsigned long *)((GPIOA) + 0x14)))
#define GPIOA_AFRH      (*((volatile unsigned long *)((GPIOA) + 0x24)))

#define GPIOB           0x40020400
#define GPIOB_MODER     (*((volatile unsigned long *)((GPIOB) + 0x00)))
#define GPIOB_OTYPER    (*((volatile unsigned long *)((GPIOB) + 0x04)))
#define GPIOB_OSPEEDER  (*((volatile unsigned long *)((GPIOB) + 0x08)))
#define GPIOB_PUPDR     (*((volatile unsigned long *)((GPIOB) + 0x0C)))
#define GPIOB_ODR       (*((volatile unsigned long *)((GPIOB) + 0x14)))
#define GPIOB_AFRH      (*((volatile unsigned long *)((GPIOB) + 0x24)))

#define USART1          0x40011000
#define USART1_SR       (*((volatile unsigned long *)((USART1) + 0x00)))
#define USART1_DR       (*((volatile unsigned long *)((USART1) + 0x04)))
#define USART1_BRR      (*((volatile unsigned long *)((USART1) + 0x08)))
#define USART1_CR1      (*((volatile unsigned long *)((USART1) + 0x0C)))
#define USART1_CR2      (*((volatile unsigned long *)((USART1) + 0x10)))
#define USART1_CR3      (*((volatile unsigned long *)((USART1) + 0x14)))

#define I2C1            0x40005400
#define I2C1_CR1        (*((volatile unsigned long *)((I2C1) + 0x00)))
#define I2C1_CR2        (*((volatile unsigned long *)((I2C1) + 0x04)))
#define I2C1_DR         (*((volatile unsigned long *)((I2C1) + 0x10)))
#define I2C1_SR1        (*((volatile unsigned long *)((I2C1) + 0x14)))
#define I2C1_SR2        (*((volatile unsigned long *)((I2C1) + 0x18)))
#define I2C1_CCR        (*((volatile unsigned long *)((I2C1) + 0x1C)))
#define I2C1_TRISE      (*((volatile unsigned long *)((I2C1) + 0x20)))

#define ADC_VDD         2.85
#define ADC_RESOLUTION  256

#define OUTPUT_LENGTH   15

int main(void);
