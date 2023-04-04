#include "Arduino.h"
#include "MsgService.h"
#include "Msg.h"
#include "arduinojson.h"

MsgService::MsgService()
{
    Serial.begin(9600);
    while(!Serial){} // wait for serial to connect
    _msg.reserve(256);
    messageAvailable = false;
    currentMsg = NULL;
}

void MsgService::sendMsg(bool ledState, int angle)
{
    DynamicJsonDocument root(256);
    root["ledState"] = ledState;
    root["angle"] = angle;
    serializeJson(root, Serial);
    Serial.println();
}

void MsgService::readSerial()
{
    while(Serial.available())
    {
        char inChar = (char)Serial.read();
        if(inChar == '\n')
        {
            this->currentMsg = new Msg(_msg);
            messageAvailable = true;
        }else{
            _msg += inChar;
        }
    }
}

bool MsgService::isMsgAvailable()
{
    return messageAvailable;
}

Msg* MsgService::receveMsg()
{
    if(messageAvailable)
    {
        messageAvailable = false;
        Msg* msg = currentMsg;
        currentMsg = NULL;
        _msg = "";
        return msg;
    }else{
        return NULL;
    }
}