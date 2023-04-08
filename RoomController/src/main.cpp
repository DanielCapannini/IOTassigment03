#include <Arduino.h>
#include <Scheduler.h>

#define LED_PIN 13

Scheduler scheduler;
Led* led;
RollerShutter* rollerShutter;
RoomTask* roomTask;

void setup() {
  led = new Led(LED_PIN);
  rollerShutter = new RollerShutter(12);
  scheduler = new Scheduler();
  roomTask = new RoomTask();
  pinMode(LED_PIN, OUTPUT);
  scheduler.init();
  scheduler.addTask(roomTask);
  Serial.begin(9600);
  while (!Serial)
  {} // wait for serial port to connect
}

void loop() {
  scheduler.run();
}