#include "SmartRoom.h"

SmartRoom::SmartRoom(ServoMotor* servoMotor, Led* led) : 
  servoMotor(servoMotor), led(led){}

void SmartRoom::setLedState(bool state)
{
  if(state)
  {
    led->switchOn();
  }
  else
  {
    led->switchOff();
  }
}

void SmartRoom::setServoOpen(int percent)
{
  servoMotor->open(percent);
}

bool SmartRoom::getLedState()
{
  return led->isOn();
}

int SmartRoom::getServoOpen(){
  return servoMotor->getOpeningPercentage();
}