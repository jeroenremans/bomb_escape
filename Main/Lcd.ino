#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> // F Malpartida's NewLiquidCrystal library
#define I2C_ADDR 0x27 // Define I2C Address for controller
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void lcdSetup() {
  lcd.begin (20,4); // initialize the lcd
  
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(LOW);
  lcd.noBacklight();
}

void showMessage() {
 // Reset the display
  lcd.clear();
  lcd.home();
  
  // Print on the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  

  lcd.print("Button pushed !!!");
  delay(500);
}


void showMessage2(char text[80]) {
 // Reset the display
  lcd.clear();
  lcd.home();
  
  // Print on the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  

  lcd.print(text);
  delay(500);
  
}

void printBombExploded() {
  resetDisplay();
  lcd.print("GAME OVER!");
  lcd.setCursor(0,1);
  lcd.print("YOU ARE DEAD.");
  lcd.setCursor(0,3);
  lcd.print("Looser!");
  
}

void printBombDisarmed() {
  resetDisplay();
  lcd.print("Bomb is deactivated!");
  lcd.setCursor(0,1);
  lcd.setCursor(0,3);
  lcd.print("Nice work!");
}

void printBinaryLockSuccessMessage() {
  resetDisplay();
  lcd.print("VALID binary code");
  lcd.setCursor(0,1);
  lcd.print("Fallback mechanishm");
  lcd.setCursor(0,2);
  lcd.print("deactivated!");
  lcd.setCursor(0,3);
  lcd.print("Nice work!");
}

void printDisarmedMessage() {
  resetDisplay();
  lcd.print("The bomb has been ");
  lcd.setCursor(0,1);
  lcd.print("disarmed! Congratulations");
  lcd.setCursor(0,3);
  lcd.print("Congratulations");
}

void printMazeEscapedMessage() {
  resetDisplay();
  lcd.print("MAZE lock disarmed");
  lcd.setCursor(0,1);
  lcd.print("Booby traps ");
  lcd.setCursor(0,2);
  lcd.print("deactivated");
  lcd.setCursor(0,3);
  lcd.print("Keep on going!");
}


void printOverflowMessage() {
  resetDisplay();
  lcd.print("Pressure too high");
  lcd.setCursor(0,1);
  lcd.print("Automatically ");
  lcd.setCursor(0,2);
  lcd.print("release pressure.");
}

void resetDisplay() {
  // Reset the display
  lcd.clear();
  lcd.home();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void intrusionDetected() {
  resetDisplay();
  lcd.print("Intrusion detected");
}

void printPopUpMessage(int duration) {
  resetDisplay();
  
  // Print on the LCD
  lcd.print("Intrusion detected");
  lcd.setCursor(0,1);
  lcd.print("5 minutes lost!!");
  
}

void lcdShowBootScreen() {
  // Reset the display
  lcd.clear();
  delay(1000);
  lcd.home();
  
  // Print on the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  
  buzzerBeep();
  lcd.print("Starting up ");
  delay(500);
  printDots(7); 
   
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Testing sensors");
  testingLedSegments();

  buzzerBeep();
  lcd.setCursor(0,1);
  lcd.print("Activating explosive");
  delay(2000);

  buzzerBeep();
  lcd.setCursor(0,2);
  lcd.print("Setting timer");
  startUpCounter();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bomb armed");

  buzzerBeep();
  delay(500);
  buzzerBeep();
  lcd.setCursor(0,2);

    
}


void printDots(byte amount) {
  for (byte i = 0; i < amount; i ++) {
    lcd.print(".");
    delay(500);
    
  }
}


