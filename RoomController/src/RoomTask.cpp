#include <Arduino.h>
#include "Task.h"
#include "Led.h"
#include "RollerShutter.h"
#include "MsgService.h"
#include "RoomTask.h"

RoomTask::RoomTask(Led* led, RollerShutter* rollerShutter, MsgService* msgService)
{
    _led = led;
    _rollerShutter = rollerShutter;
    _msgService = msgService;
}

RoomTask::init()
{
    _led->init();
}

RoomTask::run()
{
    _msgService->readSerial();
    Msg* msg = _msgService->reciveMsg();
    if(msg != NULL)
    {
        String msgstr = msg->getMsg();
        st
        _led->setState(msg->getLedState());
        _rollerShutter->setAngle(msg->getAngle());
        _msgService->sendMsg(_led->getState(), _rollerShutter->getAngle());
    }
}

RoomTask::toString()
{
    return "RoomTask";
}