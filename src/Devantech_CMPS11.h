/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS11_H
#define DEVANTECH_CMPS11_H

#include "Devantech_TCCompass.h"

class Devantech_CMPS11 :
public Devantech_TCCompass
{
public:
  Devantech_CMPS11(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_TCCompass(deviceId) {}
  virtual CompassCaps getCaps();
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT);
  virtual CompassStatus commitCalibration();
  virtual CompassStatus resetCalibration();
  virtual CompassStatus configureDeviceId(uint8_t newDeviceId);
  virtual CompassStatus doCalibration3D();

  int16_t magX();
  int16_t magY();
  int16_t magZ();
  int16_t accX();
  int16_t accY();
  int16_t accZ();
  int16_t gyrX();
  int16_t gyrY();
  int16_t gyrZ();
  int8_t pitchNK();
  int8_t rollNK();
  int16_t temp();
};

#endif /* DEVANTECH_CMPS11_H */
