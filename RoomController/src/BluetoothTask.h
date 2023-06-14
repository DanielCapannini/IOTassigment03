#include "Task.h"
#include "SmartRoom.h"
#include "Scheduler.h"
#include "MsgService.h"
#include "SoftwareSerial.h"
#include <Arduino.h>

extern bool receiving;

class  BluetoothTask: public Task {
  SmartRoom* smartRoom;
  MsgService* msg;
  SoftwareSerial* channel;
  int rxPin;
  int txPin;
  int dt;
  int ct;

public:
  BluetoothTask(int rxPin, int txPin, MsgService* msg, SmartRoom* smartRoom, int dt);  
  void init(int period);  
  void run();
};
