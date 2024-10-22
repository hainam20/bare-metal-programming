#include "stm32f103xx.h"


uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};
uint16_t APB2_PreScaler[4] = {2,4,8,16};


/* Get value from ABPB1 bus */
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1 = 0, SystemClk = 0;
	uint8_t clksrc = 0, temp = 0, ahbp = 0, apb1 = 0;
	clksrc = (RCC->CFGR >> 2) & 0x03;
	if(clksrc == 0)
	{
		SystemClk = 16000000;
	}else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}else if(clksrc == 2)
	{
		//SystemClk = RCC_GetOutputCLK();
	}

	// Get value of AHB
	temp = (RCC->CFGR >> 4) & 0x0F;
	if(temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}
	// Get value of APB1
	temp = (RCC->CFGR >> 8) & 0x07;
        if(temp < 4)
        {
                apb1 = 1;
        }else
        {
                apb1 = APB1_PreScaler[temp - 4];
        }
	pclk1 = (SystemClk / ahbp) / apb1;

	return pclk1;
		
}

/* Get value from ABPB2 bus */
uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2 = 0, SystemClk = 0;
	uint8_t clksrc = 0, temp = 0, ahbp = 0, apb2 = 0;
	clksrc = (RCC->CFGR >> 2) & 0x03;
	if(clksrc == 0)
	{
		SystemClk = 16000000;
	}else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}else if(clksrc == 2)
	{
		//SystemClk = RCC_GetOutputCLK();
	}

	/* Get value of AHB */
	temp = (RCC->CFGR >> 4) & 0x0F;
	if(temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}
	temp = (RCC->CFGR >> 11) & 0x07;
	if(temp < 4)
	{
		apb2 = 1;
	}else
	{
		apb2 = APB2_PreScaler[temp - 4];
	}
	pclk2 = (SystemClk / ahbp) / apb2;

	return pclk2;
}


