// 14-17

const int LED_1_PIN = 22; 
const int LED_2_PIN = 23; 
const int LED_3_PIN = 24; 
const int LED_4_PIN = 25; 


void uvLedsSetup() {
  // Servo
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
}

void uvLedsLoop() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);  
}

void demoLoopUvLeds() {
  if ((millis()/1000) % 2 == 0) {
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, HIGH);  
    digitalWrite(LED_3_PIN, HIGH);  
    digitalWrite(LED_4_PIN, HIGH);  
  } else {
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, LOW);  
    digitalWrite(LED_3_PIN, LOW);  
    digitalWrite(LED_4_PIN, LOW);  
  }
}

