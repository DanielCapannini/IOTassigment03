#include "RoomTask.h"
#include "MsgService.h"

SmartRoom::RoomTask(Led *l, RollerShutter *r)
{
    led = l;
    rBlind = r;
}

void RoomTask::init(int period)
{
    Task::init(period);
    MsgServiceBT.init();
    MsgService.init();
}

void RoomTask::tick()
{

    if (MsgServiceBT.isMsgAvailable())
    {
        Msg *msg = MsgServiceBT.receiveMsg();
        updateRoom(msg);
        delete msg;
    }
    if (MsgService.isMsgAvailable())
    {
        Msg *msg = MsgService.receiveMsg();
        updateRoom(msg);
        delete msg;
    }
    readSerialMessage(true, true);
}

void RoomTask::updateRoom(Msg *msg)
{
    String command = msg->getContent();
    DeserializationError error = deserializeJson(doc, command);
    if (error)
    {
        Serial.println(error.c_str());
        return;
    }
    if (doc.containsKey("light"))
    {
        digitalWrite(13, doc["light"] == 1 ? HIGH : LOW);
    }
    Serial.println(command);
}