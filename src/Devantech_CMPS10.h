/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_CMPS10_H
#define DEVANTECH_CMPS10_H

#include "Devantech_CMPS09.h"

class Devantech_CMPS10 :
public Devantech_CMPS09
{
public:
  Devantech_CMPS10(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_CMPS09(deviceId) {}
};

#endif /* DEVANTECH_CMPS10_H */
