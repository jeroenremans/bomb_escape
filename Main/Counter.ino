/* TM1637_4_Digit_Display_Basics.ino
The purpose of this sketch is to provide the basic
structure for using the TM1637 based 4-Digit Displays
like the Grove 4 digit display or other equivalents
available through the likes of www.dx.com. 

This makes use of the TM1637Display library developed by avishorp.
https://github.com/avishorp/TM1637

This has been developed to run on any Arduino.

Pin assignments are:
CLK - D9
DIO - D8
5V or 3.3V supply to Display
GND to Display

The operation is very simple.  The sketch initialises the display
and then steps through the loop incrementing the value of a
variable which is then displayed on the 4-Digit display.
Essentially it is the most basic function you would want from
such a display.  If you want more sophisticated functionality
then use the example that ships with the library.

*/

#include <TM1637Display.h>

const int CLK = 2; //Set the CLK pin connection to the display
const int DIO = 3; //Set the DIO pin connection to the display


int NumStep = 0;  //Variable to interate

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

//int totalSecondsInGame = 2100;
int totalSecondsInGame = 3600;
unsigned long clockTimerStart; // time when the clock started
unsigned long clockTimerPenalty; // time when the clock started
int timerSecondsLeft = 0; // Seconds that are left after the clock stopped
boolean timerStopped = false; // Indicates that the clock is stopped and the game is ended.
byte hours, minutes, seconds;


unsigned long clockTimerLastPenaltyStart = 0; // time when the last penalty was trigged
unsigned long clockTimerLastPenaltyStop = 0; // time when the last penalty was trigged
unsigned long penaltyMilliscondsSeconds = 0; // seconds that will be deducted
unsigned long currentPenaltyMillisconds = 0; // seconds that will be deducted

int stepSpeed = 25;
void setPenaltySeconds(int seconds) {
  clockTimerLastPenaltyStart = millis();
  penaltyMilliscondsSeconds = seconds * 1000L;
  stepSpeed = seconds / 3;
}


void executePenalty() {
  if (clockTimerLastPenaltyStart > 0) {
    currentPenaltyMillisconds = (millis() - clockTimerLastPenaltyStart) * stepSpeed;
    if (currentPenaltyMillisconds >= penaltyMilliscondsSeconds) {
        clockTimerPenalty += currentPenaltyMillisconds;
        clockTimerLastPenaltyStart = 0;
        currentPenaltyMillisconds = 0;
        penaltyMilliscondsSeconds = 0;
    } 
  }
}

void counterSetup() {
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
  display.showNumberDec(0); //Display the Variable value;
}

void resetClockStartTime() {
  clockTimerStart = millis();
}

void showRecordTime() {
  int mll = totalSecondsInGame - getClockSecondsLeft();
  seconds = mll % 60;
  minutes = (mll / 60) % 60;
  hours = (3600 /(60 * 60)) % 24;
    display.showNumberDec(seconds); //Display the Variable value;
  
}

void startUpCounter() {
  for (int i = 0; i <= totalSecondsInGame; i += 12) {
      display.showNumberDec(formatClock(i)); //Display the Variable value;
      delay(20);
  }
}

int getClockSecondsLeft() {
    executePenalty();
    if (timerStopped) {
      return timerSecondsLeft;  
    } else {
      int secondsLeft = totalSecondsInGame - ((millis() - clockTimerStart + clockTimerPenalty + currentPenaltyMillisconds) /1000);
      return secondsLeft;
    }
}

void printTimeLeftClock() {
  int secondsLeft = getClockSecondsLeft();
  if (secondsLeft <= 0 ) {
    secondsLeft = 0;
  }
  seconds = secondsLeft % 60;
  minutes = (secondsLeft / 60) % 60;
  hours = (3600 /(60 * 60)) % 24;
  display.showNumberDec(formatClock(secondsLeft), true); //Display the Variable value;

  if (secondsLeft <= 0 ) {
    eventListener(EVENT_OUT_OF_TIME);
  }
}

int formatClock(int seconds) {
  return seconds % 60 + ((seconds / 60) % 60) * 100;
}

