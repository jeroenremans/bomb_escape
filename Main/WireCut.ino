


const int WIRE_CUT_1_PIN = 42; 
const int WIRE_CUT_2_PIN = 43; 
const int WIRE_CUT_3_PIN = 44; 
const int WIRE_CUT_4_PIN = 45; 
const int WIRE_CUT_5_PIN = 46; 
const int WIRE_CUT_6_PIN = 47; 

void wireCutSetup() {


  pinMode(WIRE_CUT_1_PIN, INPUT);
  pinMode(WIRE_CUT_2_PIN, INPUT);
  pinMode(WIRE_CUT_3_PIN, INPUT);
  pinMode(WIRE_CUT_4_PIN, INPUT);
  pinMode(WIRE_CUT_5_PIN, INPUT);
  pinMode(WIRE_CUT_6_PIN, INPUT);
 
  
}

void wireCutLoop() {
  // colors : 2 (empty)
  // colors : 3 RED
  // colors : 4 WHITE
  // colors : 5 BLUE 1 BLACK
  // colors : 6 YELLOW
  // colors : 7 not connected
   byte currentState1 = digitalRead(WIRE_CUT_1_PIN);
   byte currentState2 = digitalRead(WIRE_CUT_2_PIN);
   byte currentState3 = digitalRead(WIRE_CUT_3_PIN);
   byte currentState4 = digitalRead(WIRE_CUT_4_PIN);
   byte currentState5 = digitalRead(WIRE_CUT_5_PIN);
   byte currentState6 = digitalRead(WIRE_CUT_6_PIN);
   //Serial.print(currentState1);  
   //Serial.print(currentState2);
   //Serial.print(currentState3);
   //Serial.print(currentState4);
   //Serial.print(currentState5);
   //Serial.print(currentState6);
   //Serial.print("\n");

   if (currentState4 == 0 || currentState6 == 0) {
      eventListener(EVENT_BOMD_EXPLODED);
   }
   if (currentState3 == 1 && currentState5 == 0) {
      eventListener(EVENT_BOMD_EXPLODED);
   }
   if (currentState3 == 0 && currentState5 == 0) {
      eventListener(EVENT_BOMD_DISARMED);
   }
 
}
