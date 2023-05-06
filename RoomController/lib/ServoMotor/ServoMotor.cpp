#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) : Servo(){
    pin_=pin;
    this->attach(pin_);
}

void ServoMotor::open(int percentage) {
  int newAngle = (180*percentage)/100;
  this->angle = newAngle;
  this->write(newAngle);
}

int ServoMotor::getAngle() {
  return this->angle;
}

int ServoMotor::getOpeningPercentage(){
  return (this->angle*100)/180;
  }