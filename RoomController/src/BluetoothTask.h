#include "Task.h"
#include "SmartRoom.h"
#include "SoftwareSerial.h"
#include <Arduino.h>
#include "Scheduler.h"
#include "MsgService.h"

extern bool BTReceiving;

class  BluetoothTask: public Task {
  int rxPin;
  int txPin;
  SoftwareSerial* channel;
  SmartRoom* smartRoom;
  MsgService* msg;

  int dt;
  int ct;

public:
  BluetoothTask(int rxPin, int txPin, MsgService* msg, SmartRoom* smartRoom, int dt);  
  void init(int period);  
  void tick();
};
