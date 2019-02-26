## Readme for final project

This is a general readme for Reid and Andrew's Alarm Project for WUSTL 222 IoT


Users can go to DOCS--user--README.md
Developers can go to DOCS--developer--README.md

You can find necessary files in Final Project-- and in hardware--


LIST SUBDIRECTORIES AND LIST MEANING CONTENT AND USE

  DOCS--
    developer--
      README.md: contains info for a developer to understand the setup of the program and how to modify the project

    proposal--
      diagrams--
        paperprototype.jpg: first paperprototypes
        sequence1.png: texting
        sequence2.png: pan camera (decided not to pursue)
        sequence3.png: talk (decided not to pursue)
        sequence4.png: change number (decided not to pursue)
        sequence5.png: turn ringer on
      proposal.md: our full proposal
    reports--
      diagrams--
        pi.jpg: The hardware setup for the raspberry pi
        setup.jpg: The hardware setup for the particle photon
      week1.md: Progress report
      week2.md: Progress report
      week3.md: N/A
    user--
      README.md: Readme for someone that wants to use our project
  Final Project--
    resources--
      particle--
        particle.min.js: required framework
    Security.html: Main html code for our project
    Security.js: Main js
    SecurityModel.js: Represents the project object
    SecurityStyle.css: Main css
  hardware--
    PiFiles-- bonus
      button.py: This code is used for sniffing the network for an amazon dash button
      pythoncamera.py: This code takes pictures when motion is detected
      test.py: this code is used to notify the particle. it was difficult because of sudo logging out from CLI
    src--
      hardware.ino: This is the code for the particle photon
    project.properties: just names the project file
    README.md: This file. Main Readme to start in
