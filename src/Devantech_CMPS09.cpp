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

#include "Devantech_CMPS09.h"

const uint8_t REG_MAGX_HIGH = 10;
const uint8_t REG_MAGX_LOW = 11;
const uint8_t REG_MAGY_HIGH = 12;
const uint8_t REG_MAGY_LOW = 13;
const uint8_t REG_MAGZ_HIGH = 14;
const uint8_t REG_MAGZ_LOW = 15;
const uint8_t REG_ACCX_HIGH = 16;
const uint8_t REG_ACCX_LOW = 17;
const uint8_t REG_ACCY_HIGH = 18;
const uint8_t REG_ACCY_LOW = 19;
const uint8_t REG_ACCZ_HIGH = 20;
const uint8_t REG_ACCZ_LOW = 21;
const uint8_t REG_CMD = 22;

int16_t Devantech_CMPS09::magX()
{
  return (int16_t)regReadWord(REG_MAGX_HIGH);
}

int16_t Devantech_CMPS09::magY()
{
  return (int16_t)regReadWord(REG_MAGY_HIGH);
}

int16_t Devantech_CMPS09::magZ()
{
  return (int16_t)regReadWord(REG_MAGZ_HIGH);
}

int16_t Devantech_CMPS09::accX()
{
  return (int16_t)regReadWord(REG_ACCX_HIGH);
}

int16_t Devantech_CMPS09::accY()
{
  return (int16_t)regReadWord(REG_ACCY_HIGH);
}

int16_t Devantech_CMPS09::accZ()
{
  return (int16_t)regReadWord(REG_ACCZ_HIGH);
}

Devantech_Compass::CompassStatus Devantech_CMPS09::doCalibration(CompassPoint cp)
{
  if(cp != CP_DEFAULT && cp != nextCP)
  {
    return CS_SEQUENCE_ERROR;
  }
  if(nextCP == CP_NORTH)
  {
    if( regWriteByteFrame(REG_CMD,0xF0,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  }
  if( regWriteByteFrame(REG_CMD,0xF5,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if(nextCP == CP_WEST)
  {
    nextCP = CP_NORTH;
    return CS_ALL_COMPLETE;
  }
  else
  {
    nextCP = CompassPoint((int)nextCP+1);
    return CS_STEP_COMPLETE;
  }
}

Devantech_Compass::CompassStatus Devantech_CMPS09::resetCalibration()
{
  if( regWriteByteFrame(REG_CMD,0x20,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0x2A,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0x60,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassStatus Devantech_CMPS09::configureDeviceId(uint8_t newDeviceId)
{
  if( regWriteByteFrame(REG_CMD,0xA0,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xAA,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xA5,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,newDeviceId << 1,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassCaps Devantech_CMPS09::getCaps()
{
  return CompassCaps(
    CC_CALIBRATE |
    CC_CALIBRATE_FOUR_STEP |
    CC_FACTORY_RESET |
    CC_PITCH_AND_ROLL |
    CC_MAG_XYZ |
    CC_ACC_XYZ |
    CC_CONFIG_DEVICE_ID);

}
