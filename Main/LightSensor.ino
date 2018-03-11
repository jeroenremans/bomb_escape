int lightSensorPin = A0; // select the input pin for LDR
int lightSensorValue = 0; // variable to store the value coming from the sensor
boolean gameStarted = false;

void lightSensorSetup() {
  
  pinMode(buzzerPin, OUTPUT); // Digital Pin 8


 
}

void lightSensorLoop() {
  delay(500);
  lightSensorValue = analogRead(lightSensorPin); // read the value from the sensor
  Serial.println("\nLight value : ");
  Serial.println(lightSensorValue); //prints the values coming from the sensor on the screen
  if (lightSensorValue < 500) {
    gameStarted = true;
  }  
  delay(100);
}

boolean isGameStarted() {
  return gameStarted;
}

