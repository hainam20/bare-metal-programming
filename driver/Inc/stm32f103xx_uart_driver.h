#ifndef __STM32F103XX_UART_DRIVER_H__
#define __STM32F103XX_UART_DRIVER_H__

#include "stm32f103xx.h"

/*
 * Configuration structure for USARTx peripheral
 */


typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_StopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;

/* 
 * Handle structure for USARTx peripheral
 */

typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t USART_Config;
}USART_Handle_t;


/****************************************************************************************
 * 			Usart config defination macros					*
 ****************************************************************************************/

/*
 * @USART Mode
 */
#define USART_MODE_ONLY_TX	0
#define USART_MODE_ONLY_RX	1
#define USART_MODE_TXRX		2

/*
 * USART Buad
 */

#define USART_STD_BAUD_1200	1200
#define USART_STD_BAUD_2400	2400
#define USART_STD_BAUD_9600	9600
#define USART_STD_BAUD_19200	19200
#define USART_STD_BAUD_38400	38400
#define USART_STD_BAUD_57600	57600
#define USART_STD_BAUD_115200	115200
#define USART_STD_BAUD_230400	230400
#define USART_STD_BAUD_460800	460800
#define USART_STD_BAUD_921600	921600
#define USART_STD_BAUD_2M	2000000
#define USART_STD_BAUD_3M	3000000

/*
 * USART Parity Control
 */

#define USART_PARITY_EN_ODD	3
#define USART_PARITY_EN_EVEN	1
#define USART_PARITY_DISABLE	0

/*
 * USART WordLength
 */

#define USART_WORDLEN_8BITS	0
#define USART_WORDLEN_9BITS	1

/*
 * USART Stop bits
 */

#define USART_STOPBITS_1	0
#define USART_STOPBITS_0_5	1
#define USART_STOPBITS_2	2
#define USART_STOPBITS_1_5	3

/*
 * USART HWFlow Control
 */

#define USART_HW_FLOW_CTRL_NONE		0
#define USART_HW_FLOW_CTRL_CTS		1
#define USART_HW_FLOW_CTRL_RTS		2
#define USART_HW_FLOW_CTRL_CTS_RTS	3



/****************************************************************************************
 * 			USART register bit defination macros				*
 ****************************************************************************************/

/* 
 * USART Status register
 */

#define USART_SR_PE		0	/* Parity Error */
#define USART_SR_FE		1	/* Framing Error */
#define USART_SR_NE		2	/* Noise Error flag */
#define USART_SR_ORE		3	/* Overun Error */
#define USART_SR_IDLE		4	/* IDLE line detected */
#define USART_SR_RXNE		5	/* Read data register not empty */
#define USART_SR_TC		6	/* Transmission complete */
#define USART_SR_TXE		7	/* Transmit data register empty */
#define USART_SR_LBD		8	/* LIN break detection flag */
#define USART_SR_CTS		9	/* CTS flag */


/*
 * USART BRR Register
 */

#define USART_BRR_DIV_FRATION	0	/* Fraction of USARTDIV */
#define USART_BRR_DIV_MANTISSA 	4	/* Mantissa of USARTDIV */

/*
 * USART CR1 register
 */

#define USART_CR1_SBK		0	/* Send break */
#define USART_CR1_RWU		1	/* Receiver wakeup */
#define USART_CR1_RE		2	/* Receiver enable */
#define USART_CR1_TE		3	/* Transmitter enable */
#define USART_CR1_IDLEIE	4	/* IDLE Interupt enable */
#define USART_CR1_RXNEIT	5	/* RXNE	interrupt enable */
#define USART_CR1_TCIE		6	/* Transmission complete interrupt enable */
#define USART_CR1_TXEIE		7	/* TXE interrupt enable */
#define USART_CR1_PEIE		8	/* PE interrupe enable */
#define USART_CR1_PS		9	/* Parity selection */
#define USART_CR1_PCE		10	/* Parity control enable */
#define USART_CR1_WAKE		11	/* Wakeup method */
#define USART_CR1_M		12	/* Word length */
#define USART_CR1_UE		13	/* USART Enable */

#define USART_CR1_OVER8		15
/*
 * USART CR2 register
 */

#define USART_CR2_ADD		0	/* Address of the USART node */
#define USART_CR2_LBDL		5	/* Lin break detection length */
#define USART_CR2_LBDIE		6	/* LIN break detection interrupt enable */
#define USART_CR2_LBCL		8	/* Last bit clock pulse */
#define USART_CR2_CPHA		9	/* Clock phase */
#define USART_CR2_CPOL		10 	/* Clock polarity */
#define USART_CR2_CLKEN		11	/* Clock Enable */
#define USART_CR2_STOP		12	/* STOP bits */
#define USART_CR2_LINEN		13	/* LIN mode eable */

/*
 * USART CR3 register
 */

#define USART_CR3_EIE		0 	/* Error interrupt enable */
#define USART_CR3_IREN		1	/* IrDA mode enable */
#define USART_CR3_IRLP		2 	/* IrDA low-power */
#define USART_CR3_HDSEL		3	/* Half-duplex selection */
#define USART_CR3_NACK		4 	/* Smartcard NACK enable */
#define USART_CR3_SCEN		5	/* Smartcard moode enable */
#define USART_CR3_DMAR		6	/* DMA enable receiver */
#define USART_CR3_DMAT		7	/* DMA enable transmitter */
#define USART_CR3_RTSE		8	/* RTS enable */
#define USART_CR3_CTSE		9	/* CTS Enable */
#define USART_CR3_CTSIE		10	/* CTS interrupt enable */

/* 
 * USART GTPR register
 */

#define USART_GTPR_PSC		0	/* Prescaler value Biss 0:7 */
#define USART_GTPR_GT		8	/* Guard time value Bits 15:8 */


/****************************************************************************************
 * 			Usart FLAG defination macros					*
 ****************************************************************************************/
#define USART_FLAG_TXE		(1 << USART_SR_TXE)
#define USART_FLAG_RXNE		(1 << USART_SR_RXNE)
#define USART_FLAG_TC		(1 << USART_SR_TC)


/****************************************************************************************
 * 				USART API						*
 ****************************************************************************************/

/*
 * Peripheral clock setup
 */

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and Deinit
 */

void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

/*
 * Data send and Receive
 */

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHanle, uint8_t *RxBufeer, uint32_t Len);

/*
 * Other API
 */

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

/*
 * IRQ Configuration and ISR Handling
 */

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSARTHanle);






#endif /* __STM32F103XX_UART_DRIVER_H__ */
