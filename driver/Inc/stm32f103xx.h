#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

#include<stdint.h>

#define __vo volatile
/*
 * base address of flash and ram memories
 */

#define FALSH_BASEADDR 		0x08000000U
#define SRAM_BASEADDR 		0x20000000U	/* 96kb */
#define ROM_BASEADDR		0x1FFFF000U 	/* system memory */

/*
 * base address of Bus domain
 */

#define AHB_BASEADDR 		0x40018000U
#define APB2_BASEADDR		0x40010000U
#define APB1_BASEADDR		0x40000000U

/*
 * base address of peripherals on APB2 Bus
 */

#define GPIOA_BASEADDR		(APB2_BASEADDR + 0x0800)
#define GPIOB_BASEADDR		(APB2_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR		(APB2_BASEADDR + 0x1000)
#define GPIOD_BASEADDR		(APB2_BASEADDR + 0x1400)
#define GPIOE_BASEADDR		(APB2_BASEADDR + 0x1800)
#define GPIOF_BASEADDR		(APB2_BASEADDR + 0x1C00)
#define GPIOG_BASEADDR		(APB2_BASEADDR + 0x2000)

#define EXTI_BASEADDR		(APB2_BASEADDR + 0x0400)

#define USART1_BASEADDR		(APB2_BASEADDR + 0x3800)
#define SPI1_BASEADDR		(APB2_BASEADDR + 0x3000)
/*
 * base address of peripherals on APB1 Bus
 */

#define TIM2_BASEADDR		APB1_BASEADDR
#define I2C1_BASEADDR		(APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR		(APB1_BASEADDR + 0x5800)
#define USART2_BASEADDR		(APB1_BASEADDR + 0x4400)
#define USART3_BASEADDR		(APB1_BASEADDR + 0x4800)
#define UART4_BASEADDR		(APB1_BASEADDR + 0x4C00)
#define UART5_BASEADDR		(APB1_BASEADDR + 0x5000)
#define SPI2_BASEADDR		(APB1_BASEADDR + 0x3800)
#define SPI3_BASEADDR		(APB1_BASEADDR + 0x3C00)

/*
 * base address of peripheral on AHB Bus
 */

#define RCC_BASEADDR		0x40021000


/*********************peripheral register defination structures********************/


/*
 * GPIO register defination structure
 */

typedef struct
{
	__vo uint32_t CRL;	/*Port configuration register low	adress offset: 0x00 */
	__vo uint32_t CRH;	/*Port configuration register high	adress offset: 0x00 */
	__vo uint32_t IDR;	/*Port input data register		adress offset: 0x00 */
	__vo uint32_t ODR;	/*Port output data register	 	adress offset: 0x00 */
	__vo uint32_t BSRR;	/*Port bit set/reset register		adress offset: 0x00 */
	__vo uint32_t BRR;	/*Port bit reset register		adress offset: 0x00 */
	__vo uint32_t LCKR;	/*Port configuration lock register	adress offset: 0x00 */

}GPIO_RegDef_t;

/*
 * RCC register defination structure
 */

typedef struct
{
	__vo uint32_t CR;	/* clock control register 		address offset: 0x00 */
	__vo uint32_t CFGR;	/* clock config register 		address offset: 0x04 */
	__vo uint32_t CIR;	/* clock interupt register		address offset: 0x08 */
	__vo uint32_t APB2RSTR;	/* APB2 peripheral reset register 	address offset: 0x0c */
	__vo uint32_t APB1RSTR;	/* APB1 peripheral reset register	address offset: 0x10 */
	__vo uint32_t AHBENR;	/* AHB peripheral clock enable register	address offset: 0x14 */
	__vo uint32_t APB2ENR;	/* APB2 peripheral clock enable register	address offset: 0x18 */
	__vo uint32_t APB1ENR;	/* APB1 peripheral clock enable register	address offset: 0x1c */
	__vo uint32_t RCC_BDCR;	/* Backup domain control register		address	offset: 0x20 */
	__vo uint32_t CSR;	/* control/status register			address offset: 0x24 */
	__vo uint32_t AHBSTR;	/* AHB peripheral clock reset register 		address offset: 0x28 */
	__vo uint32_t CFGR2	/* clock configuration register2		address offset: 0x2c */
} RCC_RegDef_t;

/*
 * peripheral defination
 */

#define GPIOA 		((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t *)GPIOG_BASEADDR)

/*
 * RCC defination
 */

#define RCC		((RCC_RegDef_t *)RCC_BASE_ADDR)

/*
 * clock enable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()		(RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()		(RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()		(RCC->APB2ENR |= (1 << 6))

/* 
 * clock enable macros for I2Cx peripherals 
 */

#define I2C1_PCLK_EN() 		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))

/*
 * clock enable macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))

/*
 * clock enable for USARTx peripherals
 */

#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1 << 17))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1 << 18))


/*
 * clock disable for GPIOx peripheral
 */

#define GPIOA_PCLK_DI()         (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI()         (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI()         (RCC->APB2ENR &= ~(1 << 4))

/*
 * clock disable for I2Cx peripheral
 */
#define I2C1_PCLK_DI()          (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()          (RCC->APB1ENR &= ~(1 << 22))


/*
 * clock disable for SPIx peripheral
 */

#define SPI1_PCLK_DI()          (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()          (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()          (RCC->APB1ENR &= ~(1 << 15))

/*
 * clock disable for USARTx peripheral
 */
#define USART1_PCLK_DI()        (RCC->APB2ENR &= ~(1 << 14))
#define USART2_PCLK_DI()        (RCC->APB1ENR &= ~(1 << 17))
#define USART2_PCLK_DI()        (RCC->APB1ENR &= ~(1 << 18))




#endif
