#ifndef __ROLLERSHUTTER__
#define __ROLLERSHUTTER__

#include <Servo.h>
#include <Arduino.h>

class RollerShutter: public Servo
{
public:
    RollerShutter(int pin);
    void setAngle(int angle);
    int getAngle();

private:
    int _pin;
    int _angle;
};

#endif