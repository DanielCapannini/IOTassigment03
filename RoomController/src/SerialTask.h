#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "Task.h"
#include "SmartRoom.h"
#include "MsgService.h"

class SerialTask : public Task {
  
  public: 
    SmartRoom* room;
    MsgService* msg;
    String content; 
    Msg* message;

    SerialTask(SmartRoom* room, MsgService* msg);   

    
    void init(int period);
    void tick();

  protected: 
    void write(bool ledState, int servoOpening);
}; 

#endif