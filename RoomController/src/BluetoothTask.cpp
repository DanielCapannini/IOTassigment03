#include "BluetoothTask.h"
#include "Scheduler.h"
#include "Task.h"
#include <ArduinoJson.h>
#include "MsgService.h"


BluetoothTask::BluetoothTask(int rxPin, int txPin, MsgService* msg, SmartRoom* smartRoom, int dt) {
  this->txPin = txPin;
  this->rxPin = rxPin;
  this->dt = dt;
  this->ct = dt;
  this->msg = msg;
  this->smartRoom = smartRoom;
}
  
void BluetoothTask::init(int period){
  Task::init(period);
  channel = new SoftwareSerial(txPin, rxPin);
  channel->begin(9600);
}
  
void BluetoothTask::run(){
  if(channel->available()){
    String mes = "";
    this->ct = this->dt;
    receiving = true;
    char msgChar = (char)channel->read();
    while(msgChar != '\n'){
      mes.concat(msgChar);
      msgChar = (char)channel->read();
    }
    StaticJsonDocument<64> doc;
    deserializeJson(doc, mes);
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
      receiving = false;
    }
    else{
      this->ct--;
    }
  }
  msg->sendMsg(smartRoom->getLedState(), smartRoom->getServoOpen());
}