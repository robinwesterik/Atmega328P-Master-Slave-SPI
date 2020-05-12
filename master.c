/* 
 * Author: Robin Westerik
 * Arduino Uno to Uno communication
 * The master segment pushes changes of DDRD (digital pins 0-7) to the other microcontroller via SPI
 */ 


#define F_CPU 16000000
#include <avr/io.h>

#define SS DDB2 //Slave select
#define MOSI DDB3 //Master out slave in
#define MISO DDB4 //Master in slave out
#define SCK DDB5 //Serial clock

void spiSetup(void)
{
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS); // Set SPI pins as output
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Set SPI Enable bit, set to master, set clock rate to fck/16
}

int main(void)
{
	spiSetup();
	DDRD = 0x00; // set port D as input
	char buf = 0; //Initialize buffer
	
    while (1)
    {
		char data = PIND; // read user data  from port D
		if (data != buf) { // if port D has changed
			PORTB &= ~(1 << SS); // Set slave select to active low, enabling the slave
			SPDR = data; // Put port D data into spi data register
			while(!(SPSR & (1 << SPIF))); // Wait until the transmission is complete
			PORTB |= (1 << SS); // disable the slave
			buf = data; //put new data into the buffer
		}
    }
}

