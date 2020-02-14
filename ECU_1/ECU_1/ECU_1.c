/*
 * ECU_1.c
 *
 * Created: 10/02/2020 11:56:27
 *  Author: ahmed_pc
 */ 
//#include <avr/io.h>

//#include "USART.h"
#include "SPI_.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "timers.h"
#include "USART.h"

int main(void)
{
	char Speed=0x01;
	
	USART_Config ST_Config={USART_BAUDRATE,TX_ENABLE,RX_ENABLE,NO_DOUBLE_SPEED,DATA_SIZE_8,PARITY_DISABLE,STOP_1BIT,ASYNCH};
	
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	
	USART_init(&ST_Config);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64, 0, 0, T0_INTERRUPT_NORMAL);
	SPI_Init_(Interrupt_Enable,SPI_Enable,LSB,Master,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);
	
	Speed = UART_recieveByte();
	while(1)
	{
		timer0DelayMs(100);
				if( Prepressed== pushButtonGetStatus(BTN_0))
				{
					if (Speed<10)
					{Speed++;
					}
					while(Prepressed== pushButtonGetStatus(BTN_0));					
				}
				if( Prepressed== pushButtonGetStatus(BTN_1))
				{
					if (Speed>0)
					{Speed--;
					}
					while(Prepressed== pushButtonGetStatus(BTN_1));	
				}	
		SPI_Send_(Speed);	
	}
}


/*
	SPCR =0b00110001;
	SPSR =0x00;	
	PORTB_DIR=0b10111110;
	SPCR =0b01110001;
	
   */

