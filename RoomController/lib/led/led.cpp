#include "Led.h"

Led::Led(int pin) : state(OFF) {
  pin_=pin;
  pinMode(pin_, OUTPUT);
}

void Led::switchOn() {
  if (this->state != Led::ON) {
    this->state = Led::ON;
    digitalWrite(pin_, HIGH);
  }
}

void Led::switchOff() {
  if (this->state != Led::OFF) {
    this->state = Led::OFF;
    digitalWrite(pin_, LOW);
  }
}

bool Led::isOn() {
  return Led::state == ON;
}