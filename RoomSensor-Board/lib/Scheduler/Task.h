#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task
{
public:
    virtual void run();
    virtual String toString();

    bool checkPeriod()
    {
        if ((millis() - lastTick) >= period)
        {
            lastTick = millis();
            return true;
        }
        return false;
    }
    
    void setPeriod(long period)
    {
        this->period = period;
    }

    long getPeriod()
    {
        return this->period;
    }

    virtual void initPeriodic(long period)
    {
        this->period = period;
        this->lastTick = millis();
    }

private:
    unsigned long lastTick;
    unsigned long period;
};

#endif
