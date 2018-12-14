/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

// Derived from code by Dirk Grappendorf (www.grappendorf.net)
// for the SRF02 sensor.
#if ARDUINO >= 100
#include "Arduino.h"
#define WIRE_WRITE Wire.write
#define WIRE_READ Wire.read
#else
#include "WProgram.h"
#define WIRE_WRITE Wire.send
#define WIRE_READ Wire.receive
#endif
#include "Wire.h"
#include "Devantech_Compass.h"

const int REG_VER = 0;
const int REG_BEARING_BYTE = 1;
const int REG_BEARING_HIGH = 2;
const int REG_BEARING_LOW = 3;


/* registers
0   Software version
1     Compass Bearing as a byte, i.e. 0-255 for a full circle
2,3     Compass Bearing as a word, i.e. 0-3599 for a full circle, representing 0-359.9 degrees.
4   Pitch angle - signed byte giving angle in degrees from the horizontal plane
5   Roll angle - signed byte giving angle in degrees from the horizontal plane
6   Unused
7   Unused
8   Unused
9   Unused
10,11   Magnetometer X axis raw output, 16 bit signed integer with register 10 being the upper 8 bits
12,13   Magnetometer Y axis raw output, 16 bit signed integer with register 12 being the upper 8 bits
14,15   Magnetometer Z axis raw output, 16 bit signed integer with register 14 being the upper 8 bits
16,17   Accelerometer  X axis raw output, 16 bit signed integer with register 16 being the upper 8 bits
18,19   Accelerometer  Y axis raw output, 16 bit signed integer with register 18 being the upper 8 bits
20,21   Accelerometer  Z axis raw output, 16 bit signed integer with register 20 being the upper 8 bits
*/

Devantech_Compass::Devantech_Compass(uint8_t deviceId)
{
  this->deviceId = deviceId;
  lastRead = -1;
}

uint8_t Devantech_Compass::version()
{
  return regReadByte(REG_VER);
}
uint8_t Devantech_Compass::bearingByte()
{
  return regReadByte(REG_BEARING_BYTE);
}

int16_t Devantech_Compass::bearingTenthDegrees()
{
  unsigned long currRead = millis();
  float currBearing = regReadWord(REG_BEARING_HIGH);
  if(currRead > read + 250)
  {
    lastRead = read;
    lastBearing = bearing;
  }
  bearing = currBearing;
  read = currRead;
  return currBearing;
}

float Devantech_Compass::turnRate()
{
  bearingTenthDegrees();
  if(lastRead == -1)
    return 0.0;
  else
  {
    int16_t diff = float(bearing - lastBearing) / 10.0;
    if(diff > 1800)
      diff -= 3600;
    else if (diff < -1800)
      diff += 3600;
    return float(diff) * 100.0 / (float)(read - lastRead);
  }
}


void Devantech_Compass::regReadN(uint8_t regNo, byte* buffer, uint8_t count)
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(regNo);
  if( (commsError = Wire.endTransmission()) != 0 ) return -1;
  Wire.requestFrom(deviceId, count);
  while(Wire.available() < count);;
  uint8_t i = 0;
  while(i < count)
    buffer[i++] = WIRE_READ();
}

uint8_t Devantech_Compass::regReadByte(uint8_t regNo)
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(regNo);
  if( (commsError = Wire.endTransmission()) != 0 ) return -1;
  Wire.requestFrom(deviceId, (uint8_t) 1);
  return (uint8_t)(WIRE_READ());
}

uint16_t Devantech_Compass::regReadWord(uint8_t regNo)
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(regNo);
  if( (commsError = Wire.endTransmission()) != 0 ) return -1;
  Wire.requestFrom(deviceId, (uint8_t) 2);
  while(Wire.available() < 2) ;
  uint8_t hi = WIRE_READ();
  uint8_t lo = WIRE_READ();
  return (((uint16_t)hi) << 8) + ((uint16_t)lo);
}

Devantech_Compass::CompassStatus Devantech_Compass::regWriteByteFrame(uint8_t reg, uint8_t val, int delayMs)
{
    Wire.beginTransmission(deviceId);
    WIRE_WRITE(reg);
    WIRE_WRITE(val);
    if( (commsError = Wire.endTransmission()) != 0 ) return CS_COMMS_ERROR;
    delay(delayMs);
    return CS_COMMS_OK;
}
