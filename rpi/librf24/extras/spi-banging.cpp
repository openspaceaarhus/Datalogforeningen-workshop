/* 
 * File:   spi.cpp
 * Author: Rasmus Rohde <rohde@duff.dk>
 * 
 * Example on how the SPI interface can be 'bit banged'.
 *
 * For this to work you need to export GPIO 10 and 11 as output and GPIO 9 as input.
 */

#include "spi.h"
#include "gpio.h"

SPI::SPI() {
}

void SPI::setbits( uint8_t bits )
{
 this->bits = bits;
}

void SPI::setspeed( uint32_t speed )
{
 this->speed = speed;
}

void SPI::setdevice( string devicefile ) 
{
	this->device = devicefile;
}

void SPI::init()
{
}

uint8_t SPI::transfer(uint8_t tx_)
{
	uint8_t result = 0;

	GPIO gpio;

	for(int i=0; i<8; i++) {
		// Write MOSI
		gpio.write(10, (tx_ & 0x80) ? 1 : 0);
		tx_ <<= 1;

		// SCK high
		gpio.write(11, 1);

		result <<= 1;
		// Read MISO
		result |= (gpio.read(9) != 0) ? 1 : 0;

		// SCK low
		gpio.write(11, 0);
	}

	return result;
}

SPI::~SPI() {
}

