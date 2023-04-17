import keyboard, serial, json, time
import paho.mqtt.client as paho
import requests as req
from datetime import datetime

def readArduino():
    dt = s.read_all()
    print("serial arduino: " + dt.decode("utf-8"))


def sendArduino(lightMes, windowMes):
    lightStatus = (1,0)[lightMes=="on"]
    s.open()
    dt = {}
    dt["light"] = lightStatus
    dt["window"] = windowMes
    dt=json.dumps(dt)
    s.write(dt.encode("ascii"))
    s.write(b'\n')
    s.flush
    s.close


def readEsp():
    


s = serial.Serial("COM3", 9600, timeout=1)