
#include <MD_MAX72xx.h>


#define  MAX_DEVICES 1


// Ports Matrix
#define  CLK_PIN   5  // or SCK
#define DATA_PIN  6 //5  // or MOSI
#define CS_PIN    7  // or SS

// Setup Matrix display
MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Arbitrary pins


#define ANIMATION_DELAY 250  // milliseconds
#define MAX_FRAMES      4   // number of animation frames


// Arduino pin numbers
const int SW_pin = 40; // digital pin connected to switch output
const int X_pin = 8; // analog pin connected to X output
const int Y_pin = 9; // analog pin connected to Y output


void resetMatrix(void) {
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void mazeSetup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  mx.begin();
  resetMatrix();
}

int x_step = 0;
int y_step = 0;

void mazeLoop() {
  /*Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));

  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
*/
  
//showUpArrows();
  delay(100);
  mazeGame();
}


const uint16_t maze[16] = {
0b1111101011111110,
0b0010001010001000,
  0b1110111011101010,
0b1000101000001010,
  0b1111101111111010,
0b1010100000000010,
  0b1010101011111110,
0b0010101000100010,
  0b1110111111101110,
0b1000100000101010,
  0b1110101110101010,
0b1010101000101000,
  0b1011101111101110,
0b1010101000100000,
  0b1011101111101110,
0b0000000000000000

  };

byte my2dArray[16][16]={
  {1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0},
  {0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
  {1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0},
  {1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0},
  {1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0},
  {0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0},
  {1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0},
  {1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0},
  {1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0},
  {1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0},
  {1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0},
  {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


uint8_t smiley[8] =
{B00111100,
B01000010,
B10100101,
B10000001,
B10100101,
B10011001,
B01000010,
B00111100};






// We always wait a bit between updates of the display
#define  DELAYTIME  75  // in milliseconds

void showUpArrows()
// Demonstrates the use of transform() to move bitmaps on the display
// In this case a user defined bitmap is created and animated.
{
  uint8_t arrow[COL_SIZE] =
  {
    0b00000000,
    0b00010000,
    0b10011000,
    0b11111100,
    0b11111110,
    0b11111100,
    0b10011000,
    0b00010000
  };

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU
  };

  mx.clear();

  // use the arrow bitmap
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t j=0; j<mx.getDeviceCount(); j++) {
    mx.setBuffer(((j+1)*COL_SIZE)-1, COL_SIZE, arrow);
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(DELAYTIME);

  // run through the transformations
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  for (uint8_t i=0; i<17; i++)
  {
    mx.transform(t[0]);
    delay(DELAYTIME*2);
  }
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);
  
  mx.clear();

  initGame();
}

boolean mazedDisarmed = false;
const int minC = 0;
int maxC = 0;
const int minR = 0;
const int maxR = ROW_SIZE-1;
int  nCounter = 0;
int  row = 0, column = 0;
int8_t dR = 1, dC = 1;  // delta row and column
  
void initGame() {
  maxC = mx.getColumnCount()-1;
  mx.clear();
}

void mazeGame() {
    if (!mazedDisarmed) {
        if (analogRead(X_pin) > 750) {
          dC = -1;
        } else if (analogRead(X_pin) < 250) {
          dC = 1;
        } else {
          dC = 0;
        }
        if (analogRead(Y_pin) > 750) {
          dR = -1;
        } else if (analogRead(Y_pin) < 250) {
          dR = 1;
        } else {
          dR = 0;
        }
  
      if (my2dArray[(row * 2) + dR][(column * 2) + dC] == 1) {
        mx.setPoint(7-row, column, false);
        row += dR;
        column += dC;
        mx.setPoint(7-row, column, true);
      }
      
      if (row == 7 && column == 7) {  
          mazedDisarmed = true;
          eventListener(EVENT_MAZE_DISARMED);
      }
      //delay(500/2);
      if ((row == minR) || (row == maxR)) {
        dR = -dR;
      }
      if ((column == minC) || (column == maxC)) {
        dC = -dC;
      }
    }
}
