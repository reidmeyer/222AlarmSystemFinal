/*
* Project hardware
* Description:
* Author:
* Date:
*/

STARTUP(WiFi.selectAntenna(ANT_AUTO)); // continually switches at high speed between antennas
//variables
int piezo = D1;
bool piezostatus = true;
int inputPin = D0; // pir
int ledPin = D7;                 // choose the pin for the LED
int powerstrip = D6;
int armbutton = D2;
int powerstripbutton = D3;
bool startalarm = false;
bool stripstatus = false;
bool text = false;
bool doorbell = false;
String lastalarm = "Hasn't Gone Off";
String alarmLog = "No Logs Yet";


const String topic = "cse222/alarmproject";
const String texttopic = "cse222/text";



bool armed = false;

//for arm button debouncing
Timer repeat(20,loop2);
int buttonState = 0;
int lastButtonState = 0;
int legitclick = 0;
int reading = (digitalRead(armbutton)==0);
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers


//for arm button debouncing
Timer repeat3(20,loop3);
int buttonState3 = 0;
int lastButtonState3 = 0;
int legitclick3 = 0;
int reading3 = (digitalRead(powerstripbutton)==0);
unsigned long lastDebounceTime3 = 0;
const unsigned long debounceDelay3 = 100;    // the debounce time; increase if the output flickers

//timers
Timer armtimer(5000, armtimerfunction, true);
Timer ICEtimer(10000, ICEfunction, true);


bool currentlyarming = false;

//in case of emergency
void ICEfunction() {
  Serial.println("Call authorities");
  text = true;
  publishState("");

}

//arming shouldn't be instantaneous
void armtimerfunction()
{
  armed = true;
  Serial.println("ARMED");
  currentlyarming = false;
  startalarm=false;
  digitalWrite(powerstrip, LOW);
  stripstatus= false;
  publishState("");

}




// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  repeat.start();
  repeat3.start();

  pinMode( piezo, OUTPUT );
  pinMode( ledPin, OUTPUT );
  pinMode(inputPin, INPUT);      // set sensor as input
  pinMode(powerstrip, OUTPUT);
  pinMode(armbutton, INPUT_PULLUP);
  pinMode(powerstripbutton, INPUT_PULLUP);

  Particle.function("armfunction", armfunction);
  Particle.function("stripmethod", stripmethod);
  Particle.function("piezoswitch", piezoswitch);

  Particle.function("bell", bell);



  Particle.variable("armed", armed);
  Particle.variable("stripstatus", stripstatus);
  Particle.variable("piezostatus", piezostatus);


  Particle.function("publishState", publishState);

//central time zone
  Time.zone(-6);

  publishState("");

}

//this is so the raspberry pi can call this function and notify the UI
int bell(String blank)
{
  doorbell = true;
  publishState("");
  return 0;
}


//arm function
int armfunction(String blank)
{
  Serial.println("button pressed");
  //armed = !armed;
  if (armed)
  {
    armed = false;
    Serial.println("NOTARMED");
    ICEtimer.stop();
    publishState("");

  }
  else if (currentlyarming == true)
  {
    armtimer.stop();
    armed = false;
    currentlyarming = false;
    Serial.println("NOTARMED");
    publishState("");

  }
  else
  {
    Serial.println("ARMING: 10 seconds");
    currentlyarming = true;
    armtimer.start();
  }
  return 0;
}

//for the power strip
int stripmethod(String blank2)
{
  Serial.println("powerstrip button clicked");
  if (stripstatus==true)
  {
    digitalWrite(powerstrip, LOW);
    stripstatus = false;
    publishState("");

  }
  else
  {
    digitalWrite(powerstrip, HIGH);
    stripstatus = true;
    publishState("");


  }

  legitclick3 = 0;
  return 0;
}


//for the buzzer
int piezoswitch(String blank2)
{
  Serial.println("piezo switch clicked");
  if (piezostatus==true)
  {
    piezostatus = false;
    publishState("");

  }
  else
  {
    piezostatus = true;
    publishState("");
  }

  return 0;
}


//arm debounce logic
void loop2()
{
  // read the state of the switch into a local variable:
  reading = digitalRead(armbutton)==0;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == HIGH)
      {
        legitclick=1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}



//debounce logic
void loop3()
{
  // read the state of the switch into a local variable:
  reading3 = (digitalRead(powerstripbutton)==0);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading3 != lastButtonState3)
  {
    // reset the debouncing timer
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime3) > debounceDelay3)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading3 != buttonState3)
    {
      buttonState3 = reading3;
      if (buttonState3 == HIGH)
      {
        legitclick3=1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState3 = reading3;
}

bool printonce = false;

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  if (digitalRead(inputPin) == HIGH)
  {
    if (printonce == false)
    {
      Serial.println("picking up motion");
      printonce = true;
    }
  //  digitalWrite(ledPin, HIGH);
  }
  else
  {
  //  digitalWrite(ledPin, LOW);
  }

  if (armed)
  {
    //  digitalWrite(ledPin, HIGH);         // turn LED ON if high
  }
  else
  {
    noTone(piezo);
    //digitalWrite(ledPin, LOW);
  }





  if (armed && (digitalRead(inputPin) == HIGH))
  {  // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);         // turn LED ON if high
    //tone(piezo, 500);
    //Serial.println("BUZZ");
    //  digitalWrite(ledPin, HIGH);         // turn LED ON if high

    if (startalarm==false)
    {
      Serial.println("BUZZ");

      Serial.print(Time.timeStr());
      lastalarm = Time.timeStr();

      if(alarmLog == "No Logs Yet"){
        alarmLog = lastalarm + "; ";
      } else {
        alarmLog = lastalarm + "; " + alarmLog;
      }

      if(piezostatus)
      {
        tone(piezo, 100);
      }
      startalarm = true;
      digitalWrite(powerstrip, HIGH);
      stripstatus = true;
      //start timer to call authorities
      ICEtimer.start();
      publishState("");

    }

  }
  else
  {
    //digitalWrite(ledPin, LOW);         // turn LED ON if high
  }

  //if powerstrip button clicked;
  if ((buttonState3 == 1) && (legitclick3 == 1))
  {
    Serial.println("powerstrip button clicked");
    if (stripstatus==true)
    {
      digitalWrite(powerstrip, LOW);
      stripstatus = false;
      publishState("");

    }
    else
    {
      digitalWrite(powerstrip, HIGH);
      stripstatus = true;
      publishState("");


    }

    legitclick3 = 0;


  }



  //if arm button clicked
  if ((buttonState == 1) && (legitclick == 1))
  {
    Serial.println("button pressed");
    //armed = !armed;
    if (armed)
    {
      armed = false;
      Serial.println("NOTARMED");
      ICEtimer.stop();
      publishState("");

    }
    else if (currentlyarming == true)
    {
      armtimer.stop();
      armed = false;
      currentlyarming = false;
      Serial.println("NOTARMED");
      publishState("");

    }
    else
    {
      Serial.println("ARMING: 10 seconds");
      currentlyarming = true;
      armtimer.start();
    }

    legitclick=0;
  }


}


// Publishes updated states
int publishState(String s)
{

  String data = "{";
  if(armed)
  {
    data += "\"armed\":true";
  } else {
    data += "\"armed\":false";
  }

  data += ", ";

  if(stripstatus)
  {
    data += "\"stripstatus\":true";
  }
  else
  {
    data += "\"stripstatus\":false";
  }

  data += ", ";

  if(piezostatus)
  {
    data += "\"piezostatus\":true";
  }
  else
  {
    data += "\"piezostatus\":false";
  }

  data += ", ";

  if(text)
  {
    data += "\"text\":true";
  }
  else
  {
    data += "\"text\":false";
  }

  data += ", ";

  if(doorbell)
  {
    data += "\"doorbell\":true";
  }
  else
  {
    data += "\"doorbell\":false";
  }

  data += ", ";
  data += "\"lastalarm\":\"";
  data += String(lastalarm);
  data += "\", ";

  data += "\"alarmLog\":\"";
  data += String(alarmLog);

  data += "\"}";

  Particle.publish(topic, data, 1, PRIVATE);
  doorbell = false;


  if(text)
  {
    Particle.publish(texttopic, data, 1, PRIVATE);
    text = false;
  }

  return 0;
}
