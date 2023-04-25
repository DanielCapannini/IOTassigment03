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

def sendArduino():
    global lightStatus, windowStatus
    s.open()
    dt = {}
    dt["light"] = lightStatus
    dt["window"] = windowStatus
    dt=json.dumps(dt)
    s.write(dt.encode("ascii"))
    s.write(b'\n')
    s.flush
    s.close
    
def readArduino():
    global lightStatus, windowStatus
    dt = s.read_all()
    if(dt["light"] == 1):
        lightStatus = 1
    if(dt["window"] != windowStatus):
        windowStatus = dt["window"]
    print("serial arduino: " + dt.decode("utf-8"))

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("occupance", qos=1)

def on_message(client, userdata, msg):
    global lightStatus, windowStatus, url_bashboard
    message = msg.payload.decode("utf-8")
    print(message)
    a = json.loads(message)
    t = datetime.now().strftime("%H:%M:%S")
    if a["isMotion"] == 1 and lightStatus == 0:
        lightStatus = 1
        mes = {
            "type": "luce",
            "date":{
                "state": lightStatus,
                "time": t,
                },
            }
        request.post(url_bashboard, json=mes)
    if a["isMotion"] == 1 and datetime.now().hour >= 8 and windowStatus == 0:
        windowStatus=180
        mes = {
            "type": "finestra",
            "date":{
                "state": windowStatus,
                "time": t,
                },
            }
        request.post(url_bashboard, json=mes)
    if a["isMotion"] == 0 and windowStatus>0 and datetime.now().hour < 8 and datetime.now().hour >= 19:
        windowStatus=0
        mes = {
            "type": "finestra",
            "date":{
                "state": windowStatus,
                "time": t,
                },
            }
    if a["isMotion"] == 1 and lightStatus == 1:
        lightStatus = 0
        mes = {
            "type": "luce",
            "date":{
                "state": lightStatus,
                "time": t,
                },
            }
    sendArduino() 
        
lightStatus = 0
windowStatus = 0
s = serial.Serial("COM3", 9600, timeout=1)
s.close()
url_bashboard = "http://localhost/IOTssigment03/RoomDashboard/index.php"
espclient = paho.Client()
espclient.on_connect = on_connect
espclient.on_subscribe = on_subscribe
espclient.on_message = on_message
espclient.connect("broker.hivemq.com", 1883)
espclient.loop_start()

while True:
    bashborad = request.get(url_bashboard)
    data = bashborad.json()
    if(data["luce"] == 1):
        lightStatus = 1
    if(data["tapparelle"] != windowStatus):
        windowStatus = data["tapparelle"]
    readArduino()
    sendArduino()
    time.sleep(1)