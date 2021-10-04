const int Sensor1Pin = A0; // Sensor output voltage

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
