#place file inside var/www and run with python3 pythoncamera.py
import time
import datetime
import RPi.GPIO as GPIO
import picamera
import urllib
import sys
import os
import urllib.request
url = "http://www.google.com/"
request = urllib.request.Request(url)
response = urllib.request.urlopen(request)

GPIO.setmode(GPIO.BOARD)

pir = 7

GPIO.setup(pir, GPIO.IN)
camera = picamera.PiCamera()
while True:
    if GPIO.input(pir):
        a = datetime.datetime.now()
        a = str(a)
        a = a[0:19]
        alert = ("Alarm at "+ str(a))
        print(alert)
        pic = ("html/")+ (a) + (".jpg")
        vid = ("html/")+ (a) + (".h264")
        pic = pic.replace(" ", "_")
        vid = vid.replace(" ", "_")
        pic = pic.replace(":", "-")
        vid = vid.replace(":", "-")
        camera.resolution = (1024, 768)
        camera.capture(pic)
        time.sleep(2)
        camera.resolution = (640, 480)
        camera.start_recording(vid)
        camera.wait_recording(10)
        camera.stop_recording()
        vidmp4 = vid[:-4]
        vidmp4 = vidmp4 + "mp4"
        os.system("MP4Box -fps 30 -add " + vid + " " + vidmp4)
        os.system("rm " + vid)
