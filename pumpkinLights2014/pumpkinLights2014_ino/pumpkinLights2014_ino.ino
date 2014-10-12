
// Program to control flashing lights on a breadboard inside a pumpkin.
// Light colors are random.
// Lights will flicker at 40 Hz when motion is detected.
// Motion detector is a PIR sensor (Radio Shack)
typedef struct lightState
{
  int inputPin;                   // pin for the motion sensor to control the lights
  int outputPin;                   // pin to turn the lights on and off 
  boolean state;                   // State used to set the lights
  unsigned long previousMillis;    // stores previous millisec of stimulus on time
};

const unsigned long OnTime = 25;         // set your pulsewidth ON time here in ms for the Light stimulations (THIS should rarely change unless you are testing various pulsewidths)
const unsigned long OffTime = 25;        // set your pulsewidth OFF time here in ms for the Light stimulations
// pin information

const int GreenLED = 4;      //pin for a Green LED light (can choose any color you want)

const int MotionSensor = 7;   //pin to read the motion sensor

const int BlueLED = 12;     // pin for blue LED

const int RedLED = 11;  // pin for red LED

// Variables list:


lightState Green = {MotionSensor, GreenLED, LOW, 0};  // light information
lightState Blue = {MotionSensor, BlueLED, LOW, 0};
lightState Red = {MotionSensor, RedLED, LOW, 0};
//Initialization: set all inputs as INPUT, outputs as OUTPUT and set the initial value of outputs
void setup() {

 pinMode(Green.inputPin, INPUT);
 pinMode(Green.outputPin, OUTPUT);
 digitalWrite(Green.outputPin, LOW);

 pinMode(Blue.inputPin, INPUT);
 pinMode(Blue.outputPin, OUTPUT);
 digitalWrite(Blue.outputPin, LOW);
 
 pinMode(Red.inputPin, INPUT);
 pinMode(Red.outputPin, OUTPUT);
 digitalWrite(Red.outputPin, LOW);
 
}

struct lightState UpdateLight(struct lightState curLight){  
  unsigned long currentMillis = millis();
  if (digitalRead(curLight.inputPin) == HIGH){
     if (curLight.state == LOW) {
        if (currentMillis - curLight.previousMillis > OnTime) {
          // reset interval time zero
          curLight.previousMillis = currentMillis;   
          // toggle state: if ON will turn it OFF
          curLight.state = HIGH;
         }
      } else if (curLight.state == HIGH) {
        if (currentMillis - curLight.previousMillis > OffTime) {
          // reset interval time zero
          curLight.previousMillis = currentMillis;   
          // toggle state: if OFF will turn it ON
          curLight.state = LOW;
        }
      }
  }
   else if (digitalRead(curLight.inputPin) == LOW){
     curLight.state = LOW;
   }
  // update output with current state
  digitalWrite(curLight.outputPin, curLight.state);
  
  // return the laser information to the caller of this function
  return curLight;
}   

//Main loop. Evrything in here runs every frame
void loop() {
  
  // update the laser stimulus
  Green = UpdateLight(Green);
  Blue = UpdateLight(Blue);
  Red = UpdateLight(Red);
  // update the light stimulus if motion detected
}

    
    
  
