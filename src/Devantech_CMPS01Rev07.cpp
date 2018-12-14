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

#include "Devantech_CMPS01Rev07.h"

const uint8_t REG_CALIBRATE_DONE = 14;
const uint8_t REG_CALIBRATE_CMD = 15;


Devantech_Compass::CompassStatus Devantech_CMPS01Rev07::doCalibration(CompassPoint cp)
{
  if(cp==CP_DEFAULT)
  {
    int i; 
    for(i = CP_NORTH; calibrated[i] && i <= CP_WEST; i++) ;;
    if(i > CP_WEST)
    {
      // recalibrating from scratch:
      cp = CP_NORTH;
      calibrated[CP_NORTH] = false;
      calibrated[CP_EAST] = false;
      calibrated[CP_SOUTH] = false;
      calibrated[CP_WEST] = false;
    }
  }
  Wire.beginTransmission(deviceId);
  WIRE_WRITE(REG_CALIBRATE_CMD);
  WIRE_WRITE((uint8_t)0xFF);
  if( (commsError = Wire.endTransmission()) != 0 ) return CS_COMMS_ERROR;
  calibrated[cp] = true;
  return calibrated[CP_NORTH] && calibrated[CP_EAST] && calibrated[CP_SOUTH] && calibrated[CP_WEST] ? CS_ALL_COMPLETE : CS_STEP_COMPLETE;
}

Devantech_Compass::CompassCaps Devantech_CMPS01Rev07::getCaps()
{
  return CompassCaps(CC_CALIBRATE | CC_CALIBRATE_FOUR_STEP | CC_RECALIBRATE_STEP);
}
