#ifndef __MAINTASK__
#define __MAINTASK__

#include "Task.h"
#include "pir.h"
#include "led.h"
#include "photoresistor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>

class mainTask : public Task {
    public:
        mainTask(pir* p, Led* l, photoresistor* ph, PubSubClient* client, const char* topic);
        void init();
        void run();
        String toString();
    private:
        pir* p;
        Led* l;
        photoresistor* ph;
        PubSubClient* client;
        const char* topic;
};

#endif