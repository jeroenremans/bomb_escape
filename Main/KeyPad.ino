// 14;

const int button1Pin = 16;
const int button2Pin = 17;
const int button3Pin = 14;
const int button4Pin = 15; 
int button1LastSwitchState = 0;  
int button2LastSwitchState = 0;  
int button3LastSwitchState = 0;  
int button4LastSwitchState = 0;  
int button1SwitchState = 0;  
int button2SwitchState = 0;  
int button3SwitchState = 0;  
int button4SwitchState = 0;  

unsigned long button1LastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long button2LastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long button3LastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long button4LastDebounceTime = 0;  // the last time the output pin was toggled

void keypadSetup() {
  // Servo
  Serial.print("INIT keypad\n"); 
  pinMode(button1Pin, INPUT);    
  pinMode(button2Pin, INPUT); 
  pinMode(button3Pin, INPUT); 
  pinMode(button4Pin, INPUT);
}

void keypadLoop() {

  
  byte currentState = digitalRead(button1Pin);
  if (currentState != button1LastSwitchState) {
    button1LastDebounceTime = millis();
    button1LastSwitchState = currentState;
  }
  if ((millis() - button1LastDebounceTime) > buttonDebounceDelay) {
    if (currentState != button1SwitchState) {
       button1SwitchState = currentState;
       if (currentState == 1) {
        eventListener(EVENT_BUTTON_1);
      }
    }
  }  
  
  currentState = digitalRead(button2Pin);
  if (currentState != button2LastSwitchState) {
    button2LastDebounceTime = millis();
    button2LastSwitchState = currentState;
  }
  if ((millis() - button2LastDebounceTime) > buttonDebounceDelay) {
    if (currentState != button2SwitchState) {
       button2SwitchState = currentState;
       if (currentState == 1) {
        eventListener(EVENT_BUTTON_2);
      }
    }
  }

  currentState = digitalRead(button3Pin);
  if (currentState != button3LastSwitchState) {
    button3LastDebounceTime = millis();
    button3LastSwitchState = currentState;
  }
  if ((millis() - button3LastDebounceTime) > buttonDebounceDelay) {
    if (currentState != button3SwitchState) {
       button3SwitchState = currentState;
       if (currentState == 1) {
        eventListener(EVENT_BUTTON_3);
      }
    }
  }

  currentState = digitalRead(button4Pin);
  if (currentState != button4LastSwitchState) {
    button4LastDebounceTime = millis();
    button4LastSwitchState = currentState;
  }
  if ((millis() - button4LastDebounceTime) > buttonDebounceDelay) {
    if (currentState != button4SwitchState) {
       button4SwitchState = currentState;
       if (currentState == 1) {
        eventListener(EVENT_BUTTON_4);
      }
    }
  }

 
}
