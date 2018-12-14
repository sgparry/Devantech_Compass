/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

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

#include "Devantech_TCCompass.h"

const uint8_t REG_PITCH = 4;
const uint8_t REG_ROLL = 5;

int8_t Devantech_TCCompass::pitch()
{
  return (int8_t)(regReadByte(REG_PITCH));
}

int8_t Devantech_TCCompass::roll()
{
  return (int8_t)(regReadByte(REG_ROLL));
}
