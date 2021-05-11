/******************************************************************************
Example program I2C-DAC interface with Arduino.

SETUP:    I2C-DAC => Arduino
          PIN2 => ground, PIN3 => +5V, PIN4 => A4(SDA), PIN5 => A5(SCL)
Note:     The program is written for address 0x98 (Arduino address 0x4C).
          This program was tested using Arduino Nano
Document: DAC5571 datasheet
Updated:  September 4, 2008
E-mail:   support@gravitech.us
          Gravitech
(C) Copyright 2008 All Rights Reserved
*******************************************************************************/

#include <Wire.h> 

#define Binary 0
#define Hex 1

/*******************************************************************************
                      Function Prototype
*******************************************************************************/  
unsigned int SerialNumRead (byte);

/*******************************************************************************
                      Setup
*******************************************************************************/ 
void setup() 
{ 
  Serial.begin(9600);
  Wire.begin();             // join i2c bus (address optional for master) 
  delay(1000);
} 
 
/*******************************************************************************
                      Main Loop
*******************************************************************************/  
void loop() 
{
  const int I2C_address = 0x4C;  // I2C write address 
  
  byte DACval;                  // Store D/A value
  byte DAT0;                    // I2C data
  byte DAT1;                    // I2C data
  
  delay(100);
  
  // Display prompt for D/A value
  Serial.print("Enter D/A value in HEX (0-255): ");
  
  DACval = SerialNumRead (Binary);  // Get DAC data from user 
  Serial.println(DACval,HEX);
  DAT1 = DACval >> 4;            // Ctrl/MS-Byte (PD1&PD0 = 0) 
  DAT0 = DACval << 4;            // LS-Byte
    
  // Setup DAC
  Wire.beginTransmission(I2C_address);
  Wire.send(DAT1);
  Wire.send(DAT0);
  Wire.endTransmission();  
}

/*******************************************************************************
       Read a input number from the Serial Monitor ASCII string
       Return: A binary number or hex number
*******************************************************************************/ 
unsigned int SerialNumRead (byte Type)
{
  unsigned int Number = 0;       // Serial receive number
  unsigned int digit = 1;        // Digit
  byte  i = 0, j, k=0, n;        // Counter
  byte  ReceiveBuf [5];          // for incoming serial data
  
  while (Serial.available() <= 0);
  
  while (Serial.available() > 0)  // Get serial input
  {
    // read the incoming byte:
    ReceiveBuf[i] = Serial.read();
    i++;
    delay(10);
  }
  
  for (j=i; j>0; j--)
  {
    digit = 1;
    
    for (n=0; n<k; n++)          // This act as pow() with base = 10
    {
      if (Type == Binary)
        digit = 10 * digit;
      else if (Type == Hex)
        digit = 16 * digit;
    }
        
    ReceiveBuf[j-1] = ReceiveBuf[j-1] - 0x30;    // Change ASCII to BIN
    Number = Number + (ReceiveBuf[j-1] * digit); // Calcluate the number
    k++;
  }
  return (Number);    
}

/* From Linux driver
https://github.com/torvalds/linux/blob/master/drivers/iio/dac/ti-dac5571.c

static int dac5571_cmd_quad(struct dac5571_data *data, int channel, u16 val)
{
	unsigned int shift;

	shift = 16 - data->spec->resolution;
	data->buf[2] = val << shift;
	data->buf[1] = (val >> (8 - shift));
	data->buf[0] = (channel << DAC5571_CHANNEL_SELECT) |
		       DAC5571_LOADMODE_DIRECT;

	if (i2c_master_send(data->client, data->buf, 3) != 3)
		return -EIO;

	return 0;
}

*/
