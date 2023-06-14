#include "BluetoothTask.h"
#include "Scheduler.h"
#include "Task.h"
#include <ArduinoJson.h>
#include "MsgService.h"


BluetoothTask::BluetoothTask(int rxPin, int txPin, MsgService* msg, SmartRoom* smartRoom, int dt) {
  this->txPin = txPin;
  this->rxPin = rxPin;
  this->msg = msg;
  this->smartRoom = smartRoom;
  this->dt = dt;
  this->ct = dt;
}
  
void BluetoothTask::init(int period){
  Task::init(period);
  channel = new SoftwareSerial(txPin, rxPin);
  channel->begin(9600);
}
  
void BluetoothTask::tick(){
  if(channel->available()){
    this->ct = this->dt;
    BTReceiving = true;
    char msgChar = (char)channel->read();
    String msg = "";
    while(msgChar != '\n'){
      msg.concat(msgChar);
      msgChar = (char)channel->read();
    }
    StaticJsonDocument<64> doc;
    deserializeJson(doc, msg);
    int servoOpening = doc["RollerBlinds"];
    if(doc["Lights"] ==  true) {
      smartRoom->setLedState(true);
    } else if (doc["Lights"] == false) {
      smartRoom->setLedState(false);
    }else if(servoOpening >= 0 && servoOpening <= 100){
      smartRoom->setServoOpen(servoOpening);
    }
  }
  else{
    if(this->ct == 0){
      BTReceiving = false;
    }
    else{
      this->ct--;
    }
  }
  msg->sendMsg(smartRoom->getLedState(), smartRoom->getServoOpen());
}