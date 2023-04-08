#ifdef _ROOMTASK_
#define _ROOMTASK_

#include <Arduino.h>
#include "Task.h"
#include "Led.h"
#include "RollerShutter.h"
#include "MsgService.h"

class RoomTask : public Task {
    public:
        RoomTask(Led* l, RollerShutter* r);
        void tick();
        void init(int period);
        void updateRoom(Msg* msg);
    private:
        Led* led;
        rBlinds* rBlind;
        DynamicJsonDocument doc = DynamicJsonDocument(256);
};

#endif