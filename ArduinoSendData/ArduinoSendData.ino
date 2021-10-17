
const int left = A2; // 880-940: use 920 as cutoff
const int mid = A1; // 830-900: use 880 as cutoff
const int right = A0; // 790-870: use 850 as cutoff

const int cutoff_left = 920;
const int cutoff_mid = 880;
const int cutoff_right = 850;

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode(mid, INPUT);
  pinMode(right, INPUT);
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
  Serial.print("left: ");
  Serial.println(analogRead(left));
  Serial.print("middle: ");
  Serial.println(analogRead(mid));
  Serial.print("right: ");
  Serial.println(analogRead(right));
  Serial.println("");
  delay(1000);
}
