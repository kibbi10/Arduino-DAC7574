#include <Wire.h>
#include <DAC7574.h>

#define DAC_ADDR 0x4C

int input = A8;

DAC7574 dac;

void setup() {
  Wire.begin();
  delay(100);
  dac.begin(DAC_ADDR);
  delay(100);
  Serial.begin(115200);
  while(!Serial)
  delay(100);
  Serial.println("Ready.\n");
  Serial.println("Writing 0 to dac ... ");
  delay(100);
  dac.setVoltage(0, 0);
  Serial.print("Voltage read on A8: ");
  Serial.println(analogRead(input));
  delay(500);
  Serial.println("Writing 2.5V to dac (Channel 0)");
  delay(500);
  dac.setVoltage(2047, 0);
  Serial.print("Voltage read on A8: ");
  Serial.println(analogRead(input));
  Serial.println("Done.");
}

void loop() {

}
