/*
 * SPI_.c
 *
 * Created: 10/02/2020 14:17:39
 *  Author: ahmed_pc
 */ 

#include "SPI_.h"


void SPI_Init_(Interrupt_State interrupt_state,SPI_En_State SPI_state , Data_Order data_order ,SPI_Mode SPI_mode ,Clock_Polarity clock_Polarity ,Clock_Phase clock_phase , SPI_Clock_Rate clock_rate)
{
	//SPCR =0b01010001;
	SPCR = SPCR|(interrupt_state | data_order | SPI_mode | clock_Polarity | clock_phase | clock_rate);	
	//Bit 7 SPIE: SPI Interrupt Enable 
	//Bit 6 SPE: SPI Enable
	//Bit 5  DORD: Data Order  1:LSB 0:MSB
	//Bit 4  MSTR: Master/Slave Select   1:Master 0:slave
	//Bit 3  CPOL: Clock Polarity
	//Bit 2  CPHA: Clock Phase
	//Bits 1, 0  SPR1, SPR0: SPI Clock Rate Select 1 and 0 
    
	if(SPI_mode == Master)
	{gpioPinDirection(SPI_MOSI_PORT, SPI_MOSI_PIN, OUTPUT);
	 gpioPinDirection(SPI_MISO_PORT, SPI_MISO_PIN, INPUT);	 	
	 gpioPinDirection(SPI_SCK_PORT, SPI_SCK_PIN, OUTPUT);
	 gpioPinDirection(SPI_SS_PORT, SPI_SS_PIN, OUTPUT);	
	}else
	{gpioPinDirection(SPI_MOSI_PORT, SPI_MOSI_PIN, INPUT);
	 gpioPinDirection(SPI_MISO_PORT, SPI_MISO_PIN, OUTPUT);
	 gpioPinDirection(SPI_SCK_PORT, SPI_SCK_PIN, INPUT);
	 gpioPinDirection(SPI_SS_PORT, SPI_SS_PIN, INPUT);
	}
	
	SPCR = SPCR|SPI_state;
    		
}
void SPI_Send_(char data)
{
	SPDR=data;
	while(!(SPSR& 0x80)); // wait until send complete

	
}
char SPI_Recive(void)
{
	while(!(SPSR& 0x80)); // wait until receive complete
	  return SPDR ;			
}


char SPI_Recive_Unblock(char* data)
{
	/*
	while(!(SPSR& 0x80)); // wait until receive complete
	return SPDR ;
	*/
	if ((SPSR& 0x80)==1)
	{
		*data=SPDR;
		return 0;
	}else
	{
		return 1;
	}
	
}

