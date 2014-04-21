/**************************************************************************/
/*
    file:     BubbleFade.ino
    author:   C. Schnarel
    license:  Beerware
	
    This is an example Arduino sketch showing the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller varying brightness of
    the display.

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

    HISTORY

    2014-Apr-20  - First release, C. Schnarel
*/
/**************************************************************************/


// include the library code:
#include <Wire.h>
#include <BubbleDisplay.h>

// initialize the library with the numbers of the interface pins
BubbleDisplay led;

int bright = 250;
int delta = 2;

void setup() {
  // set up the I2C bus
  Wire.begin();
  // set up the LCD's number of columns and rows: 
  led.begin();
  // Print a message to the LCD.
  led.print("SparkFun");
}

void loop() {
  // Turn off the display:
  led.setBrightness(uint8_t (bright));
  delay(10);
  bright += delta;
  if(bright>250 || bright<0){
    delta = -delta;
    bright += delta;
  }
}