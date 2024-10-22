#include "stm32f103xx.h"

/*
 * Peripheral clock setup
 */

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
        {
                if(pUSARTx == USART1)
                {
                        USART1_PCLK_EN();
                }else if(pUSARTx == USART2)
                {
                        USART2_PCLK_EN();
                }else if(pUSARTx == USART3)
		{
			USART3_PCLK_EN();
		}
        }else
        {
                 if(pUSARTx == USART1)
                {
                        USART1_PCLK_DI();
                }else if(pUSARTx == USART2)
                {
                        USART2_PCLK_DI();
                }else if(pUSARTx == USART3)
		{
			USART3_PCLK_DI();
		}
      }
	

}

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}



void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx, usartdiv, M_part, F_part;
	uint32_t tempreg = 0;

	if(pUSARTx == USART1)
	{
		/* Uart 1 hanging on APB2 bus */
		PCLKx = RCC_GetPCLK2Value();
	}else
	{

		PCLKx = RCC_GetPCLK1Value();
	}
	if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		/* over sampling by 8 */
		usartdiv = ((25 * PCLKx) / (2 * BaudRate));
	}else
	{
		/* over sampling by 16 */
		usartdiv = ((25 * PCLKx) / (4 * BaudRate));
	}

	/* Calculate the Mantissa part */
	M_part = usartdiv/100;

	tempreg |= M_part << 4;
	
	/* Calculate final fractional */
	if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		/* over sampling by 8 */
		F_part = ((( F_part * 8) + 50 / 100) & ((uint8_t)0x07));
	}else
	{
		/* over sampling by 16 */
		F_part = ((( F_part * 16) + 50 / 100) & ((uint8_t)0x0F));
	}
	tempreg |= F_part;

	pUSARTx->BRR = tempreg;

}
/*
 * Init and Deinit
 */

void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;

	/* Enable clock for USART peripheral */
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	/********************* Configuration of CR1 *****************************/

	/* Configure USART mode */
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		/* Mode TX */
		tempreg |= (1 << USART_CR1_TE);

	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{	
		/* Mode RX */
		tempreg |= (1 << USART_CR1_RE);
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		/* Mode TXRX */
		tempreg |= (1 << USART_CR1_TE) | (1 << USART_CR1_RE);
	}

	/* Configure the Word length */
	tempreg |= (pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M);

	/* Configure parity control bit fields */
	tempreg |= (pUSARTHandle->USART_Config.USART_ParityControl << USART_CR1_PS);

	pUSARTHandle->pUSARTx->CR1 = tempreg;

	/********************* Configuration of CR2 *****************************/
	tempreg = 0;

	/* Configure number of stop bits */
	tempreg |= (pUSARTHandle->USART_Config.USART_StopBits << USART_CR2_STOP);

	pUSARTHandle->pUSARTx->CR2 = tempreg;

	
	/********************* Configuration of CR3 *****************************/
	
	tempreg = 0;
	/* Configure USART Hardware flow control */

	if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		/* Mode TX */
		tempreg |= (1 << USART_CR3_CTSE);

	}else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{	
		/* Mode RX */
		tempreg |= (1 << USART_CR3_RTSE);
	}else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		
		tempreg |= (1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE);
	}else
	{
	
		tempreg &= ~(1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE);
	}
	pUSARTHandle->pUSARTx->CR3 = tempreg;
	/***************Configuration of Baudrate register ***********************/
	
	USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);

}

/*
 * Data send and Receive
 */

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
	for(uint32_t i = 0; i < Len; i++)
	{
		/* wait until TX register is set */
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE)));
		
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			pdata = (uint16_t*)pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);
			
			/* Check for USART parity control */

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				/* No parity is used in this transfer, so 9bits of user data will be sent */
				pTxBuffer++;
				pTxBuffer++;
			}else
			{
				pTxBuffer++;
			}
		}else
		{
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}
	
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC)));

}
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	for(uint32_t i = 0; i < Len; i++)
	{
		/* wait until RX register is set */
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_RXNE)));
		
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			/* Check for USART parity control */

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{

				*(uint16_t *)pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);
				/* No parity is used */
				pRxBuffer++;
				pRxBuffer++;
			}else
			{
				pRxBuffer = pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF;
				pRxBuffer++;
			}
		}else
		{
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				/* Read 8 bit from DR */
				*(uint8_t *)pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint16_t)0xFF);
				/* No parity is used */
				pRxBuffer++;
			}else
			{
				/* Read 7 bit form DR*/
				pRxBuffer = pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F;
				pRxBuffer++;
			}

		}
	}

}

/*
 * Other API
 */

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
	if(pUSARTx->SR & StatusFlagName)
	{
		return SET;
	}else
	{
		return CLEAR;
	}
}



