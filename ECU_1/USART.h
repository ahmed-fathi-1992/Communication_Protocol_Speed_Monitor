/*
 * USART.h
 *
 * Created: 2/9/2020 2:02:18 PM
 *  Author: Ema
 */ 


#ifndef USART_H_
#define USART_H_

#include "USART_Config.h"
/*******************************************************************************
 *                      User Defined Types                                     *
 *******************************************************************************/
/*
volatile UCSRA_Reg * const UCSRA_ptr = (volatile UCSRA_Reg*)&UCSRA; 
volatile UCSRB_Reg * const UCSRB_ptr = (volatile UCSRA_Reg*)&UCSRB;
volatile UCSRC_Reg * const UCSRC_ptr = (volatile UCSRA_Reg*)&UCSRC;
*/ 

typedef struct usart_config{
	
	UCSRA_Reg UCSRA_Init;
	UCSRB_Reg UCSRB_Init;
	UCSRC_Reg UCSRC_Init;
	
	}USART_Config;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600
# define F_CPU 8000000UL

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
extern void UART_init(void);

extern void USART_init(USART_Config UART_config);

extern void UART_sendByte(const uint8_t data);

extern uint8_t UART_recieveByte(void);

extern void UART_sendString(const uint8_t *Str);

extern void UART_receiveString(uint8_t *Str); // Receive until #




#endif /* USART_H_ */