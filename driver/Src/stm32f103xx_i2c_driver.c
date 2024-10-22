#include "stm32f103xx.h"


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFLag(I2C_RegDef_t *pI2Cx);



void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}
	}else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();
		}
	}
}

void I2C_PerepheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}
}


void I2C_Init(I2C_RegDef_t *pI2Cx, I2C_Config_t *I2CConfig)
{
	uint32_t tempreg = 0;

	/* Configure ACK Control bit */

	tempreg |= (I2CConfig->I2C_ACKControl << I2C_CR1_ACK);
	pI2Cx->CR1 = tempreg;
	
	/* Configure the FREQ field of CR2 */
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000U;
	pI2Cx->CR2 = tempreg & 0x3F;

	/* Configure the device own address */
	tempreg = 0;
	tempreg |= I2CConfig->I2C_DeviceAddress < 1;
	tempreg |= (1 << 14);
	pI2Cx->OAR1 = tempreg;
	
	/* CCR calculations */

	uint16_t ccr_value = 0;
	tempreg = 0;
	if(I2CConfig->I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		/* Mode is standard mode */
		ccr_value = (RCC_GetPCLK1Value() / (2 * I2CConfig->I2C_SCLSpeed));
		tempreg |= ccr_value & 0xFFF;
		
	}else
	{
		/* Mode is fast mode */
		tempreg |= (1 << 15);
		tempreg |= (I2CConfig->I2C_FMDutyCycle << 14);
	       if(I2CConfig->I2C_FMDutyCycle == I2C_FM_DUTY_2)
	       {
		      
		ccr_value = (RCC_GetPCLK1Value() / (3 * I2CConfig->I2C_SCLSpeed));

	       }else if(I2CConfig->I2C_FMDutyCycle == I2C_FM_DUTY_16_9)
	       {

		ccr_value = (RCC_GetPCLK1Value() / (25 * I2CConfig->I2C_SCLSpeed));
	       }	       
		tempreg |= ccr_value & 0xFFF;
	}
	pI2Cx->CCR = tempreg;
	

}
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint8_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return SET;
	}
	return CLEAR;
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~1;
	pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFLag(I2C_RegDef_t *pI2Cx)
{
	uint32_t dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

void I2C_ManageAck(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}else
	{
		pI2Cx->CR1 &= (1 << I2C_CR1_ACK);
	}
}

void I2C_MasterSendData(I2C_RegDef_t *pI2Cx,uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
	/* Generate start condition */
	I2C_GenerateStartCondition(pI2Cx);

	/* Confirm that start generation is completed by checking the SB flag in SR1 */
	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_SB)));
	
	/* Send the address of the slave with r/w bit (total 8 bits) */
	I2C_ExecuteAddressPhase(pI2Cx, SlaveAddr);

	/*Confirm that address phase is completed by checking the ADDR flag in SR1*/
	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_ADDR)));
	
	I2C_ClearADDRFLag(pI2Cx);

	while(Len > 0)
	{
		while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE)));
		pI2Cx->DR = *(pTxBuffer);
		pTxBuffer++;
		Len--;
	}
	
       	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE)));
       	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_BTF)));

	/* Generate Stop Condition */

	I2C_GenerateStopCondition(pI2Cx);


}	
void I2C_MasterReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, I2C_Config_t *I2CConfig)
{
	 /* Generate Start condition */
  	I2C_GenerateStartCondition(pI2Cx);

	/* Confirm that start generation is completed by checking the SB flag in SR1 */
	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_SB)));

	/* Send the address of the slave with r/w bit (total 8 bits) */
	I2C_ExecuteAddressPhase(pI2Cx, SlaveAddr);

	/*Confirm that address phase is completed by checking the ADDR flag in SR1*/
	while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_ADDR)));
	

	if(Len == 1)
	{
		/* Disable ACK */
		I2C_ManageAck(pI2Cx, I2C_ACK_DISABLE);
	
		/*Clear the ADDR flag */
		I2C_ClearADDRFLag(pI2Cx);

		while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_RXNE)));
	
		/* Generate Stop Condition */
		I2C_GenerateStopCondition(pI2Cx);


		/* Read data into buffer */

		*pRxBuffer = pI2Cx->DR;


	}

	if(Len > 1)
	{
		/* Clear addr flag */
		I2C_ClearADDRFLag(pI2Cx);

		/* Read data */
		for(uint32_t i = Len; i > 0; i--)
		{
			/* Wait until RXNE become 1 */
			while(!(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_RXNE)));
			
			if(i == 2)
			{
				/* Disable ACK */
                		I2C_ManageAck(pI2Cx, I2C_ACK_DISABLE);

                		/* Generate Stop Condition */
                		I2C_GenerateStopCondition(pI2Cx);


			}
			/* Read data into buffer */
			*pRxBuffer = pI2Cx->DR;
			pRxBuffer++;



		}
		
	}
	/* Enable  ACK */
	if(I2CConfig->I2C_ACKControl == I2C_ACK_ENABLE)
	{

        	I2C_ManageAck(pI2Cx, I2C_ACK_ENABLE);
	}

}


void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx, uint8_t data)
{
	pI2Cx->DR = data;
}

uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2Cx)
{
	return (uint8_t)pI2Cx->DR;
}

