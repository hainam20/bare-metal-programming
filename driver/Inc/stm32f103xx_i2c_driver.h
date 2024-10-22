#ifndef __STM32F103XX_I2C_DRIVER_H__
#define __STM32F103XX_I2C_DRIVER_H__

#include "stm32f103xx.h"


typedef enum
{
	I2C_ADDR_MODE_7BIT = 0,
	I2C_ADDR_MODE_10BIT
}I2C_ADDRMode_t;

typedef enum
{
	I2C_SCL_SPEED_SM = 0, 		/* Standard mode 2MHz */
	I2C_SCL_SPEED_FM,		/* Fast mode 4MHz */
}I2C_Speed_t;
/*
typedef enum
{
	I2C_ACK_DISABLE = 0,
        I2C_ACK_ENABLE,
}I2C_ACKControl_t;
*/
typedef enum
{
	I2C_FM_DUTY_2 = 0,
        I2C_FM_DUTY_16_9,
}I2C_FMDuty_t;	


typedef struct
{
	uint8_t I2C_DeviceAddress;
	I2C_Speed_t I2C_SCLSpeed;
	uint8_t I2C_ACKControl;
	I2C_FMDuty_t I2C_FMDutyCycle;
}I2C_Config_t;


/* ----------- Define macro for register -------------- */

/*
 * @I2C_CR1
 */

#define I2C_CR1_PE 		0
#define I2C_CR1_SMBUS_MODE  	1
#define I2C_CR1_SMBTYPE		3
#define I2C_CR1_ENARP		4
#define I2C_CR1_ENPEC		5
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK		10
#define I2C_CR1_POS		11	// PEC Position
#define I2C_CR1_PEC		12	// Packet Error Checking
#define I2C_CR1_ALERT		13
#define I2C_CR1_SWRST		15	// Software Reset

/*
 * @I2C_CR2
 */

#define I2C_CR2_FRQE		0
#define I2C_CR2_ITERREN		8	/* Error Interrupt Ennable */
#define I2C_CR2_ITEVTEN		9	/* Event Interrupt Enable */
#define I2C_CR2_ITBUFEN		10	/* Buffer Interrupt Enable */
#define I2C_CR2_DMAEN		11	/* DMA Request Enable */
#define I2C_CR2_LAST		12	/* DMA Last Transfer */

/*
 * @I2C_OAR1
 */
#define I2C_OAR1_ADDMODE	15

/*
 * @I2C_OAR2
 */

#define I2C_OAR2_ENDUAL		0

/*
 * @I2C_SR1
 * Status Register
 */

#define	I2C_SR1_SB		0
#define I2C_SR1_ADDR		1		
#define I2C_SR1_BTF		2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define	I2C_SR1_RXNE		6
#define I2C_SR1_TXE		7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF		10
#define I2C_SR1_OVR		11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALERT	15

/*
 * @I2C_SR2
 */

#define I2C_MSL			0
#define I2C_BUSY_FLAG		1
#define I2C_TRA			2
#define I2C_GENCALL		4
#define I2C_SMBDEFAULT		5
#define I2C_SMHOST		6
#define I2C_DUAL_FLAH		7
#define I2C_PEC			8

/*
 * Define I2C flags marcro
 */

#define I2C_FLAG_TXE		(1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE		(1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB		(1 << I2C_SR1_SB)
#define I2C_FLAG_OVR		(1 << I2C_SR1_OVR)
#define I2C_FLAG_AF 		(1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO		(1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR		(1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF 		(1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10		(1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF		(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR		(1 << I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT	(1 << I2C_SR1_TIMEOUT)


#define I2C_ACK_ENABLE 		ENABLE
#define I2C_ACK_DISABLE		DISABLE

/* 
 * SPI Init and DeInit
 */

void I2C_Init(I2C_RegDef_t *pI2Cx, I2C_Config_t *I2C_Config);

void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * SPI Clock Setup
 */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


void I2C_PeripheralControl(I2C_RegDef_t *I2Cx, uint8_t EnorDi);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint8_t FlagName);


/* Other I2C funtion */

void I2C_ManageAck(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


/*
 * SPI Send and Receive data
 */



void I2C_MasterSendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);

void I2C_MasterReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, I2C_Config_t *I2CConfig);


void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx, uint8_t data);

uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2Cx);


/*
 * I2C Interrupt 
 */

void I2CIRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2CIRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);











#endif /* __STM32F103XX_I2C_DRIVER_H__ */
