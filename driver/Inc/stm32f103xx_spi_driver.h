#ifndef __STM32F103XX_SPI_DRIVER_H__
#define __STM32F103XX_SPI_DRIVER_H__

#include "stm32f103xx.h"

/* ------------------ Define macro for SPI ---------------*/


typedef enum
{
	SPI_SSM_SW = 0,  	/* Software slave slect management */
	SPI_SSM_HW,		/* Hardware slave slect management */
}SPI_SSM_t;

typedef enum
{
	SPI_BUS_CONFIG_FD = 0,		/* SPI Bus Full-duplex */
	SPI_BUS_CONFIG_HD,		/* SPI BUs Half-duplex */
	SPI_BUS_CONFIG_SIMPLEX_RXONLY,
}SPI_BusConfig_t;

typedef enum
{
	SPI_DFF_8BIT = 0,		/* Data frame format 8 bit */
	SPI_DFF_16BIT,			/* Data frame format 16 bit */
}SPI_DFF_t;

typedef enum
{
	SPI_MODE_SLAVE = 0, 
	SPI_MODE_MASTER,	
}SPI_DeviceMode_t;

typedef enum
{
	SPI_SCLK_SPEED_DIV2 = 0,
	SPI_SCLK_SPEED_DIV4,
	SPI_SCLK_SPEED_DIV8,
	SPI_SCLK_SPEED_DIV16,
	SPI_SCLK_SPEED_DIV32,
	SPI_SCLK_SPEED_DIV64,
	SPI_SCLK_SPEED_DIV128,
	SPI_SCLK_SPEED_DIV256,
}SPI_SclkSpeed_t;

typedef enum
{
	SPI_CPOL_LOW = 0,
	SPI_CPOL_HIGH,
}SPI_CPOL_t;

typedef enum
{
	SPI_CPHA_LOW = 0,
	SPI_SPHA_HIGH,
}SPI_CPHA_t;

typedef enum
{
	SPI_MSB_FIRST = 0,
	SPI_LSB_FIRST,
}SPI_FrameFormat_t;



/*
 * Configuration structure for SPIx Peripheral
 */

typedef struct
{
	SPI_DeviceMode_t SPI_DeviceMode;
	SPI_BusConfig_t SPI_BusConfig;
	SPI_SclkSpeed_t SPI_SclkSpeed;
	SPI_DFF_t SPI_DFF;
	SPI_CPOL_t SPI_CPOL;
	SPI_CPHA_t SPI_CPHA;
	SPI_SSM_t SPI_SSM;
	SPI_FrameFormat_t SPI_FF;
}SPI_Config_t;


/*
 * Define marcro for SPI CR1 Register
 */

#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR		3
#define SPI_CR1_SPE		6
#define SPI_CR1_LSB		7
#define SPI_CR1_SSI		8
#define SPI_CR1_SSM		9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

/*
 * Define marcro for SPI CR2 Register
 */

#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_RXEIE		7


/*
 * Define marcro for SPI SR Flag
 */

#define SPI_RXNE_FLAG		BIT0		/* Receive buffer flag */
#define SPI_TXE_FLAG		BIT1		/* Transmit buffer flag */
#define SPI_CHSIDE_FLAG		BIT2		/* Channel side */
#define SPI_UDR_FLAG		BIT3		/* Underun flag */
#define SPI_CRCERR_FLAG		BIT4		/* CRC ERROR flag */
#define SPI_MODEF_FLAG		BIT5		/* Mode fault flag */
#define SPI_OVR_FLAG		BIT6		/* Overun flag */
#define SPI_BSY_FLAG		BIT7		/* Busy flag */




/* 
 * SPI Init and DeInit
 */

void SPI_Init(SPI_RegDef_t *pSPIx, SPI_Config_t *SPI_Config);

void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * SPI Clock Setup
 */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t Flag);
/*
 * SPI Send and Receive data
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


void SPI_SendDataIT(SPI_RegDef_t *pSPIx,SPI_Config_t *pSPIConfig, uint8_t *pTxBuffer, uint32_t Len);

void SPI_ReceiveDataIT(SPI_RegDef_t *pSPIx,SPI_Config_t *pSPIConfig,  uint8_t *pRxBuffer, uint32_t Len);







#endif  /* __STM32F103XX_SPI_DRIVER_H__ */
