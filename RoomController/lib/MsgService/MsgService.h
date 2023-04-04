#ifdef _MSGSERVICE_
#define _MSGSERVICE_

#include <Arduino.h>
#include "Msg.h"

class MsgService
{
public:
    MsgService();
    void sendMsg(bool ledState, int angle);
    Msg getMsg();
    String toString();
    void readSerial();
    bool isMsgAvailable();
    Msg* receveMsg();
    Msg* currentMsg;
    bool messageAvailable;

private:
    String _msg;
};

#endif