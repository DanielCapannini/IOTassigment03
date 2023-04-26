#include "mainTask.h"

mainTask::mainTask(pir* p, Led* l, photoresistor* ph, PubSubClient* client, const char* topic) {
    this->p = p;
    this->l = l;
    this->ph = ph;
    this->client = client;
    this->topic = topic;
}

void mainTask::init() {
}

void mainTask::run() {
    StaticJsonDocument<200> doc;
    doc["lightLevel"] = analogRead(32);
    doc["isMotion"] = p->getState();
    serializeJson(doc, Serial);
    Serial.println();
    char buffer[256];
    serializeJson(doc, buffer);
    client->publish(this->topic, buffer);
    Serial.println(buffer);

    if(p->getState()){
        l->switchOn();
    } else {
        l->switchOff();
    }
}

String mainTask::toString() {
    return "mainTask";
}