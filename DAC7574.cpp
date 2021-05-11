/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.cpp
    @author   K.Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the Adafruit MCP4725 breakout
	----> http://www.adafruit.com/products/935
		
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "Adafruit_MCP4725.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new MCP4725 class
*/
/**************************************************************************/
DAC7574::DAC7574() {
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
void DAC7574::begin(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}
 
/**************************************************************************/
/*! 
Control - Most Significant Byte
    Most Significant Byte CTRL/MSB[7:0] consists of two zeros, two power-down bits, and four most significant bits
    of 8-bit unsigned binary D/A conversion data.

Least Significant Byte
    Least Significant Byte LSB[7:0] consists of the four least significant bits of the 8-bit unsigned binary D/A
    conversion data, followed by four don't care bits. DAC5571 updates at the falling edge of the acknowledge signal
    that follows the LSB[0] bit.
*/
/**************************************************************************/
void DAC7574::setVoltage( uint16_t output, bool writeEEPROM )
{
#ifdef TWBR
  uint8_t twbrback = TWBR;
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
#endif
  Wire.beginTransmission(_i2caddr);
  // Write command
  Wire.write(DAC7574_CMD_WRITEDAC);
  // Write data
  Wire.write(output / 16);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  Wire.write((output % 16) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  Wire.endTransmission();
#ifdef TWBR
  TWBR = twbrback;
#endif
}
