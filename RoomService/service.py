import keyboard, serial, json, time
import paho.mqtt.client as paho
import requests as req
from datetime import datetime

def readArduino():
    global lightStatus, windowStatus
    dt = s.read_all()
    if(dt["light"] == 1):
        lightStatus = 1
    if(dt["window"] != windowStatus):
        windowStatus = dt["window"]
    print("serial arduino: " + dt.decode("utf-8"))


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

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("occupance", qos=1)

def on_message(client, userdata, msg):
    global lightStatus, windowStatus, url_bashboard
    message = msg.payload.decode("utf-8")
    t = datetime.now()
    

lightStatus = 0
windowStatus = 0
s = serial.Serial("COM3", 9600, timeout=1)
s.close()
url_bashboard = "http://localhost/IOTssigment03/RoomDashboard/index.php"
espclient = paho.Client()
espclient.on_connect = on_connect
espclient.on_subscribe = on_subscribe
espclient.on_message = on_message

#loop

while True:
    bashborad = req.get(url_bashboard)
    data = bashborad.json()
    if(data["light"] == 1):
        lightStatus = 1
    if(data["window"] != windowStatus):
        windowStatus = data["window"]
    readArduino()
    sendArduino()
    time.sleep(1)
    

