
//items used to subscribe to particle stream
//var myParticleAccessToken = "a458155af299ccf60cb4e33fa0884903e35a74a5"
//var myDeviceId =            "260026000c47363339343638"
var topic =                 "cse222/alarmproject"

var myParticleAccessToken = "75f889214b6daa1a3bee0b88b51f7380f5983eea" // Reid

var myDeviceId =              "2e002d000447363333343435" // Reid


//receives information from stream and updates the state accordingly
function newSecurityEvent(objectContainingData) {
      console.log(objectContainingData.data);
      var data = JSON.parse(objectContainingData.data);

      securityModel.alarmStatus = data.armed;
      securityModel.stripStatus = data.stripstatus;
      securityModel.ringerStatus = data.piezostatus;
      securityModel.alarmLastWentOff = data.lastalarm;
      securityModel.textSent = data.text;
      securityModel.alarmLog = data.alarmLog;
      securityModel.doorbell = data.doorbell;

      console.log(securityModel.alarmStatus);
      console.log(securityModel.stripStatus);
      console.log(securityModel.ringerStatus);
      console.log(securityModel.alarmLastWentOff);
      console.log(securityModel.textSent);
      console.log(securityModel.alarmLog);
      console.log(securityModel.doorbell);

      securityModel.stateChange();
}


//A model representing out Security System

var securityModel = {


//state variables for simulated garage
  alarmStatus: false,
  stripStatus: false,
  alarmLastWentOff: "",
  ringerStatus: true,
  textSent: true,
  alarmLog: "",
  doorbell: false,

//function sets the alarm to the correct state when the set alarm button is clicked and sends to Particle
  setAlarm: function(aStatus){
    this.alarmStatus = aStatus

    var functionData = {
         deviceId: myDeviceId,
         name: "armfunction",
         argument: ""+this.alarmStatus,
         auth: myParticleAccessToken
    }
    console.log(this.alarmStatus)

    // Include functions to provide details about the process.
    function onSuccess(e) { console.log("setAlarm call success") }
    function onFailure(e) { console.log("setAlarm failed")
                           console.dir(e) }
    particle.callFunction(functionData).then(onSuccess,onFailure)

    securityModel.stateChange();
  },

//this function sets the correct state of the power strip when the corresponding button is clicked
  setStrip: function(sStatus){
    this.stripStatus = sStatus

    var functionData = {
         deviceId: myDeviceId,
         name: "stripmethod",
         argument: ""+this.stripStatus,
         auth: myParticleAccessToken
    }
    console.log(this.stripStatus)

    // Include functions to provide details about the process.
    function onSuccess(e) { console.log("setStrip call success") }
    function onFailure(e) { console.log("setStrip failed")
                           console.dir(e) }
    particle.callFunction(functionData).then(onSuccess,onFailure)

    securityModel.stateChange();
  },

//this function sets the correct state of the ringer to either on or off
  setRinger: function(rStatus){
    this.ringerStatus = rStatus

    var functionData = {
         deviceId: myDeviceId,
         name: "piezoswitch",
         argument: ""+this.ringerStatus,
         auth: myParticleAccessToken
    }
    console.log(this.ringerStatus)

    // Include functions to provide details about the process.
    function onSuccess(e) { console.log("setRinger call success") }
    function onFailure(e) { console.log("setRinger failed")
                           console.dir(e) }
    particle.callFunction(functionData).then(onSuccess,onFailure)

    securityModel.stateChange();
  },

//listens for changes in states
  setStateChangeListener: function(aListener) {
        this.stateChangeListener = aListener;

        var callingObject = this
    },

//stateChange is a utility function (helper function).
//Consolidate all your code to update listeners here and then just call it
  stateChange: function() {

        var callingObject = this

        if(callingObject.stateChangeListener) {
            var state = { alarmStatus:this.alarmStatus,
                          stripStatus:this.stripStatus,
                          alarmLastWentOff:this.alarmLastWentOff,
                          ringerStatus:this.ringerStatus,
                          textSent:this.textSent,
                          alarmLog:this.alarmLog,
                          doorbell:this.doorbell
                        }

            setTimeout(function() {callingObject.stateChangeListener(state)}, 1000);
        }
    },

//New setup function to do initial setup and update with state of the Security Model
    setup: function() {

      particle = new Particle();

      function onSuccess(stream) {

        console.dir("getEventStream success")
        stream.on('event', newSecurityEvent)

        var functionData = {
             deviceId:myDeviceId,
             name: "publishState",
             argument: "",
             auth: myParticleAccessToken
        }

        function onSuccess(e) { console.log("publishState success")}
        function onFailure(e) { console.log("publishState call failed")
                    console.dir(e)}

        particle.callFunction(functionData).then(onSuccess,onFailure)

      }

      function onFailure(e) { console.log("getEventStream call failed")
                              console.dir(e) }

      // Subscribe to the stream
      particle.getEventStream( { name: topic, auth: myParticleAccessToken, deviceId: 'mine' }).then(onSuccess, onFailure)
      securityModel.stateChange();
    }
}
