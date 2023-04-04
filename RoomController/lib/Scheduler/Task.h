#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task
{
public:
    Task();
    virtual void init();
    virtual void run();
    virtual String toString();
    
};

#endif
