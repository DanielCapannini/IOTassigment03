#include "pir.h"
#include "led.h"
#include "photoresistor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "mainTask.h"
#include "Scheduler.h"
#include <WiFi.h>

const char* ssid = "DIGOS";
const char* password = "Daniel12";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topic = "occupance";

pir* p = new pir(19);
Led* l = new Led(18);
photoresistor* ph = new photoresistor(32);
WiFiClient espClient;
PubSubClient client(espClient);
mainTask* t = new mainTask(p, l, ph, &client, topic);
Scheduler* s = new Scheduler();

void setup_wifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("non si connette");
        delay(500);
    }
}

void setup() {
  Serial.begin(115200);
  p->initialize();
  l->init();
  s->init();
  s->addTask(t);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = String("occupance-client-")+String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  s->run();
}