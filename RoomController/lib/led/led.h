#ifndef __LED__
#define __LED__

#include <Arduino.h>

class Led
{
public:
    Led(int pin);
    void init();
    void switchOn();
    void switchOff();
    bool isOn();
    String toString();

private:
    int _pin;
    bool _isOn;
};

#endif