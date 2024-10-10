#ifndef __STM32F103XX_I2C_DRIVER_H__
#define "stm32f103xx_i2c_driver.h"

#include "stm32f103xx.h"


typedef enum
{
	I2C_MODE_SLAVE_TX = 0,
	I2C_MODE_SLAVE_RX,
	I2C_MODE_MASER_TX,
	I2C_MODE_MASTER_Rx
}I2C_Mode_t;

typedef enum
{
	I2C_ADDR_MODE_7BIT = 0,
	I2C_ADDR_MODE_10BIT
}I2C_ADDRMode_t;

typedef enum
{
	I2C_SM_CLK = 0, 	/* Standard mode 2MHz */
	I2C_FM_CLK,		/* Fast mode 4MHz */
}I2C_CLKMode_t;

typedef enum
{
	I2C_ACK_DISABLE = 0,
        I2C_ACK_ENABLE,
}I2C_ACKE_t;





















#endif /* __STM32F103XX_I2C_DRIVER_H__ */
