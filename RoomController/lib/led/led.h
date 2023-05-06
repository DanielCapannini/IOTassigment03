#ifndef __LED__
#define __LED__

#include <Arduino.h>

class Led {
  enum {ON, OFF} state;
  
  public:
    Led(int pin); 
    void switchOn();
    void switchOff();
    bool isOn();

  private:
    int pin_;
};

#endif