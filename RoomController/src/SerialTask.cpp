#include "SerialTask.h"
#include <Arduino.h>
#include "Scheduler.h"
#include "SmartRoom.h"
#include "MsgService.h"
#include "Task.h"
#include "ArduinoJson.h"

SerialTask::SerialTask(SmartRoom* smartRoom, MsgService* msg) {
  this->room = smartRoom;
  this->msg = msg;
} 

void SerialTask::init(int period) {
  Task::init(period);
}

void SerialTask::write(bool ledState, int servoOpening) {
  this->msg->sendMsg(ledState, servoOpening);
}


void SerialTask::tick() {
  this->msg->readSerial();
  Msg* msg = this->msg->receiveMsg();
  if (msg) {
    String content = msg->getContent();
    StaticJsonDocument<64> doc;
    deserializeJson(doc, content);
    this->room->setLedState(doc["light"]);
    this->room->setServoOpen(doc["window"]);
 }
  delete msg;
}