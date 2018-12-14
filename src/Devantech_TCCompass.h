/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef DEVANTECH_TCCOMPASS_H
#define DEVANTECH_TCCOMPASS_H

/*
 * Author S. G. Parry
 * 
 * Base class for all tilt compensated models,
 * i.e. CMPS09,10,11
 */

#include "Devantech_Compass.h"

class Devantech_TCCompass :
public Devantech_Compass
{
public:
  Devantech_TCCompass(uint8_t deviceId = Devantech_Compass::DEFAULT_ADDRESS) : Devantech_Compass(deviceId) {}
  int8_t pitch();
  int8_t roll();
  virtual int16_t magX() { return 0x7FFF; }
  virtual int16_t magY() { return 0x7FFF; }
  virtual int16_t magZ() { return 0x7FFF; }
  virtual int16_t accX() { return 0x7FFF; }
  virtual int16_t accY() { return 0x7FFF; }
  virtual int16_t accZ() { return 0x7FFF; }
  virtual int16_t gyrX() { return 0x7FFF; }
  virtual int16_t gyrY() { return 0x7FFF; }
  virtual int16_t gyrZ() { return 0x7FFF; }
  virtual int8_t pitchNK() { return 0x7F; }
  virtual int8_t rollNK() { return 0x7F; }
  virtual int16_t temp() { return 0x7FFF; }
};

#endif /* DEVANTECH_TCCOMPASS_H */
