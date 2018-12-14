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

#include "Devantech_CMPS01Rev03.h"

const uint8_t REG_CALIBRATE_DONE = 14;
const uint8_t REG_CALIBRATE_CMD = 15;


Devantech_Compass::CompassStatus Devantech_CMPS01Rev03 ::doCalibration(CompassPoint cp)
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(REG_CALIBRATE_CMD);
  WIRE_WRITE((uint8_t)0xFF);
  if( (commsError = Wire.endTransmission()) != 0 ) return CS_COMMS_ERROR;
  return CS_CALIBRATING;
}

Devantech_Compass::CompassStatus Devantech_CMPS01Rev03::getCalibrationStatus()
{
  uint8_t data = regReadByte(REG_CALIBRATE_DONE);
  if(data == 0xff)
  {
    return CS_READY_COMMIT;
  }
  else
  {
    return CS_CALIBRATING;
  }
}
  


Devantech_Compass::CompassStatus Devantech_CMPS01Rev03 ::commitCalibration()
{
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(REG_CALIBRATE_CMD);
  WIRE_WRITE((uint8_t)0x0);
  if( (commsError = Wire.endTransmission()) != 0 ) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassCaps Devantech_CMPS01Rev03::getCaps()
{
  return CompassCaps(CC_CALIBRATE | CC_CALIBRATE_REPORTS_WHEN_DONE | CC_CALIBRATE_NEEDS_COMMIT);
}
