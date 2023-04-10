#include "pir.h"

pir::pir(int pin)
{
    _pin = pin;
    _state = false;
}

void pir::initialize()
{
    pinMode(_pin, INPUT);
}

bool pir::isMotion()
{
    _state = digitalRead(_pin);
    return _state;
}

bool pir::getState()
{
    return _state;
}