#pragma once
#ifndef __STM32F103XX_GPIO_DRIVER_H__
#define __STM32F103XX_GPIO_DRIVER_H__

#include"stm32f103xx.h"
/*
 * GPIO pin numbers
 */

#define GPIO_PIN_NO_0 		BIT0
#define GPIO_PIN_NO_1 		BIT1
#define GPIO_PIN_NO_2 		BIT2
#define GPIO_PIN_NO_3 		BIT3
#define GPIO_PIN_NO_4 		BIT4
#define GPIO_PIN_NO_5 		BIT5
#define GPIO_PIN_NO_6 		BIT6
#define GPIO_PIN_NO_7 		BIT7
#define GPIO_PIN_NO_8 		BIT8
#define GPIO_PIN_NO_9 		BIT9
#define GPIO_PIN_NO_10 		BIT10
#define GPIO_PIN_NO_11		BIT11
#define GPIO_PIN_NO_12		BIT12
#define GPIO_PIN_NO_13		BIT13
#define GPIO_PIN_NO_14		BIT14
#define GPIO_PIN_NO_15		BIT15


/*
 * GPIO pin mode
 */

typedef enum{
	GPIO_OUT_PP		= 0x01,	
	GPIO_OUT_OP		= 0x05,
	GPIO_OUT_AF_PP		= 0x09,
	GPIO_OUT_AF_OP		= 0x0D,
	GPIO_IN_AN		= 0x00,
	GPIO_IN_FLOATING	= 0x04,
	GPIO_IN_PD		= 0x08,
	GPIO_IN_PU		= 0x0C, 	/* 1100 */
	GPIO_IT_RFT		= 0x0E,
	GPIO_IT_FFT		= 0x0F,
}GPIOMode_t;

typedef enum{
	GPIO_Speed_10MHz	= 1,
	GPIO_Speed_2MHz,
	GPIO_Speed_50Mhz
}GPIOSpeed_t;


typedef struct
{
	uint16_t GPIO_PinNumber;
	GPIOMode_t GPIO_PinMode;
	GPIOSpeed_t GPIO_PinSpeed;
	
}GPIO_PinConfig_t;

/*
 * Init and DeInit
 */

void GPIO_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConfig_t *GPIOConfig);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Peripheral Clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Data read and write
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *GPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *GPIOx, uint16_t value);
uint8_t GPIO_ReadFromOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber);
uint16_t GPIO_ReadFromOutputPort(GPIO_RegDef_t *GPIOx);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber);

/*
 * IRQ Configuration and IRQ Handling
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif
