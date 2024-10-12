#pragma once
#ifndef __STM32F103XX_H__
#define __STM32F103XX_H__

#include <stdint.h>
#define __vo volatile
/*
 * base address of flash and ram memories
 */

#define FLASH_BASEADDR 		0x08000000U
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
	__vo uint32_t CR;	/* clock control register 			address offset: 0x00 */
	__vo uint32_t CFGR;	/* clock config register 			address offset: 0x04 */
	__vo uint32_t CIR;	/* clock interupt register			address offset: 0x08 */
	__vo uint32_t APB2RSTR;	/* APB2 peripheral reset register 		address offset: 0x0c */
	__vo uint32_t APB1RSTR;	/* APB1 peripheral reset register		address offset: 0x10 */
	__vo uint32_t AHBENR;	/* AHB peripheral clock enable register		address offset: 0x14 */
	__vo uint32_t APB2ENR;	/* APB2 peripheral clock enable register	address offset: 0x18 */
	__vo uint32_t APB1ENR;	/* APB1 peripheral clock enable register	address offset: 0x1c */
	__vo uint32_t RCC_BDCR;	/* Backup domain control register		address	offset: 0x20 */
	__vo uint32_t CSR;	/* control/status register			address offset: 0x24 */
	__vo uint32_t AHBSTR;	/* AHB peripheral clock reset register 		address offset: 0x28 */
	__vo uint32_t CFGR2;	/* clock configuration register2		address offset: 0x2c */
}RCC_RegDef_t;



/*
 * EXTI register defination structure
 */


typedef struct
{
	__vo uint32_t EXTI_IMR;
	__vo uint32_t EXTI_EMR;
	__vo uint32_t EXTI_RTSR;
	__vo uint32_t EXTI_FTSR;
	__vo uint32_t EXTI_SWIER;
	__vo uint32_t EXTI_PR; 
}EXTI_RegDef_t;


/*
 * NVIC register defination structure
 */

typedef struct
{
	__vo uint32_t ISR[2];
	uint32_t reserved0[30];
	__vo uint32_t ICER[2];
	uint32_t reserved1[34];
	__vo uint32_t ISPR[2];
	uint32_t reserved2[66];
	__vo uint32_t ICPR[2];
	uint32_t reserved3[30];
	__vo uint32_t IABR[2];
	uint32_t reserved4[62];
	__vo uint32_t IPR[20];
	
	__vo uint32_t STIR;
}NVIC_RegDef_t;

/*
 * SPI register defination structure
 */

typedef struct
{
	__vo uint32_t CR1;	/* Address offset: 0x00 */	
	__vo uint32_t CR2; 	/* Address offset: 0x04 */
	__vo uint32_t SR;  	/* Address offset: 0x08 */
	__vo uint32_t DR; 	/* Address offset: 0x0C */
	__vo uint32_t CRCPR; 	/* Address offset: 0x10 */
	__vo uint32_t RXCRCR;	/* Address offset: 0x14 */
	__vo uint32_t TXCRCR; 	/* Address offset: 0x18 */
	__vo uint32_t I2SCFRG; 	/* Address offset: 0x1C */
	__vo uint32_t I2SPR; 	/* Address offset: 0x20 */
}SPI_RegDef_t;
		


/*
 * I2C register defination structure
 */

typedef struct
{
	__vo uint32_t CR1;	/* Control register 1 | Address offset: 0x00 */
	__vo uint32_t CR2;	/* Control regsiter 2 | Adderss offset: 0x04 */
	__vo uint32_t OAR1;	/* Own address register 1 | Address offset: 0x08 */
	__vo uint32_t OAR2;	/* Own address register 2 | Address offset: 0x0c */
	__vo uint32_t DR;	/* Data register | Address offset: 0x10 */
	__vo uint32_t SR1;	/* Status register 1 | Address offset: 0x14 */
	__vo uint32_t SR2;	/* Status register 2 | Address offset: 0x18 */
	__vo uint32_t CCR;	/* Clock control register | Address offset: 0x1C */
	__vo uint32_t TRISE;	/* TRISE Register | Address offset: 0x20 */

}I2C_RegDef_t;
/*
 * Define BIT mask
 */

#define BIT0		0x0001U
#define BIT1		0x0002U
#define BIT2		0x0004U
#define BIT3		0x0008U
#define BIT4		0x0010U
#define BIT5		0x0020U
#define BIT6		0x0040U
#define BIT7		0x0080U
#define BIT8		0x0100U
#define BIT9		0x0200U
#define BIT10		0x0400U
#define BIT11		0x0800U
#define BIT12		0x1000U
#define BIT13		0x2000U
#define BIT14		0x4000U
#define BIT15		0x8000U

/*
 * peripheral defination
 */

#define GPIOA 		((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t *)GPIOG_BASEADDR)

/*
 * RCC defination
 */

#define RCC		((RCC_RegDef_t *)RCC_BASEADDR)
#define EXTI 		((EXTI_RegDef_t *)EXTI_BASEADDR)


/*
 * SPI defination
 */

#define SPI1 		((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2		((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3		((SPI_RegDef_t *)SPI3_BASEADDR)

/*
 * I2C defination
 */

#define I2C1		((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2		((I2C_RegDef_t *)I2C2_BASEADDR)


/*
 * clock enable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()		(RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()		(RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()		(RCC->APB2ENR |= (1 << 6))

/*
 * Clock disable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))
#define GPIOE_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 6))



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
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1 << 18))


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
#define USART3_PCLK_DI()        (RCC->APB1ENR &= ~(1 << 18))


#define ENABLE 			1
#define DISABLE 		0

#define SET			ENABLE
#define CLEAR			DISABLE


#include "stm32f103xx_i2c_driver.h"
#endif
