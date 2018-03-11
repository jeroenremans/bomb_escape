#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 12
#define CSN_PIN 13
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

const byte address[6] = "00001";


void wirelessSetup()   /****** SETUP: RUNS ONCE ******/
{
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.startListening();
}//--(end setup )---

void wirelessLoop()   /****** LOOP: RUNS CONSTANTLY ******/
{
 
   if (radio.available()) {
    char text[80] = ""; 
    
    radio.read(&text, sizeof(text));
      Serial.println(text);
      showMessage2(text);
    
    //buzzerBeep();
    
  } else {
 //Serial.println("no signal");
 //delay(50);
  }
  

}
