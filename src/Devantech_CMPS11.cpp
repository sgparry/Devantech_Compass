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

#include "Devantech_CMPS11.h"

const int REG_MAGX_HIGH = 6;
const int REG_MAGX_LOW = 7;
const int REG_MAGY_HIGH = 8;
const int REG_MAGY_LOW = 9;
const int REG_MAGZ_HIGH = 10;
const int REG_MAGZ_LOW = 11;
const int REG_ACCX_HIGH = 12;
const int REG_ACCX_LOW = 13;
const int REG_ACCY_HIGH = 14;
const int REG_ACCY_LOW = 15;
const int REG_ACCZ_HIGH = 16;
const int REG_ACCZ_LOW = 17;
const int REG_GYRX_HIGH = 18;
const int REG_GYRX_LOW = 19;
const int REG_GYRY_HIGH = 20;
const int REG_GYRY_LOW = 21;
const int REG_GYRZ_HIGH = 22;
const int REG_GYRZ_LOW = 23;
const int REG_TEMP_HIGH = 24;
const int REG_TEMP_LOW = 25;
const int REG_PITCH_NK = 26;
const int REG_ROLL_NK = 27;
const int REG_CMD = 0;

int16_t Devantech_CMPS11::magX()
{
  return (int16_t)regReadWord(REG_MAGX_HIGH);
}

int16_t Devantech_CMPS11::magY()
{
  return (int16_t)regReadWord(REG_MAGY_HIGH);
}

int16_t Devantech_CMPS11::magZ()
{
  return (int16_t)regReadWord(REG_MAGZ_HIGH);
}

int16_t Devantech_CMPS11::accX()
{
  return (int16_t)regReadWord(REG_ACCX_HIGH);
}

int16_t Devantech_CMPS11::accY()
{
  return (int16_t)regReadWord(REG_ACCY_HIGH);
}

int16_t Devantech_CMPS11::accZ()
{
  return (int16_t)regReadWord(REG_ACCZ_HIGH);
}

int16_t Devantech_CMPS11::gyrX()
{
  return (int16_t)regReadWord(REG_GYRX_HIGH);
}

int16_t Devantech_CMPS11::gyrY()
{
  return (int16_t)regReadWord(REG_GYRY_HIGH);
}

int16_t Devantech_CMPS11::gyrZ()
{
  return (int16_t)regReadWord(REG_GYRZ_HIGH);
}

int8_t Devantech_CMPS11::pitchNK()
{
  return (int8_t)(regReadByte(REG_PITCH_NK));
}
int8_t Devantech_CMPS11::rollNK()
{
  return (int8_t)(regReadByte(REG_ROLL_NK));
}
int16_t Devantech_CMPS11::temp()
{
    return (int16_t)(regReadWord(REG_TEMP_HIGH));
}


Devantech_Compass::CompassStatus Devantech_CMPS11::doCalibration(CompassPoint cp)
{
  if( regWriteByteFrame(REG_CMD,0xF0,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xF5,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xF7,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_READY_COMMIT;
}

Devantech_Compass::CompassStatus Devantech_CMPS11::doCalibration3D()
{
  if( regWriteByteFrame(REG_CMD,0xF0,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xF5,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xF6,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_READY_COMMIT;
}

Devantech_Compass::CompassStatus Devantech_CMPS11::commitCalibration()
{
  if( regWriteByteFrame(REG_CMD,0xF8,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassStatus Devantech_CMPS11::resetCalibration()
{
  if( regWriteByteFrame(REG_CMD,0x20,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0x2A,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0x60,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassStatus Devantech_CMPS11::configureDeviceId(uint8_t newDeviceId)
{
  if( regWriteByteFrame(REG_CMD,0xA0,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xAA,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,0xA5,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  if( regWriteByteFrame(REG_CMD,newDeviceId << 1,100) != Devantech_Compass::CS_COMMS_OK) return CS_COMMS_ERROR;
  this->deviceId = newDeviceId;
  return CS_ALL_COMPLETE;
}

Devantech_Compass::CompassCaps Devantech_CMPS11::getCaps()
{
  return CompassCaps(
    CC_CALIBRATE |
    CC_FACTORY_RESET |
    CC_CALIBRATE_3D |
    CC_PITCH_AND_ROLL |
    CC_MAG_XYZ |
    CC_ACC_XYZ |
    CC_GYRO_XYZ |
    CC_TEMP |
    CC_PITCH_AND_ROLL_NK |
    CC_CONFIG_DEVICE_ID);
}
