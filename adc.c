#include <math.h>
#include "adc.h"

/*
 * This program is an example of communicating with an ADC chip using I2C.
 *
 * It was tested on an STM32 Nucleo F446RE board.
 */
int main(void)
{
    /* Enable GPIOA */
    RCC_AHB1ENR |= (0x01 << 0x00);
    /* Alternate function (AF) mode for PA9 and PA10 */
    GPIOA_MODER |= (0x02 << 0x12) | (0x02 << 0x14);
    /* AF7 (USART TX and RX) for PA9 and PA10 */
    GPIOA_AFRH  |= (0x07 << 0x04) | (0x07 << 0x08); 

    /* Configure PA5 and PA6 for debugging output */
    GPIOA_MODER |= (0x01 << 0x0A) | (0x01 << 0x0C);

    /* Enable GPIOB */
    RCC_AHB1ENR |= (0x01 << 0x01);
    /* Alternate function (AF) mode for PB8 and PB9 */
    GPIOB_MODER |= (0x02 << 0x10) | (0x02 << 0x12);
    /* AF4 (I2C SCL and SDA) for PB8 and PB9 */
    GPIOB_AFRH  |= (0x04 << 0x00) | (0x04 << 0x04);
    GPIOB_OTYPER|= (0x01 << 0x08) | (0x01 << 0x09);
    GPIOB_PUPDR |= (0x01 << 0x10) | (0x01 << 0x12);

    /* Enable USART1 */
    RCC_APB2ENR |= (0x01 << 0x04);
    /* Configure baud rate based on APB2 clock (equals to HSI 16MHz by default) */
    USART1_BRR   = 0x683;
    /* Enable TX and RX, and USART overall */
    USART1_CR1  |= (0x01 << 0x03) | (0x01 << 0x02) | (0x01 << 0x0D);

    /* Enable I2C1 */
    RCC_APB1ENR |= (0x01 << 0x15);
    /* Set input clock (APB1, HSI 16MHz by default) */
    I2C1_CR2    |= (0x10 << 0x00);
    /* Set CCR */
    I2C1_CCR    |= (0x50 << 0x00);
    /* Set time rise */
    I2C1_TRISE  |= (0x11 << 0x00);
    /* Enable I2C1 */
    I2C1_CR1    |= (0x01 << 0x00);

    while (1)
    {
        /* Wait for an input from USART before reading */
        /* starting I2C and ADC reading */
        if (USART1_SR & (0x01 << 0x05))
        {
            char unused = USART1_DR;

            /* Toggle PA6 when we received a character from USART */
            GPIOA_ODR ^= (0x01 << 0x06);

            USART1_DR = '\t';
            while (!(USART1_SR & (0x01 << 0x06)))
                ;

            /* I2C: set the start condition, entering MASTER mode */
            I2C1_CR1    |= (0x01 << 0x08);

            /* ... and for start bit */
            while (!(I2C1_SR1 & (0x01 << 0x00)))
                ;
            /* ... and for MSL */
            while (!(I2C1_SR2 & (0x01 << 0x00)))
                ;

            /* Send the address */
            I2C1_DR     |= (0x28 << 0x01) | (0x01 << 0x00);

            /* Send a NACK here because we expect only one byte */
            I2C1_CR1 &= ~(0x01 << 0x0A);

            /* Wait for ADDR */
            while (!(I2C1_SR1 & (0x01 << 0x01)))
                ;
            /* ... and TRA bits */
            while (I2C1_SR2 & (0x01 << 0x02))
                ;

            /* Wait for RxNE to be set */
            while (!(I2C1_SR1 & (0x01 << 0x06)))
                ;

            char data = I2C1_DR;

            /* Clear the DR bits so that on next start */
            /* its value is not used as the address. */
            I2C1_DR = 0;

            /* Stop. This is optional if we want to use */
            /* repeated start. */
            I2C1_CR1     |= (0x01 << 0x09);

            /* Convert data */
            float val = data * (ADC_VDD / (float) ADC_RESOLUTION);

            int whole = (int)val;
            int decimal = (int)trunc((val - whole)*10000);

            char output[OUTPUT_LENGTH];
            for (int i = 0; i<OUTPUT_LENGTH; i++)
                output[i] = '0';

            unsigned char x = 0;
            while (decimal > 0 && ++x < OUTPUT_LENGTH)
            {
                char digit = decimal % 10;
                decimal = (int) trunc(decimal / 10);
                output[OUTPUT_LENGTH - x] = '0' + (char)digit;
            }
            output[OUTPUT_LENGTH - ++x] = '.';
            while (whole > 0 && ++x < OUTPUT_LENGTH)
            {
                char digit = whole % 10;
                whole = (int)trunc(whole / 10);
                output[OUTPUT_LENGTH - x] = '0' + (char)digit;
            }

            for (unsigned char i = 0; i<OUTPUT_LENGTH; i++)
            {
                USART1_DR = output[i];
                while (!(USART1_SR & (0x01 << 0x06)))
                    ;
            }
        }
    }

    return 0;
}
