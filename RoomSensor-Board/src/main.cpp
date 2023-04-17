#include "pir.h"
#include "led.h"
#include "photoresistor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "espWIFI.h"
#include "mainTask.h"
#include "Scheduler.h"

const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topic = "occupance";

pir* p = new pir(19);
Led* l = new Led(18);
photoresistor* ph = new photoresistor(32);
espWIFI espClient;
PubSubClient client(espClient);
mainTask* t = new mainTask(p, l, ph, &client, topic);
Scheduler* s = new Scheduler();

void setup() {
  Serial.begin(115200);
  p->initialize();
  l->init();
  s->init();
  s->addTask(t);
  espWIFI::wifiConnect("", "");
  client.setServer(mqtt_server, 1883);
}

void loop() {
  // put your main code here, to run repeatedly:
}