
#include"stm32f103xx_gpio_driver.h"
#include"stm32f103xx.h"


/*
 * Init and Deinit
 */

void GPIO_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConfig_t *GPIOConfig)
{
    uint32_t temp = GPIOConfig->GPIO_PinMode;
 
    if (GPIOConfig->GPIO_PinMode & 0x03)
    {
        temp |= GPIOConfig->GPIO_PinSpeed;
    }
    /*------------ GPIO CRL configuration------*/
    if ((GPIOConfig->GPIO_PinNumber & 0x00FF) != 0x00)
    {
        for (int pinnum = 0; pinnum < 8; pinnum++)
        {
            if (GPIOConfig->GPIO_PinNumber & (1 << pinnum))
            {
                //temp = temp << (pinnum * 2);
		GPIOx->CRL &= ~((0x0F) << (pinnum * 4));
            
	    /* ----- Config Pull-up / Pull-down mode ------*/

            	if (GPIOConfig->GPIO_PinMode == GPIO_IN_PD)
            	{
                	GPIOx->ODR = (1 << pinnum);
            	}
            	else if (GPIOConfig->GPIO_PinMode == GPIO_IN_PU)
            	{
			temp |= (1 << 3);
                	GPIOx->ODR = (1 << pinnum);
            	}
	   
		GPIOx->CRL |= (temp << (pinnum * 4 ));
	    }

        }
	
    }

    /*--------------- GPIO CRH Configuration ----------------*/
    if ((GPIOConfig->GPIO_PinNumber & 0xFF00) != 0x00)
    {
        for (int pinnum = 8; pinnum < 16; pinnum++)
        {
            if (GPIOConfig->GPIO_PinNumber & (1 << pinnum))
            {
                GPIOx->CRH &= ~((0x0F) << ((pinnum - 8) * 4));
            
           	 if (GPIOConfig->GPIO_PinMode == GPIO_IN_PD)
            	{
                	GPIOx->ODR = (1 << (pinnum - 8));
            	}
           	 else if (GPIOConfig->GPIO_PinMode == GPIO_IN_PU)
            	{
			temp |= (1 << 3);
                	GPIOx->ODR = (1 << (pinnum - 8));
           	 }
       	   
		GPIOx->CRH |= (temp << ((pinnum - 8) * 4));
	    }

	}

    }

    /* ------------ GPIO IT CONFIG --------------*/

   /* if(GPIOConfig->GPIO_PinMode == GPIO_IT_RFT)
    {	
	
	    EXTI->EXTI_EMR &= ~(1 << GPIOConfig->GPIO_PinNumber);
	    EXTI->EXTI_EMR |= (1 << GPIOConfig->GPIO_PinNumber);

	    EXTI->EXTI_RTSR &= ~(1 << GPIOConfig->GPIO_PinNumber);
	    EXTI->EXTI_RTSR |= (1 << GPIOConfig->GPIO_PinNumber);


    }else if(GPIOConfig->GPIO_PinMode == GPIO_IT_FFT)
    {
	    EXTI->EXTI_EMR &= ~(1 << GPIOConfig->GPIO_PinNumber);
	    EXTI->EXTI_EMR |= (1 << GPIOConfig->GPIO_PinNumber);

	    EXTI->EXTI_FTSR &= ~(1 << GPIOConfig->GPIO_PinNumber);
	    EXTI->EXTI_FTSR |= (1 << GPIOConfig->GPIO_PinNumber);
    }
	*/

}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_PCLK_DI();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_PCLK_DI();
	}else if(pGPIOx == GPIOC)
	{	
		GPIOC_PCLK_DI();
	}
}


/*
 * Peripheral Clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
	}
	else if(EnorDi == DISABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
	}
	
}

/*
 * Data read and write
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((GPIOx->IDR >> PinNumber) & 0x01);
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *GPIOx)
{
	uint16_t value;
	value = (uint16_t) GPIOx->IDR;
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber, uint8_t value)
{
	uint8_t temp;
	temp = value << PinNumber;
	GPIOx->ODR = temp;
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *GPIOx, uint16_t value)
{
	GPIOx->ODR = value;
}
uint8_t GPIO_ReadFromOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber);
uint16_t GPIO_ReadFromOutputPort(GPIO_RegDef_t *GPIOx);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (uint32_t) PinNumber;
}

/*
 * IRQ Configuration and IRQ Handling
 */

//void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
//void GPIO_IRQHandling(uint16_t PinNumber);


