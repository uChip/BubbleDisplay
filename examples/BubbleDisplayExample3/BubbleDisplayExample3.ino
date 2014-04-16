#include <Wire.h>
#include "BubbleDisplay.h"

BubbleDisplay theDisplay(4);

void setup(){
  delay(5000);
  Serial.begin(115200);
  Wire.begin();
  TWBR = 12;  // 400 kHz
  
  Serial.println("About to call display.begin()");
  delay(5);
  theDisplay.begin();
  Serial.println("Returned from display.begin()");
  delay(5000);
  
  float num = 3.1415;
  Serial.println(num, 3);
  theDisplay.print("ABCDEFGHIJ");
  
  delay(2000);
  theDisplay.scrollDisplayLeft();
  delay(2000);
  theDisplay.noDisplay();
  delay(2000);
  theDisplay.display();
  delay(2000);
  theDisplay.scrollDisplayLeft();
  delay(2000);
  theDisplay.home();
  delay(2000);
  theDisplay.createChar('A',0b11111001);
  theDisplay.createChar('B',0b10100100);
  theDisplay.createChar('C',0b10110000);
  theDisplay.createChar('D',0b10011001);
  delay(2000);
  theDisplay.setCursor(3);
  theDisplay.write('F');
  delay(2000);
  theDisplay.clear();
  theDisplay.print(num);
}

void loop(){
}

