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

#include "Devantech_CMPS03Rev15.h"

const uint8_t REG_UNLOCK_1 = 12;
const uint8_t REG_UNLOCK_2 = 13;
const uint8_t REG_UNLOCK_3 = 14;
const uint8_t REG_CALIBRATE_CMD = 15;


Devantech_Compass::CompassStatus Devantech_CMPS03Rev15::setScanPeriod(ScanPeriod sp)
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(REG_UNLOCK_1);
  WIRE_WRITE((uint8_t) 0x55);
  WIRE_WRITE((uint8_t) 0x5A);
  WIRE_WRITE((uint8_t) 0xA5);
  WIRE_WRITE((uint8_t) sp);
  if( (commsError = Wire.endTransmission()) != 0 ) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassCaps Devantech_CMPS03Rev15::getCaps()
{
  return Devantech_CMPS03Rev14::getCaps() | CC_SET_SCAN_PERIOD;
}
