


unsigned long buttonDebounceDelay = 50;    // the debounce time; increase if the output flickers

byte const EVENT_PRESSURE_OVERFLOW = 0;
byte const EVENT_OUT_OF_TIME = 1;
byte const EVENT_BINARY_SWITCH = 5;
byte const EVENT_MAZE_DISARMED = 6;
byte const EVENT_BOMD_DISARMED = 7;
byte const EVENT_BOMD_EXPLODED = 8;
byte const EVENT_BUTTON_1 = 10;
byte const EVENT_BUTTON_2 = 20;
byte const EVENT_BUTTON_3 = 30;
byte const EVENT_BUTTON_4 = 40;
uint32_t prevTime = 0;  // remember the millis() value in animations
byte gamePhase = 0;
byte totalStrikeCount = 0;
byte strikeCount = 0;
boolean processRunning = false;

boolean binaryLockDisarmed = false;
boolean mazeDisarmed = false;
boolean bomdDisarmed = false;
boolean bombExploded = false;

void setup(){
  Serial.begin(9600); //sets serial port for communication
  delay(1000);
 
  lightSensorSetup();
  counterSetup();
  lcdSetup();
  mazeSetup();
  ledSegmentInit();
  //buzzerSetup();
  servoSetup();
  wireCutSetup();
  uvLedsSetup();
  binSwitchSetup();
  keypadSetup();
  //wirelessSetup();
  prevTime = millis();
}

void triggerPenalty() {
  processRunning = true;
  printPopUpMessage(10); // Show message 10 seconds
  buzzerAlarm();
  setPenaltySeconds(300);
  processRunning = false;
}

void clearPressure() {
  processRunning = true;
  clearPressureSegments();
  // Message pressure sucessfully released
  processRunning = false;
}


void eventListener(byte code) {
  if (EVENT_PRESSURE_OVERFLOW == code) {
    strikeCount += 1;
    printOverflowMessage();
    buzzerAlarm();
    setPenaltySeconds(60);
    clearPressureSegments();
    setSegmentSpeedInSeconds(10);
    
  } else if (EVENT_MAZE_DISARMED == code) {
    printMazeEscapedMessage();
    buzzerBeep();
    mazeDisarmed = true;
  } else if (EVENT_BUTTON_1 == code) {
    if (!binaryLockDisarmed) {
      if (isBinSwitchValid()) {
        binaryLockDisarmed = true;
        printBinaryLockSuccessMessage();
        buzzerBeep();
      } else {
        intrusionDetected();
        setPenaltySeconds(300);
        buzzerAlarm();
      }
    
    }
    
  } else if (EVENT_BOMD_DISARMED == code) {
    if (!bomdDisarmed && !bombExploded) {
      gamePhase = 5;
      printBombDisarmed();
      playPiratesOfTheCaribbean();
      bomdDisarmed = true; 
    }
  } else if (EVENT_BOMD_EXPLODED == code ||  EVENT_OUT_OF_TIME == code) {
    if (!bomdDisarmed && !bombExploded) {
      gamePhase = 5;
      printBombExploded();
      starWarsDeadSong();
      bombExploded = true;
    }
  } else if (EVENT_BUTTON_2 == code) {
    
        intrusionDetected();
        buzzerAlarm();
        setPenaltySeconds(60);
  } else if (EVENT_BUTTON_3 == code) {
    
        intrusionDetected();
        buzzerAlarm();
        setPenaltySeconds(120);
  } else if (EVENT_BUTTON_4 == code) {
    clearPressure();
    
    setSegmentSpeedInSeconds(11);
  } else {

  }
}

void strikesLoop() {
  if (!processRunning && strikeCount >= 2) {
    totalStrikeCount += strikeCount;
    strikeCount = 0;
    triggerPenalty(); // 5 minutes will be deducted!!
  }
}

void loop(){
  //wirelessLoop();
  //
  //servoLoop();
  if (gamePhase != 5) {
  ledSegmentLoop();
    keypadLoop();
    wireCutLoop();
  }
  //buzzerLoop();
    
  if (gamePhase == 99) {
    demoLoopUvLeds();
    demoLoopLedSegments();
    
  } else {

    if (gamePhase == 0) {
      lightSensorLoop();
      if (isGameStarted()) {
        gamePhase  = 1; 
      }
    } else if (gamePhase == 1) { // SHOW STARTUP
       lcdShowBootScreen();
       gamePhase = 2; // Initialize
    } else if (gamePhase == 2) {
        resetClockStartTime();
        clearPressureSegments();
        gamePhase  = 3; 
        
    } else if (gamePhase == 3) { // GAME IS RUNNING
        mazeLoop();
        printTimeLeftClock();
        if (mazeDisarmed && binaryLockDisarmed) {
          demoLoopUvLeds();
        }
        wireCutLoop();   
    } else if (gamePhase == 4) { // SHOW END RESULT (STOPPED)
      printDisarmedMessage();
      playPiratesOfTheCaribbean();
      gamePhase = 5;
    } else if (gamePhase == 5) {

      
    }
  }
}
