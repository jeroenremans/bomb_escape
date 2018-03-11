

class LedSegment10 {
 public:
   int X, Y;
   int Color;
   LedSegment10( int pin_ser, int pin_rclk, int pin_srclk) ;
   void setMode();
};


LedSegment10::LedSegment10( int pin_ser, int pin_rclk, int pin_srclk) {

  pinMode(pin_ser, OUTPUT);
  pinMode(pin_rclk, OUTPUT);
  pinMode(pin_srclk, OUTPUT);
}  

void  LedSegment10::setMode() {
    //do something here;  
}
