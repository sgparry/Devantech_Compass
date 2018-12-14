/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS09_H
#define DEVANTECH_CMPS09_H

#include "Devantech_TCCompass.h"

class Devantech_CMPS09 :
public Devantech_TCCompass
{
protected:
  CompassPoint nextCP = CP_NORTH;
public:
  Devantech_CMPS09(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_TCCompass(deviceId) {}
  int16_t magX();
  int16_t magY();
  int16_t magZ();
  int16_t accX();
  int16_t accY();
  int16_t accZ();

  virtual CompassCaps getCaps();
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT);
  virtual CompassStatus resetCalibration();
  virtual CompassStatus configureDeviceId(uint8_t newDeviceId);
};


#endif /* DEVANTECH_CMPS09_H */
