#ifndef __ROOM__
#define __ROOM__

#include "ServoMotor.h"
#include "Led.h"

class SmartRoom 
{
  ServoMotor* servoMotor;
  Led* led;

public:
  SmartRoom(ServoMotor* servoMotor, Led* led);
  void setServoOpen(int percent);
  int getServoOpen();
  void setLedState(bool state);
  bool getLedState();
};
#endif