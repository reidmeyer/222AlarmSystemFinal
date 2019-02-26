Alarm system readme for developer:


RASPBERRY PI PHOTO SENSOR HOOKUP

  hardware used:
    raspberry pi Model B
    wifi dongle or ethernet connection
    picamera (works with regular, but could modify project to work with the infrared)
    PIR motion SENSOR
    Amazon Dash Button
    Speaker with aux port

  Necessary Setup:
    Raspbery Pi
      Raspberry pi ran Sketch
      Plug in all of the components
      Use python 2.7 and 3.4
      Install apache server on port 80 to serve files at /var/www/html
      You will need many packages (might be missing a few here) such as pip, GPIO, Scapy, motion, picamera, MP4Box, OMXPlayer, ngrok
      Place pythoncamera.py in /var/www/ and run with python3 pythoncamera.py. This will place pictures and videos in /var/www/html when movement is detected.
      Place button.py in home/pi/. Change the code so the MAC ADDRESS is that of the amazon dash button you are using. Place the audio file, old-fashioned-door-bell-daniel_simon.mp3 in /home/pi/Doanloads. Run with sudo python button.py.
    Amazon Dash Button:
      Setup Dash button by holding down the button for 6 seconds until it starts blinking blue. Then connect to the amazon wifi created. then go to http://192.168.0.1/ and write down the mac address of your Amazon Dash button. Modify the button.py code to have your mac address.
      While the button is blinking blue, go to the amazon app on your phone, go to settings, your account, set up new dash button. Follow the steps, but at the end, when it asks you to choose a product to buy on button click, exit the app so you don't accidentally purchase things while using this project.
      Connect it to the same network as your raspberry pi.


    You can connect to your apache server in a few ways. The easiest way is on the same network as your pi. Go to http://PIIPADDRESS and your apache server should pop up. You should also input http://PIIPADDRESS in the html/js code where it directs to the photos page since this ip address can change depending on your network.
    Another option, if you want to view these photos off of your home network, is to push this local server to the web. I used ngrok. once installed, you can run ngrok but typing "./ngrok http 80" on the command line in the directory where your ngrok installation is. This will print out a unique web address so you can access your server from anywhere. If you use this method, again, change the url in the html/js to reflect the ./ngrok address. Ngrok is a free platform, and might not be reliable for professional use, but serves as a proof of concept.

    Notifying the Particle of a doorbell ring:
    run python test.py in the /home/pi directory. Had to do this in the most convoluted way. but its pretty interesting. This makes it so the particle is notified when the doorbell rings and an alert occurs


PHOTON ALARM SYSTEM
      Hardware Used:
        PIR Motion SENSOR
        Particle PHOTON
        Powerswitch Tail II
        piezo buzzer

      Necessary steps:
        the included pictures indicate wiring
        Flash the particle with the hardware ino file
        Plug the powerswitch into a light source to scare of intruders
        Change the code in SecurityModel.js to reflect your specific device_id and access_token for your photon
        Run the UI but opening Security.html in line with Security.js, SecurityModel.js, SecurityStyle.css, and resources/particle/particle.min.js

        The button closest to the edge serves as an arm/disarm button and the other button serves as a switch for the powerstrip. For an extra layer of security you  might want to remove the arm/disarm button and use the ui alone.

        To set up the texting feature, you must download IFTTT on your phone and create an account. Then create a trigger that way when your particle publishes an event named "cse222/text", it sends a text to you.

  Modifying code:
    If you want to modify the sound played on the doorbell, thats as simple as editing the button.py code to reflect a different mp3.
    It should be very possible to add new features or change this project to fit your needs. I recommend getting the current version up and running first.
    For most hardware features, such as changing the arming delay, or changing how long before a text is sent, you can edit the values in the ino file. If you wanted to, for example, make it so the buzzer turns off after a certain amount of time, instead of going forever, that might require a more precise modification to the code.
    You could replace the picamera with the infrared version and try to get it running well at night.
    or you could hook up a light that turns on before a picture is taken so it wouldn't need an infrared camera.
    You could create a fail safe so if the photon is unplugged it sets off some type of alarm.
    you could create some type of password protocols to disarm the device.
    Make sure to change the device ID to your photon's ID and the access token to your access token.
