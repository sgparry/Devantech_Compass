/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS01_REV07_H
#define DEVANTECH_CMPS01_REV07_H

#include "Devantech_Compass.h"

class Devantech_CMPS01Rev07 :
public Devantech_Compass
{
protected:
  boolean calibrated[4] = {false,false,false,false};
public:
  Devantech_CMPS01Rev07(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_Compass(deviceId) {}
  virtual CompassCaps getCaps();
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT);
};

#endif /* DEVANTECH_CMPS01_REV07_H */
