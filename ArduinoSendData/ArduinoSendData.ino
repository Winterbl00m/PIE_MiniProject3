const int Sensor1Pin = A0; // Sensor output voltage

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600);
  pinMode(Sensor1Pin, INPUT);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
}

void loop() 
{
  // Read in the ADC and convert it to a voltage:
  int proximityADC = analogRead(Sensor1Pin);
  Serial.println(proximityADC);
  delay(100);
}
