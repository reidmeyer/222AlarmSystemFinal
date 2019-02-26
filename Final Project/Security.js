
//Variables representing elements on the "System Status" screen
var alarmStatus
var alarmLastWentOff
var alarmButton
var powerStripStatus
var powerStripButton

//Variables representing elements on the "Settings" screen
var ringerButton
var ringerStatus
var alarmLog

//Placeholder variables
var status
var status2
var status3
var x = 1

//functions to fade in and out the screens
function fadeOut() {
  var box1 = document.getElementById('HomeBox').hidden = true
  var box2 = document.getElementById('SettingsBox')
  box2.hidden = false
  box2.style.opacity = '1'
}

function fadeIn() {
  var box1 = document.getElementById('HomeBox').hidden = false
  var box2 = document.getElementById('SettingsBox').hidden = true
}

//change alarm state when button is clicked
function alarmButtonClicked(event) {
    if(securityModel.alarmStatus == false){
      alert("Arming. Will be armed in 10 seconds");
    }
    securityModel.setAlarm("")
}

//listens for state changes when button isnt clicked
function alarmStatusListen(){
    if(securityModel.alarmStatus == true){
        status = "Armed";
    } else if(securityModel.alarmStatus == false){
        status = "Not Armed";
    }

    alarmStatus.innerText = status;
}

//change power strip state when button is clicked
function powerStripButtonClicked(event) {
    securityModel.setStrip("")
}

//listens for state changes when button isnt clicked
function powerStripStatusListen(){
    if(securityModel.stripStatus == true){
        status2 = "Strip On";
    } else if(securityModel.stripStatus == false){
        status2 = "Strip Off";
    }

    powerStripStatus.innerText = status2;
}

//change power strip state when button is clicked
function ringerButtonClicked(event) {
    securityModel.setRinger("")
}

//listens for state changes when button isnt clicked
function ringerStatusListen(){
    if(securityModel.ringerStatus == true){
        status3 = "Ringer On";
    } else if(securityModel.ringerStatus == false){
        status3 = "Ringer Off";
    }

    ringerStatus.innerText = status3;
}

//listens for when the the last date the alarm went off changes
function dateStatusListen(){
    alarmLastWentOff.innerText = securityModel.alarmLastWentOff;
}

//sents alert when the alarm has been activated for 20secs
function textListen(){
    if(securityModel.textSent == true)
      alert("Warning! Alarm has been set off for 20sec. Please contact the Authorities");
}

//listens for when the log of dates the alarm went off is updated
function alarmLogListen(){
    alarmLog.innerText = securityModel.alarmLog;
}

//alert pops up when the doorbell is rung
function doorbellListen(){
  if(securityModel.doorbell == true)
    alert("Doorbell was clicked");
}

//hides page if parameter is true
function loadingPage(value) {
  document.getElementById('HomeBox').hidden = value;
}

//listens for certain things and updates with new state
function stateUpdate(newState) {
    if(x == 1){
      loadingPage(false)
      x=0;
    }

    console.log(newState)
    alarmStatusListen()
    powerStripStatusListen()
    ringerStatusListen()
    dateStatusListen()
    textListen()
    alarmLogListen()
    doorbellListen()
}

// On startup
document.addEventListener("DOMContentLoaded", function(event) {

    // Variables representing elements on the "Home" screen
    alarmStatus = document.getElementById("alarmStatus")
    alarmLastWentOff = document.getElementById("lastWentOffTime")
    alarmButton = document.getElementById("alarmButton")
    powerStripStatus = document.getElementById("powerStripStatus")
    powerStripButton = document.getElementById("powerStripButton")

    // Variables representing elements on the "Settings" screen
    ringerButton = document.getElementById("ringerButton")
    ringerStatus = document.getElementById("ringerStatus")
    alarmLog = document.getElementById("scrollingBox")

    // Event handlers
    document.getElementById("alarmButton").addEventListener("click", alarmButtonClicked)
    document.getElementById("powerStripButton").addEventListener("click", powerStripButtonClicked)
    document.getElementById("ringerButton").addEventListener("click", ringerButtonClicked)

    //page is hidden until UI receive state of garage
    if(x == 1){
      loadingPage(true)
    }

    //setup Security Model
    securityModel.setup()
    securityModel.setStateChangeListener(stateUpdate)

})
