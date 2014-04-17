/**************************************************************************/
/*
 file:     BubbleTest.ino
 author:   C. Schnarel
 license:  Beerware
 	
 This is an Arduino sketch to interface with and test the hp "Bubble Display"
 display controller which is connected via the I2C bus.
 
 Display controller I2C device test software
 
 (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
 Updates should (hopefully) always be available at
 https://github.com/uChip/BubbleDisplay
 
 HISTORY
 
 2014-Apr-16  - First release, C. Schnarel
 */
/**************************************************************************/

// As each message is printed out on the serial monitor, the display should
//  show the text quoted in the message.

// The I2C bus library from Arduino
#include <Wire.h>
// The interface library included with this distribution
#include "BubbleDisplay.h"

// Instantiate the library object
BubbleDisplay theDisplay(4);

void setup(){
  delay(5000);
  Serial.begin(115200);
  Wire.begin();
  // set the speed of the I2C bus
  TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz
  //TWBR = 78;  // 25 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
  //TWBR = 158;  // 12.5 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler

  Serial.println("About to call display.begin()");
  delay(5);
  theDisplay.begin();
  if(theDisplay.testConnection()) Serial.println("Found display on I2C bus");
  delay(1000);

  float num = 3.1415;
  theDisplay.print("ABCDEFGHIJ");
  Serial.println("Should be displaying \"AbCdEFGH\"");  
  delay(4000);

  theDisplay.scrollDisplayLeft();
  Serial.println("Should be displaying \"bCdEFGHI\"");
  delay(4000);

  theDisplay.noDisplay();
  Serial.println("Should be displaying \"        \" (blank)");
  delay(4000);

  theDisplay.display();
  Serial.println("Should be displaying \"bCdEFGHI\" blinking");
  for(int i=0;i<20;i++){
    theDisplay.noDisplay();
    delay(250);
    theDisplay.display();
    delay(250);
  }

  Serial.println("Should be jittering between \"CdEFGHIJ\" and \"bCdEFGHI\"");
  for(int i=0;i<20;i++){
    theDisplay.scrollDisplayLeft();
    delay(250);
    theDisplay.scrollDisplayRight();
    delay(250);
  }

  theDisplay.home();
  Serial.println("Should be displaying \"AbCdEFGH\"");
  delay(4000);

  theDisplay.createChar('A',0b00000110);  // define "A" as "1"
  theDisplay.createChar('B',0b01011011);  // define "B" as "2"
  theDisplay.createChar('C',0b01001111);  // define "C" as "3"
  theDisplay.createChar('D',0b01100110);  // define "D" as "4"
  Serial.println("Should be displaying \"1234EFGH\"");
  delay(4000);

  theDisplay.setCursor(3);  // set data entry cursor to the 4th buffer location
  theDisplay.write('S');
  Serial.println("Should be displaying \"123SEFGH\"");
  delay(4000);

  theDisplay.clear();
  theDisplay.print(num, 4);
  Serial.println("Should be displaying \"3.1415  \"");
  delay(4000);

  theDisplay.restart();
  Serial.println("Should be displaying \"SPArkFun\"");
  delay(4000);

  for(int j=0;j<256;j++) theDisplay.write(j & 0x7F);
  Serial.println("Should be displaying a scrolling list of all characters");
}

void loop(){
  theDisplay.home();
  for(int k=0;k<248;k++) {
    theDisplay.scrollDisplayLeft();
    delay(250);
  }
}


