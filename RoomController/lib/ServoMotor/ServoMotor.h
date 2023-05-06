#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "Arduino.h"
#include <Servo.h>


class ServoMotor : public Servo {
  
  int angle = 0;

  public:
    ServoMotor(int pin); 
    void open(int percentage);
    int getAngle();
    int getOpeningPercentage();
    
  private:
    int pin_;
};

#endif