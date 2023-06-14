#include "led.h"

Led::Led(int pin)
{
    _pin = pin;
    _isOn = false;
}

void Led::init()
{
    pinMode(_pin, OUTPUT);
    switchOff();
}

void Led::switchOn()
{
    digitalWrite(_pin, HIGH);
    _isOn = true;
}

void Led::switchOff()
{
    digitalWrite(_pin, LOW);
    _isOn = false;
}

bool Led::isOn()
{
    return _isOn;
}

String Led::toString()
{
    return String(_pin) + " " + String(_isOn);
}

// Path: RoomController\lib\led\led.h