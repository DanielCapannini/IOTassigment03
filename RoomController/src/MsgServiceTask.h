#ifdef _MSGSERVICETASK_
#define _MSGSERVICETASK_

#include <Arduino.h>
#include "Task.h"
#include "MsgService.h"

class MsgServiceTask: public Task
{
public:
    MsgServiceTask();
    void init();
    void run();
    String toString();

};

#endif