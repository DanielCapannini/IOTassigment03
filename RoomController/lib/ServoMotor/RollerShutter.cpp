#include "RollerShutter.h"

RollerShutter::RollerShutter(int pin)
{
    _pin = pin;
    _angle = 0;
}

void RollerShutter::setAngle(int angle)
{
    _angle = angle;
    write(angle);
}

int RollerShutter::getAngle()
{
    return _angle;
}