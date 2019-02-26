HTML Update
- The html is done except ids and classes will probably change as the design changed. Some parts of the HTML might be removed based on if we are able to implement the hardware. Streaming video may or may not be possible, however, a possible change would be to send photos at certain intervals or when the motion sensor goes off. The push to speak button also may not be implemented. The radio can be implemented however we are not sure how send the frequency from the particle to the raspberry pi.

CSS Update
- The colors and basic styling are done. We decided to go with a basic blue and white color scheme in order to not take away from the information being displayed. The styling of the image hasn't been done yet because we want to wait til we decide to send photos or videos or just scrap the idea.

JS Update
- JS has not been started yet. We are ready to begin coding the JS and hopefully start hooking things up through the cloud by the next update.

Hardware Update
- Have a button, piezo buzzer, and PIR motion sensor hooked up.
- Hooked up a camera to the raspberry pi, and made it so I can ssh in and run it headless.
- got powerswitch tail 2 working

.ino Update
- Have a simple starter ino file which has a button to arm/de-arm the alarm. If armed, the alarm (pizo button) will go off if there is motion detected.

Cloud Update
- Have a particle function to arm the device

Raspberry Pi Update
- Can ssh into the pi
- Hooked the Pi up to the particle console. It has GPIO functions built in
- Bought a pi Camera and can use the raspivid library to control it.
- NC Streaming
- Working on figuring out a way to get photos and videos to the site over the internet. Possibly with my AWS instance or

IFTTT Update
- IFTTT capabilities have not been implemented yet will be done in a future update.
- texting function tested, so can create an emergency contact protocol for the alarm system.

Problems and concerns
- Don't think we will be able to stream video to the site; when I was testing it, there was a substantial delay.
- Haven't successfully communicated between the photon and pi. Need to be able to send a signal to the pi to do something, like use the radio or the camera etc.
- Probably won't use the pan camera mode, since a servo motor might not work well with the pi camera, which is on a wire strip, unlike a typical usb camera that would be easy to turn.
- Need to figure out how to send photo/video to the online website.

Priorities for the next week
- Getting the JS started
- Narrowing everything down


Photo

![alt text](diagrams/setup.jpg)
- Current hardware setup with arming button, piezo buzzer, and PIR motion sensor
