/*
  BubbleDisplay Library - setCursor
 
 Demonstrates the use of an hp BubbleDisplay.  The BubbleDisplay library
 is modeled after the LiquidCrystal library and implements many of the same
 library calls.  To demonstrate this, this example from LiquidCrystal has
 been ported to BubbleDisplay and the changes noted.
 
 This sketch prints to all the positions of the LCD using the
 setCursor(0 method:
 
  The circuit:
 * BubbleDisplay 5V pin to 5V supply
 * BubbleDisplay GND pin to GND
 * BubbleDisplay SDA pin to SDA or A4
 * BubbleDisplay SCL pin to SCL or A5
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe
 modified 19 Apr 2014
 by Chip Schnarel

 This example code is in the public domain.
 
 http://www.github.com/uchip/BubbleDisplay

 */

// include the library code:
#include <Wire.h>
#include <BubbleDisplay.h>

// these constants won't change.  But you can change the size of
// your LCD using them:
const int numRows = 1;
const int numCols = 8;

// initialize the library with the numbers of the interface pins
BubbleDisplay led;

void setup() {
  // set up the I2C bus
  Wire.begin();
  // set up the display 
  led.begin();
}

void loop() {
  // loop from ASCII 'a' to ASCII 'z':
  for (uint8_t thisLetter = 'a'; thisLetter <= 'z'; thisLetter++) {
    // loop over the columns:
    for (uint8_t thisCol = 0; thisCol < numCols; thisCol++) {
      // loop over the rows:
      for (uint8_t thisRow = 0; thisRow < numRows; thisRow++) {
        // set the cursor position:
        led.setCursor(byte(thisCol));
        // print the letter:
        led.write(thisLetter);
        delay(200);
      }
    }
  }
}


