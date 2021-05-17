/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.h
    @author   K. Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	This is a library for the Adafruit MCP4725 breakout board
	----> http://www.adafruit.com/products/935
	
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#define MCP4726_CMD_WRITEDAC            (0x40)  // Writes data to the DAC
// unsigned char CMD_BYTES[4] = {0x08,0xA,0xC,0x16}; // Channels A,B,C,D
#define CMD_A  (0x08)
#define CMD_B  (0xA)
#define CMD_C  (0xC)
#define CMD_D  (0x16)



class DAC7574{
 public:
  DAC7574();
  void begin(uint8_t a);  
  void setVoltage( uint16_t outputvl, int channel);
  private:
  uint8_t _i2caddr;
};
