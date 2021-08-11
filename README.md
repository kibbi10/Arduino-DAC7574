Arduino Library to drive the DAC7574 Quad 12Bit DAC Chip
----

Very simple library which writes to one of the 4 (A,B,C,D) channels of the
TI DAC7574 12 bit DAC using I2C.

https://www.ti.com/product/DAC7574

Just include the library in the project and initialize the object e.g. by
```c++
#include <DAC7574.h>
DAC7574 dac;
```
and then you can set the voltage on each of the four channels A through D by
```c++
dac.setVoltage(level, channel);
```
where `level` and `channel` are type `int` in the range 0-4095 and 0-3 respectively.
