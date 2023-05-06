# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 11:27:17 2023

@author: daniel
"""
import  json, serial, time
import paho.mqtt.client as paho
from datetime import datetime
import requests as request2

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
    if movimento == 1 and lightStatus == 0:
        lightStatus = 1
        mes = {
            "type": "lights",
            "state": lightStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        request2.post(url_bashboard_post, json=mes)
    if movimento == 1 and datetime.now().hour >= 8 and int(windowStatus) == 0:
        windowStatus=100
        mes = {
            "type": "window",
            "state": windowStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        request2.post(url_bashboard_post, json=mes)
    if movimento == 0 and int(windowStatus)>0 and (datetime.now().hour < 8 or datetime.now().hour >= 19):
        windowStatus=0
        mes = {
            "type": "window",
            "state": windowStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        request2.post(url_bashboard_post, json=mes)
    if movimento == 0 and lightStatus == 1:
        lightStatus = 0
        mes = {
            "type": "lights",
            "state": lightStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        request2.post(url_bashboard_post, json=mes)
    
  
luminosita = 0
movimento = 0
lightStatus = 0
windowStatus = 0
url_bashboard_get = "http://localhost/IOTassigment03/RoomDashboard/room-dashboard-window.php"
url_bashboard_post = "http://localhost/IOTassigment03/RoomDashboard/room-post.php"
s = serial.Serial("COM5", 9600)
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
    if json_obj['Light'] != lightStatus:
        lightStatus = bool(json_obj['Light'])
        mes = {
            "type": "lights",
            "state": lightStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        response = request2.post(url_bashboard_post, data=mes)
        if response.status_code == 200:
            content = response.content
            print(content)
    elif int(json_obj['Servo']) != int(windowStatus):
        windowStatus = int(json_obj['Servo'])
        mes = {
            "type": "window",
            "state": windowStatus,
            "start": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        response = request2.post(url_bashboard_post, data=mes)
        if response.status_code == 200:
            content = response.content
            print(content)
    else:
        bashborad = request2.get(url_bashboard_get)
        if bashborad.status_code == 200:
            data = bashborad.json()
            print("get:  ", data)
            if data["lights"] == "False":
                lightStatus = False
            else:
                lightStatus = True
        windowStatus=int(data["window"])
        control()
    dt = {}
    dt["light"] = lightStatus
    dt["window"] = windowStatus
    dt=json.dumps(dt)
    s.write(dt.encode())
    s.write(b'\n')
    time.sleep(0.2)