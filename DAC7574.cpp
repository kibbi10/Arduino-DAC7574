/**************************************************************************
    DAC7574 quad 12-bit DAC chip from Texas Instruments
    https://www.ti.com/product/DAC7574

    Written by Tryggvi Kr Tryggvason
    Grein Research ehf
    Iceland

**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "DAC7574.h"
// unsigned char CMD_BYTES[4] = {0x08,0xA,0xC,0x16}; // Channels A,B,C,D

DAC7574::DAC7574() {
}

void DAC7574::begin(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}
 
void DAC7574::setVoltage( uint16_t data, int channel )
{
  #ifdef TWBR
    uint8_t twbrback = TWBR;
    TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
  #endif
  
  Wire.beginTransmission(_i2caddr);
  // Write command based on channel
  if (channel == 0) {
    Wire.write(CMD_A);
  } else if (channel == 1) {
    Wire.write(CMD_B);
  } else if (channel == 2) {
    Wire.write(CMD_C);
  } else if (channel == 3) {
    Wire.write(CMD_D);
  }

  Wire.write(data >> 4);
  Wire.write(data << 4);
  Wire.endTransmission();

  #ifdef TWBR
    TWBR = twbrback;
  #endif
}
