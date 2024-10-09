#include "stm32f103xx_spi_driver.h"


void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if(pSPix == SPI2)
		{
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if(pSPix == SPI2)
		{
			SPI2_PCLK_DI();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	
	}
}

/*
 * SPI Init 
 */



void SPI_Init(SPI_Regdef_t *pSPIx, SPI_Congfig_t *SPI_Config)
{
	uint32_t tempreg = 0;
	
	// select mode
	tempreg |= (SPI_Config->SPI_DeviceMode << SPI_CR1_MSTR);
	
	// configure Clock speed
	tempreg |= (SPI_Config->SPI_SclkSpeed << SPI_CR1_BR);
	
	// setting CPOL and CPHA 

	tempreg |= SPI_Config->SPI_CPHA << SPI_CR1_CPHA;
	tempreg |= SPI_Config->SPI_CPOL << SPI_CR1_CPOL;	

	// setting data frame format 

	tempreg |= (SPI_Config->SPI_DFF << SPI_CR1_DFF);

	/* configure Bus */
	if(SPI_Config->SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(SPI_Config->SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tempreg |= (1 << SPI_CR1_BIDIMODE);

	}else if(SPI_Config->SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		tempreg &= ~(1 << SPI_CR1_RXONLY);
	}	

	/* configure LSBfirst */
	tempreg |= (SPI_FF << SPI_CR1_LSB)
		
	pSPIx->CR1 = tempreg;
}
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	SPI_PeripheralControl(pSPIx, ENABLE);
	while(len > 0)
	{
		while(!(GetFlagStatus(pSPIx, SPI_TXE_FLAG)));
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			pSPIx->DR = *((uint16_t *) pTxBuffer);
			len -= 2;
			(uint16_t *)pTxBuffer++;
		}else
		{
			pSPIx->DR = *pTxBuffer;
			--len;
			pTxBuffer++;
		}

	}
	while(!(GetFlagStatus(pSPIx, SPI_BSY_FLAG));
	SPI_PeripheralControl(pSPIx, DISABLE);

}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	SPI_PeripheralControl(pSPIx, ENABLE);
	while(len > 0)
	{
		while(!(GetFlagStatus(pSPIx, SPI_RXNE_FLAG)));
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			pRXBuffer = *((uint16_t *)pSPIx->DR);
			len-=2;
			(uint16_t *)pRXBuffer++;
		}else
		{
			pRxBuffer = pRxBuffer;
			--len;
			pRxBuffer++;
		}
	}

	while(!(GetFlagStatus(pSPIx, SPI_BSY_FLAG));
	SPI_PeripheralControl(pSPIx, DISABLE);
}
		

				




void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t Flag)
{
	if(pSPIx->SR & Flag)
	{
		return SET;
	}
	else
	{
		return CLEAR;
	}
}


