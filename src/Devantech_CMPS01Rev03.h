/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS01_REV03_H
#define DEVANTECH_CMPS01_REV03_H

#include "Devantech_Compass.h"

class Devantech_CMPS01Rev03 :
public Devantech_Compass
{
public:
  Devantech_CMPS01Rev03(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_Compass(deviceId) {}
  virtual CompassCaps getCaps();
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT);
  virtual CompassStatus commitCalibration();
  virtual CompassStatus getCalibrationStatus();
};

#endif /* DEVANTECH_CMPS01_REV03_H */
