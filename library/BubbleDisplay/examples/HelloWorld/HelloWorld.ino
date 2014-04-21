/*
  BubbleDisplay Library - Hello World
 
 Demonstrates the use of a hp BubbleDisplay.  The BubbleDisplay library
is modeled after the LiquidCrystal library and implements many of the same
library calls.  To demostrate this, the examples from LiquidCrystal have
been ported to BubbleDisplay and the changes noted.
 
 This sketch prints "Hello World!" to the display
 and shows the time.
 
  The circuit:
 * BubbleDisplay 5V pin to supply
 * BubbleDisplay GND pin to GND
 * BubbleDisplay SCL pin to SCL or A4
 * BubbleDisplay SDA pin to SDA or A5
 
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

// initialize the library
BubbleDisplay led;

void setup() {
  // set up the I2C bus
  Wire.begin();
  // set up the display
  led.begin();
  // Print a message to the LCD.
  led.print("hello, world!");
}

void loop() {
  // set the cursor to column 5
  led.setCursor(5);
  // print the number of seconds since reset:
  led.print(millis()/1000);
}

