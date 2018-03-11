int SEGMENT_LEDB_SER_Pin = 8; //pin 14 on the 75HC595
int SEGMENT_LED_RCLK_Pin = 9; //pin 12 on the 75HC595
int SEGMENT_LED_SRCLK_Pin = 10; //pin 11 on the 75HC595

//How many of the shift registers – change this
#define number_of_74hc595s 2

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8
boolean registers[numOfRegisterPins];


byte _currentSegments;
byte increaseEverySeconds = 14;

uint32_t segmentsStartTime = 0;  // remember the millis() value in animations


void ledSegmentInit() {

  segmentsStartTime = millis();
  pinMode(SEGMENT_LEDB_SER_Pin, OUTPUT);
  pinMode(SEGMENT_LED_RCLK_Pin, OUTPUT);
  pinMode(SEGMENT_LED_SRCLK_Pin, OUTPUT);
  
  //reset all register pins
  clearRegisters();
  writeRegisters();
}

void setSegmentSpeedInSeconds(int seconds) {
  increaseEverySeconds = seconds;
}

void clearPressureSegments() {
  segmentsStartTime = millis();
}


void startIncrease(byte speed) {
  
}

void showSegments(byte index) {
  if (index != _currentSegments) {
    for(int i = 0; i < index; i++){
      registers[i] = HIGH;
    }
    
    for(int i = index; i <= 10; i++){
      registers[i] = LOW;
    }
  
    writeRegisters();
    _currentSegments = index;
  } 
}

void ledSegmentLoop() {
  int seconds = (millis() - segmentsStartTime)/1000;
  int segmentCount = (seconds / increaseEverySeconds) % 11;
  showSegments((seconds / increaseEverySeconds) % 11);
  if (segmentCount == 10) {
    eventListener(EVENT_PRESSURE_OVERFLOW);
  }
}

void testingLedSegments() {
  for (byte j = 0; j <= 2 ; j ++) {
    for (byte i = 0; i <=10 ; i++) {
      showSegments(i);
      delay(100);
    }
    for (byte i = 10; i > 0 ; i--) {
      showSegments(i);
      delay(100);
    }  
  }
}


void demoLoopLedSegments() {
  int mll = (millis())/1000;
  seconds = mll % 60;
  showSegments(seconds % 11);
}

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >= 0; i--){
    registers[i] = LOW;
  }
}

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){
  digitalWrite(SEGMENT_LED_RCLK_Pin, LOW);
  for(int i = numOfRegisterPins - 1; i >= 0; i--){
    digitalWrite(SEGMENT_LED_SRCLK_Pin, LOW);
    int val = registers[i];
    digitalWrite(SEGMENT_LEDB_SER_Pin, val);
    digitalWrite(SEGMENT_LED_SRCLK_Pin, HIGH);
  }
  digitalWrite(SEGMENT_LED_RCLK_Pin, HIGH);
}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}




