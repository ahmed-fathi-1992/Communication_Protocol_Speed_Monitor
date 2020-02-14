/*
 * USART.c
 *
 * Created: 2/9/2020 2:01:56 PM
 *  Author: Ema
 */ 

#include "USART.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
void UART_init(void)
{
	/ * U2X = 1 for double transmission speed * /
	UCSRA.B.U2X1 = 1;
	/ ************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 *********************************************************************** / 
	UCSRB.UCSRB_ST.RXEN1 = 1;
	UCSRB.UCSRB_ST.TXEN1 = 1;
	
	/ ************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 *********************************************************************** / 	
	UCSRC.UCSRC_ST.URSEL1 = 1;
	UCSRC.UCSRC_ST.UCSZ = 3;
	/ *UCSRC.UCSRC_ST.UCSZ01 = 1;
	UCSRC.UCSRC_ST.UCSZ11 = 1;* /
	
	/ * First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH* /
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}
*/


void USART_init(USART_Config * UART_config)
{
	uint8_t UCSRC_URSEL_Value= 128;
	
	UCSRA.B.U2X1 = UART_config->Speed;
	UCSRB.UCSRB_ST.TXEN1 = UART_config->Tx_enable;
	UCSRB.UCSRB_ST.RXEN1 = UART_config->Rx_enable;
	
	UCSRC.UCSRC_B = UCSRC_URSEL_Value|(UART_config->Parity)|(UART_config->Stop)|(UART_config->Mode)|(UART_config->DataSize); 
	
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
	/*UBRRL = 0x67;
	UBRRH = 0;*/

	
}

void UART_sendByte(const uint8_t data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
}

uint8_t UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}

void UART_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}
