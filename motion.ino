#define MOVEMENT_THRESHOLD 100

int inputPin = D2;     // input pin (for PIR sensor/movement)
int led = D7;       // LED Pin
int pirState = LOW;    // Assuming that there is no movement
int motionCounter = 0;           

int calibrateTime = 5000;      // waitinng for calibration

void setup() {
    pinMode(led, OUTPUT);
    pinMode(inputPin, INPUT);     
}
void loop() {
  
  // if the sensor is calibrated
  if (calibrated()) {
      
  // get the data from the sensor
    readTheSensor();
    
    // report it out, if the state has changed
    reportTheData();
    }
}
void readTheSensor() {
    motionCounter = digitalRead(inputPin);
}
bool calibrated() {
    return millis() - calibrateTime > 0;
}
void setLED(int state) {
    digitalWrite(led, state);
}
void reportTheData() {
    
    // the sensor reads high and motion is detected
    if (motionCounter == HIGH) {
        // motion 
        // Publishing an event to notify the owner
        if (pirState == LOW) {
          // turned on
          Particle.publish("motion", String(motionCounter), PRIVATE);
          // Update the current state
          pirState = HIGH;
          setLED(pirState);
          }
        } else {
        if (pirState == HIGH) {
          // turned off
          // Update on current state
          Particle.publish("motion", String(motionCounter), PRIVATE);
          pirState = LOW;
          setLED(pirState);
        }
    }
}