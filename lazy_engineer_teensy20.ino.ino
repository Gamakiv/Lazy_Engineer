#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Keyboard.begin ();
}
void loop() 
  {
    delay(100);
  }

void receiveEvent(int howMany) 
  {
    while (1 < Wire.available()) 
      { // loop through all but the last
        char c = Wire.read(); // receive byte as a character
        Serial.print(c);  
      }
  
  int x = Wire.read();    
  Serial.print(x);      
  
  if (x == 1)
      {
        Keyboard.print("Hello Teensy++2.0 -");
        delay(5000);
        Keyboard.press (KEY_RETURN);
        Keyboard.release (KEY_RETURN);
      }  
}

