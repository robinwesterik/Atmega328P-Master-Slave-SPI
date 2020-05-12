
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

#define SS DDB2 //Slave select
#define MOSI DDB3 //Master out slave in
#define MISO DDB4 //Master in slave out
#define SCK DDB5 //Serial clock

void spiSetup(void)
{
	DDRB |= (1 << MISO); // Set MISO output, all others (SCK, SS) input
	SPCR |= (1 << SPE) | (1 << SPIE); // Set SPI Enable pin, enable spi receive interrupts
}

int main(void)
{
	sei(); // Enable global interrupts
	DDRD = 0xFF; // set port D as output
	PORTD = 0xFF; // Turn pins initially on
	spiSetup();
	
	while (1)
	{
	}
}

ISR (SPI_STC_vect){
	PORTD = SPDR; // set port D as SPI Data Register from Master
}
