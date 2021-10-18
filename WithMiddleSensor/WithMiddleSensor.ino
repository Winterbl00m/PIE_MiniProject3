
#include <Adafruit_MotorShield.h>

const int leftSensorPin = A2; // 880-940: use 910 as cutoff
const int middleSensorPin = A1; // 830-900: use 870 as cutoff
const int rightSensorPin = A0; // 790-870: use 840 as cutoff

const int cutoff_left = 920;
const int cutoff_mid = 850;
const int cutoff_right = 800;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int left_offset = 6;
int default_speed = 50;
//int sensorThreshold = 970;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  stop_driving();
}

// checkSensor() returns true sensor if on the tape
bool checkSensor(int sensorPin, int cutoff_value){
  if (analogRead(sensorPin) > cutoff_value) {
    return true;
  }
  return false;
}


void turn(bool leftDir){
  int sensorPin = rightSensorPin;
  if (leftDir) {
    sensorPin = leftSensorPin;
  }
  if (leftDir) {
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(default_speed);
  } else {
    leftMotor->setSpeed(default_speed-left_offset);
    rightMotor->setSpeed(0);
  }

  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

//void turn_slightly(bool leftDir){
//  int sensorPin = rightSensorPin;
//  if (leftDir) {
//    sensorPin = leftSensorPin;
//  }
//
//  if (leftDir) {
//    leftMotor->setSpeed((default_speed-left_offset) / 2);
//    rightMotor->setSpeed(default_speed);
//  } else {
//    leftMotor->setSpeed(default_speed-left_offset);
//    rightMotor->setSpeed(default_speed / 2);
//  }
//
//  leftMotor->run(FORWARD);
//  rightMotor->run(FORWARD);
//  
//  while(checkSensor(leftSensorPin, cutoff_left) or !checkSensor(middleSensorPin, cutoff_right)) {
//    delay(1);
//  }
//}

void forward(){
    leftMotor->setSpeed(default_speed-left_offset);
    rightMotor->setSpeed(default_speed);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void stop_driving(){
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void search() {
  turn(true);
}

void loop() {
  Serial.print("Left: ");
  Serial.print(checkSensor(leftSensorPin, cutoff_left));
  Serial.print(" | Mid: ");
  Serial.print(checkSensor(middleSensorPin, cutoff_mid));
  Serial.print(" | Right: ");
  Serial.println(checkSensor(rightSensorPin, cutoff_right));
  Serial.print("Left: ");
  Serial.print(analogRead(leftSensorPin));
  Serial.print(" | Mid: ");
  Serial.print(analogRead(middleSensorPin));
  Serial.print(" | Right: ");
  Serial.println(analogRead(rightSensorPin));
  
  if (checkSensor(middleSensorPin, cutoff_mid)) { // and (!checkSensor(leftSensorPin, cutoff_left) or !checkSensor(rightSensorPin, cutoff_right))){
    forward();
//  } else if (checkSensor(leftSensorPin, cutoff_left) and checkSensor(middleSensorPin, cutoff_mid)){
//    turn(true); // turn left
//  } else if (checkSensor(middleSensorPin, cutoff_mid) and checkSensor(rightSensorPin, cutoff_right)){
//    turn(false); // turn right
    Serial.println("forward");
  } else if (checkSensor(leftSensorPin, cutoff_left) and !checkSensor(rightSensorPin, cutoff_right)){
    turn(true); // turn left
    Serial.println("turn left");
  } else if (!checkSensor(leftSensorPin, cutoff_left) and checkSensor(rightSensorPin, cutoff_right)){
    turn(false); // turn right
    Serial.println("turn right");
  } else if (!checkSensor(middleSensorPin, cutoff_mid) and !checkSensor(leftSensorPin, cutoff_left) and !checkSensor(rightSensorPin, cutoff_right)){
    search(); 
    Serial.println("search");
  } 
}
