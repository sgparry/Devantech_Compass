/***********************************************************************************
 * Copyright (c) 2018 EduMake Limited and Stephen Parry (sgparry@mainscreen.com)
 * See file LICENSE for further details
 * MIT license, this line and all text above must be included in any redistribution
 ***********************************************************************************/

#ifndef Devantech_Compass_H
#define Devantech_Compass_H

#include <inttypes.h>

/*
 * Author S. G. Parry
 * 
 * Base class for all compass models.
 * 
 */

class Devantech_Compass
{
protected:
  uint8_t commsError = 0;
public:
  enum CompassPoint
  {
    CP_NORTH,
    CP_EAST,
    CP_SOUTH,
    CP_WEST,
    CP_DEFAULT
  };

  enum CompassStatus
  {
    CS_ALL_COMPLETE,    // The compass is fully calibrated / reset
    CS_STEP_COMPLETE,   // The compass point is calibrated
    CS_READY_COMMIT,    // The compass calibration is ready / needs to be committed.
    CS_NOT_NEEDED,      // Commit called on a compass that does not support it or thta has not been calibrated.
    CS_UNKNOWN_ERROR,   // Something unexpected went wrong.
    CS_SEQUENCE_ERROR,  // Attempt to return to a compass point on firmware that does not support it
    CS_UNSUPPORTED,     // This operation is not supported on this firmware
    CS_SW_FW_MISMATCH,  // The software does not match the compass firmware.
    CS_CALIBRATING,     // The compass calibration is ongoing, not ready to be committed.
    CS_COMMS_ERROR,     // An error occurred communicating with the compass.
    CS_COMMS_OK,        // Function completed comms OK.
  };

  enum CompassCaps
  {
    CC_CALIBRATE = 0x1,
    CC_CALIBRATE_REPORTS_WHEN_DONE = 0x2,
    CC_CALIBRATE_NEEDS_COMMIT = 0x4,
    CC_CALIBRATE_FOUR_STEP = 0x8,
    CC_RECALIBRATE_STEP = 0x10,
    CC_FACTORY_RESET = 0X20,
    CC_CALIBRATE_ABORT = 0X40,
    CC_CALIBRATE_3D = 0x80,
    CC_PITCH_AND_ROLL = 0x100,
    CC_MAG_XYZ = 0x200,
    CC_ACC_XYZ = 0x400,
    CC_GYRO_XYZ = 0x800,
    CC_TEMP = 0x1000,
    CC_PITCH_AND_ROLL_NK = 0x2000,
    CC_SET_SCAN_PERIOD = 0x4000,
    CC_CONFIG_DEVICE_ID = 0x8000
  };

  uint8_t getCommsError()
  {
    return commsError;
  }
    
  static const uint8_t DEFAULT_ADDRESS = 0x60;

  Devantech_Compass(uint8_t deviceId = DEFAULT_ADDRESS);

  uint8_t version();
  uint8_t bearingByte();
  float bearingDegrees() { return float(bearingTenthDegrees()) / 10.0; } 
  int16_t bearingTenthDegrees();
  float turnRate();

  virtual CompassStatus doCalibration3D()
  {
    return CS_UNSUPPORTED;
  }
  
  virtual CompassCaps getCaps() = 0;
  virtual CompassStatus doCalibration(CompassPoint cp = CP_DEFAULT) = 0;
  virtual CompassStatus commitCalibration()
  {
    return CS_NOT_NEEDED;
  }
  
  virtual CompassStatus getCalibrationStatus()
  {
    return CS_UNSUPPORTED;
  }
  
  virtual CompassStatus resetCalibration()
  {
    return CS_UNSUPPORTED;
  }
  
  virtual CompassStatus configureDeviceId(uint8_t newDeviceId)
  {
    return CS_UNSUPPORTED;
  }

protected:
  
  /** I2C device id */
  uint8_t deviceId;
  unsigned long read;
  unsigned long lastRead;
  int16_t bearing;
  int16_t lastBearing;

  uint8_t regReadByte(uint8_t regNo);
  uint16_t regReadWord(uint8_t regNo);
  
  Devantech_Compass::CompassStatus regWriteByteFrame(uint8_t reg, uint8_t val, int delayMs = 0);

public:
  void regReadN(uint8_t regNo, byte* buffer, uint8_t count);
};

#endif /* Devantech_Compass_H */
