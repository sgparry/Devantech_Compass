/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS03_REV14_H
#define DEVANTECH_CMPS03_REV14_H

#include "Devantech_Compass.h"

class Devantech_CMPS03Rev14 :
public Devantech_Compass
{
protected:
  boolean calibrated[4] = {false,false,false,false};
public:
  Devantech_CMPS03Rev14(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_Compass(deviceId) {}
  virtual CompassCaps getCaps();
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT);
  virtual CompassStatus resetCalibration();
  virtual CompassStatus configureDeviceId(uint8_t newDeviceId);
};

#endif /* DEVANTECH_CMPS03_REV14_H */
