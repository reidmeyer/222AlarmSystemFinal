import subprocess
import os

while True:
    exists = os.path.isfile('/home/pi/trigger.txt')

    if exists:
        print("caught")
        os.system("sudo rm trigger.txt")
        subprocess.call(["/home/pi/.npm-global/bin/particle", "call", "2e002d000447363333343435", "bell", "true"])
