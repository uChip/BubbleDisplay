/*
  BubbleDisplay Library - scrollDisplayLeft() and scrollDisplayRight()
 
 Demonstrates the use of an hp BubbleDisplay.  The BubbleDisplay library
 is modeled after the LiquidCrystal library and implements many of the same
 library calls.  To demonstrate this, this example from LiquidCrystal has
 been ported to BubbleDisplay and the changes noted.
 
 This sketch prints "Hello World!" to the display and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.
 
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

void setup() {
  // set up the I2C bus
  Wire.begin();
  // set up the LCD's number of columns and rows: 
  led.begin();
  // Print a message to the LCD.
  led.print("             hello, world!             ");
  for (int i = 0; i < 13; i++) {
    // scroll one position left:
    led.scrollDisplayLeft(); 
  }
  delay(1000);
}

void loop() {
  // scroll 13 positions (string length) to the left 
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    led.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }

  // scroll 26 positions to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 26; positionCounter++) {
    // scroll one position right:
    led.scrollDisplayRight(); 
    // wait a bit:
    delay(150);
  }
  
    // scroll 13 positions to the left
    // to move it back to center:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    led.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }
  
  // delay at the end of the full loop:
  delay(1000);

}