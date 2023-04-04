#ifdef _ROOMTASK_
#define _ROOMTASK_

#include <Arduino.h>
#include "Task.h"
#include "Led.h"
#include "RollerShutter.h"
#include "MsgService.h"

class RoomTask: public Task
{
public:
    RoomTask(Led* led, RollerShutter* rollerShutter, MsgService* msgService);
    void init();
    void run();
    String toString();

private:
    Led* _led;
    RollerShutter* _rollerShutter;
    MsgService* _msgService;
};

#endif