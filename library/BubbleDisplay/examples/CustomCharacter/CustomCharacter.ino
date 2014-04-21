/*
  BubbleDisplay Library - Custom Characters
 
 Demonstrates the use of an hp BubbleDisplay.  The BubbleDisplay library
is modeled after the LiquidCrystal library and implements many of the same
library calls.  To demonstrate this, this example from LiquidCrystal has
been ported to BubbleDisplay and the changes noted.

 
 This sketch prints "I <heart> Arduino!" and a little dancing man
 to the LCD.
 
 The circuit:
 * BubbleDisplay 5V pin to 5V supply
 * BubbleDisplay GND pin to GND
 * BubbleDisplay SDA pin to SDA or A4
 * BubbleDisplay SCL pin to SCL or A5
 
 created21 Mar 2011
 by Tom Igoe
 Based on Adafruit's example at
 https://github.com/adafruit/SPI_VFD/blob/master/examples/createChar/createChar.pde

 modified 19 Apr 2014
 by Chip Schnarel
 
 This example code is in the public domain.
 
 http://www.github.com/uchip/BubbleDisplay
 */

// include the library code:
#include <Wire.h>
#include <BubbleDisplay.h>

// initialize the library with the numbers of the interface pins
BubbleDisplay led;

// make some custom characters:
byte heart =    0b11100011;
byte smiley =   0b10000000;
byte frownie =  0b11010100;
byte armsDown = 0b11011100;
byte armsUp =   0b11111110;

void setup() {
  // set up the I2C bus
  Wire.begin();
  // set up the lcd's number of columns and rows: 
  led.begin();

  // create a new character
  led.createChar(byte(0), heart);
  // create a new character
  led.createChar(byte(1), smiley);
  // create a new character
  led.createChar(byte(2), frownie);
  // create a new character
  led.createChar(byte(3), armsDown);  
  // create a new character
  led.createChar(byte(4), armsUp);  

  // Print a message to the lcd.
  led.print("I "); 
  led.write(byte(0));
  led.print(" Arduino! ");
  led.write(byte(1));

}

void loop() {
  // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 5th position:
  led.setCursor(2);
  // draw the little man, arms down:
  led.write(3);
  delay(delayTime);
  led.setCursor(2);
  // draw him arms up:
  led.write(4);
  delay(delayTime); 
}



