#include "Arduino.h"
#include "MsgService.h"
#include "ArduinoJson.h"

void MsgService::readSerial() {
   while(Serial.available()) {
    char ch = (char)Serial.read();
    if (ch == '\n') {
      this->currentMes = new Msg(this->content);
      this->messageAvailable = true;
    } else {
      this->content += ch;
    }
  }
}

void MsgService::init() {
    Serial.begin(9600);
    while (!Serial) {}
    this->content.reserve(256);
    this->content = "";
    this->currentMes = NULL;
    this->messageAvailable = false;
}

void MsgService::sendMsg(bool ledState, int servoOpening) {
    DynamicJsonDocument doc(200);
    doc["Light"] = ledState;
    doc["Servo"] = servoOpening;
    serializeJson(doc, Serial);
    Serial.println();
}

void MsgService::sendMsg(String mes) {
    Serial.println(mes);
}

bool MsgService::isMessageAvailable() {
    return this->messageAvailable == true;
};

Msg* MsgService::receiveMsg() {
    if (this->isMessageAvailable()) {
        Msg* mes = this->currentMes;
        this->messageAvailable = false;
        this->currentMes = NULL;
        content = "";
        return mes;
    } else {
        return NULL;
    }
};