const int Sensor1Pin = A0; // Sensor output voltage

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600);
  pinMode(Sensor1Pin, INPUT);
}

void loop() 
{
  // Read in the ADC and convert it to a voltage:
  int proximityADC = analogRead(Sensor1Pin);
  Serial.println(proximityADC);
  delay(100);
}
