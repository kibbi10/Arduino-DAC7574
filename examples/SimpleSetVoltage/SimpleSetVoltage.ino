#include <DAC7574.h>

#define DAC_ADDR 0x4C

int input = A8;

DAC7574 dac;

void setup() {

  dac.begin(DAC_ADDR);
  Serial.begin(115200);
  while(!Serial)
  Serial.println("Ready.\n");

  Serial.println("Writing 0 to dac ... ");
  dac.setVoltage(0, 0);
  Serial.print("Voltage read on A8: ");
  Serial.println(analogRead(input));
  delay(1500);
  
  Serial.println("Writing 2.5V to dac (Channel 0)");
  dac.setVoltage(2047, 0);
  Serial.print("Voltage read on A8: ");
  Serial.println(analogRead(input));
  Serial.println("Done.");
}

void loop() {

}
