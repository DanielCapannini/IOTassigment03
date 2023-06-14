#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "Task.h"
#include "SmartRoom.h"
#include "MsgService.h"

class SerialTask : public Task {
  
  public: 
    Msg* message;
    SerialTask(SmartRoom* room, MsgService* msg);
    SmartRoom* room;
    MsgService* msg;
    String content;    
    void init(int period);
    void run();

  protected: 
    void write(bool ledState, int servoOpening);
}; 

#endif