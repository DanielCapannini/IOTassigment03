#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "ArduinoJson.h"

class Msg {

private:
    String mes;

public:
    Msg(String content) {
        this->mes = content;
    }
    String getContent() {
        return this->mes;
    }
};

class MsgService {    
private:
    String content;
public:   
    void init();  
    void readSerial();
    void sendMsg(bool ledState, int servoOpening);
    void sendMsg(String mes);
    bool isMessageAvailable();
    Msg* receiveMsg();
    Msg* currentMes;
    bool messageAvailable;
};

#endif