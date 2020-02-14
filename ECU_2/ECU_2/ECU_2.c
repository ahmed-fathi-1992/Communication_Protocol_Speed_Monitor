/*
 * ECU_2.c
 *
 * Created: 10/02/2020 11:58:29
 *  Author: ahmed_pc
 */ 


#include "SPI_.h"
#include "softwareDelay.h"
#include "sevenSeg.h"
#include "pushButton.h"
#include "timers.h"
#include "USART.h"
//#include <avr/io.h>



	
int main(void)
{
	char Received_Speed=0x00;
	int distance=0;
	USART_Config ST_Config={USART_BAUDRATE,TX_ENABLE,RX_ENABLE,NO_DOUBLE_SPEED,DATA_SIZE_8,PARITY_DISABLE,STOP_1BIT,ASYNCH};
		
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
				
    USART_init(&ST_Config);

   timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64, 0, 0, T0_INTERRUPT_NORMAL);
  
	SPI_Init_(Interrupt_Enable,SPI_Enable,LSB,Slave,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);			
		
    timer0DelayMs(100);
while(1)
{	
	
	while(Released == pushButtonGetStatus(BTN_0));
	Received_Speed = SPI_Recive();
	while(Released == pushButtonGetStatus(BTN_1))
	{
		SPI_Recive_Unblock(&Received_Speed);
		//Received_Speed = SPI_Recive();
		timer0DelayMs(100);
		distance = distance + Received_Speed;		
	}
	UART_sendByte(distance /10);
	distance =0;
	
}
	
}




/*
int main(void)
{
	char Received=0x00;
	
	//	gpioPinDirection(SEG_EN1_GPIO, SEG_EN1_BIT, OUTPUT);
	//	gpioPinWrite(SEG_EN1_GPIO, SEG_EN1_BIT, SEG_ENABLE);

        gpioPinDirection(GPIOD, BIT4, OUTPUT);
	

SPI_Init_(Interrupt_Enable,SPI_Enable,LSB,Slave,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);

	sevenSegInit(SEG_0);
	sevenSegWrite(SEG_0, 4);
	
 			gpioPinWrite(GPIOD, BIT4, HIGH);
 			softwareDelayMs(2000);
 			gpioPinWrite(GPIOD, BIT4, LOW );
			 softwareDelayMs(2000);
			
	while(1)
	{	
		//UART_sendByte('a');
		Received = SPI_Recive();
		sevenSegWrite(SEG_0, Received);
			
		if (Received>3 && Received<7 )
		{gpioPinWrite(GPIOD, BIT4, HIGH);

		}else
		gpioPinWrite(GPIOD, BIT4, LOW);
		}
				
	
}
*/

	/*
 	SPCR =0b00100001;
 	SPSR =0x00; 	
 	PORTB_DIR=0b10111110;
 	SPCR =0b01100001;
	 */
	
	