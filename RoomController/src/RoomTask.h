#ifdef _ROOMTASK_
#define _ROOMTASK_

#include <Arduino.h>
#include "Task.h"
#include "Led.h"
#include "RollerShutter.h"

class RoomTask: public Task
{
public:
    RoomTask();
    void init();
    void run();
    String toString();

private:
    Led* led;
    RollerShutter* rollerShutter;
};

#endif