#include <Arduino.h>
#include <Scheduler.h>

#define LED_PIN 13

Scheduler scheduler;
Led* led;
RollerShutter* rollerShutter;

void setup() {
  led = new Led(LED_PIN);
  rollerShutter = new RollerShutter(12);
  scheduler = new Scheduler();
  pinMode(LED_PIN, OUTPUT);
  
}

void loop() {
  scheduler.run();
}