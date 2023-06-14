
#include "Scheduler.h"
#include "SmartRoom.h"
#include "MsgService.h"
#include "Task.h"
#include "ArduinoJson.h"
#include "SerialTask.h"
#include <Arduino.h>

SerialTask::SerialTask(SmartRoom* smartRoom, MsgService* msg) {
  this->room = smartRoom;
  this->msg = msg;
} 

void SerialTask::run() {
  this->msg->readSerial();
  Msg* mes = this->mes->receiveMsg();
  if (mes) {
    String content = mes->getContent();
    StaticJsonDocument<64> doc;
    deserializeJson(doc, content);
    this->room->setLedState(doc["light"]);
    this->room->setServoOpen(doc["window"]);
 }
  delete mes;
}

void SerialTask::init(int period) {
  Task::init(period);
}

void SerialTask::write(bool ledState, int servoOpening) {
  this->msg->sendMsg(ledState, servoOpening);
}
