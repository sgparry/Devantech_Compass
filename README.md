# Devantech_Compass
Simple Arduino (Unofficial) class library that supports the following compass modules produced by Devantech:

* CMPS01 reV 3
* CMPS01 rev 7
* CMPS03 rev 8
* CMPS03 rev 14
* CMPS03 rev 15
* CMPS09
* CMPS10
* CMPS11

To install, first ensure you have Git installed. Open an OS or Git Bash shell. Change directory to the Libraries sub-folder of your Arduino sketchbook area:

`cd ~/Arduino/Libraries`

Use git to pull the source:
 
`git clone https://github.com/sgparry/Devantech_Compass`

Restart the Arduino IDE.

Here is a simple example of how to initalize and read a CMPS11 compass. The reading is printed out to the serial once per second:

```C++
#include <Arduino.h>
#include <Devantech_CMPS11.h>
#include <Wire.h>
const uint8_t COMPASS_I2C = 0x60;
const uint8_t MASTER_I2C = 3;

Devantech_TCCompass* compass;

void setup() {
  Wire.begin( MASTER_I2C );
  compass = new Devantech_CMPS11( COMPASS_I2C );

}

void loop() {
  static long prevMillis = 0;
  long currMillis = millis();
  if ( currMillis > prevMillis + 1000 ) {
    Serial.print( compass->bearingDegrees() );
    prevMillis = currMillis;
  }
}
```