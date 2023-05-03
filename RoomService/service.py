# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 11:27:17 2023

@author: daniel
"""
import  json, serial, time
import paho.mqtt.client as paho
from datetime import datetime
import requests as request

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("occupance", qos=1)

def on_message(client, userdata, msg):
    global movimento, luminosita
    message = msg.payload.decode("utf-8")
    a = json.loads(message)
    movimento=a["isMotion"]
    luminosita=a["lightLevel"]
    
def control():
    global lightStatus, windowStatus, url_bashboard_post, movimento
    t = datetime.now().strftime("%H:%M:%S")
    if movimento == 1 and lightStatus == 0:
        lightStatus = 1
        mes = {
            "type": "luce",
            "date":{
                "state": lightStatus,
                "time": t,
                },
            }
        request.post(url_bashboard_post, json=mes)
    if movimento == 1 and datetime.now().hour >= 8 and windowStatus == 0:
        windowStatus=100
        mes = {
            "type": "finestra",
            "date":{
                "state": windowStatus,
                "time": t,
                },
            }
        request.post(url_bashboard_post, json=mes)
    if movimento == 0 and windowStatus>0 and datetime.now().hour < 8 and datetime.now().hour >= 19:
        windowStatus=0
        mes = {
            "type": "finestra",
            "date":{
                "state": windowStatus,
                "time": t,
                },
            }
        request.post(url_bashboard_post, json=mes)
    if movimento == 1 and lightStatus == 1:
        lightStatus = 0
        mes = {
            "type": "luce",
            "date":{
                "state": lightStatus,
                "time": t,
                },
            }
        request.post(url_bashboard_post, json=mes)
    
  
luminosita = 0
movimento = 0
lightStatus = 0
windowStatus = 0
url_bashboard_get = "http://localhost/IOTssigment03/RoomDashboard/room-dashboard-window.php"
url_bashboard_post = "http://localhost/IOTssigment03/RoomDashboard/room-dashboard-history.php"
s = serial.Serial("COM6", 9600)
espclient = paho.Client()
espclient.on_connect = on_connect
espclient.on_subscribe = on_subscribe
espclient.on_message = on_message
espclient.connect("broker.hivemq.com", 1883)
espclient.loop_start()


while True:
    dt = s.read_all()
    line = s.readline().decode('utf-8')
    print(line)
    json_obj = json.loads(line)
    lightStatus = json_obj['Light']
    windowStatus = json_obj['Servo']
    print(luminosita , " " ,  movimento, " ", lightStatus, " ", windowStatus)
    bashborad = request.get(url_bashboard_get)
    data = bashborad.json()
    if(data["luce"] == 1):
        lightStatus = 1
    if(data["tapparelle"] != windowStatus):
        windowStatus = data["tapparelle"]
    control()
    dt = {}
    dt["light"] = lightStatus
    dt["window"] = windowStatus
    dt=json.dumps(dt)
    s.write(dt.encode())
    s.write(b'\n')
    time.sleep(0.2)
    control()