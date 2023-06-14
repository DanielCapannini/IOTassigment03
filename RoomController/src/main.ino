#include "Scheduler.h"
#include "ServoMotor.h"
#include "Led.h"
#include "SmartRoom.h"
#include "BluetoothTask.h"
#include "SerialTask.h"
#include "MsgService.h"

bool BTReceiving;

Scheduler scheduler;

void setup(){

  MsgService* msg = new MsgService();
  msg->init();
  ServoMotor* servo = new ServoMotor(10);
  Led* led = new Led(11);
  led->init();
  SmartRoom* smartRoom = new SmartRoom(servo, led);
  SerialTask* serialTask = new SerialTask(smartRoom, msg);
  serialTask->init(150);
  BluetoothTask* bluetoothtask = new BluetoothTask(2, 3, msg, smartRoom, 10);
  bluetoothtask->init(150);
  scheduler.init(100);
  scheduler.addTask(bluetoothtask);
  scheduler.addTask(serialTask);
}

void loop(){
  scheduler.run();
}