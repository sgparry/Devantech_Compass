/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS03_REV15_H
#define DEVANTECH_CMPS03_REV15_H

#include "Devantech_CMPS03Rev14.h"

class Devantech_CMPS03Rev15 :
public Devantech_CMPS03Rev14
{
public:
  Devantech_CMPS03Rev15(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_CMPS03Rev14(deviceId) {}
  enum ScanPeriod
  {
    SP_300 = 0x10, SP_100 = 0x11, SP_33 = 0x12
  };
  virtual CompassCaps getCaps();
  CompassStatus setScanPeriod(ScanPeriod sp);
};

#endif /* DEVANTECH_CMPS03_REV15_H */
