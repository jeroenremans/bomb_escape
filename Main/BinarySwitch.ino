const int binSwitchPin = 31; 
int binSwitchState = 0;  
int oldBinSwitchState = 0;  

void binSwitchSetup() {
  Serial.print("INIT  binary switch on port 31\n"); 
  pinMode(binSwitchPin, INPUT);   
}

void binSwitchLoop() {
  
 
 
}

boolean isBinSwitchValid() {
   binSwitchState = digitalRead(binSwitchPin);
  Serial.print(binSwitchState); 
   if (binSwitchState == 1) {
     return true;
   }
   return false;
}

