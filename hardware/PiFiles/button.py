#run with sudo python button.py
import subprocess
from scapy.all import *
MAC_ADDRESS = '44:65:0d:0d:80:73'

def detect_button(pkt):
    if pkt.haslayer(DHCP) and pkt[Ether].src == MAC_ADDRESS:
        print("Button Press Detected")

        subprocess.call(["touch", "trigger.txt"])
        subprocess.call(["omxplayer","-o","local","/home/pi/Downalods/old-fashioned-door-bell-daniel_simon.mp3"])

sniff(prn=detect_button, filter="(udp and (port 67 or 68))", store=0)
