
/**************************************************************************/
/*
    file:     ScrollingBanner.ino
    author:   C. Schnarel
    license:  Beerware
	
    This is an example Arduino sketch showing the hp "Bubble Display"
    scrolling a text banner back-and-forth across the display.

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

    HISTORY

    2014-Apr-17  - First release, C. Schnarel
*/
/**************************************************************************/

#include <Wire.h>
#include "BubbleDisplay.h"

BubbleDisplay theDisplay;

void setup() {
  Serial.begin(115200);

  Wire.begin();
  // set speed of I2C bus
  TWBR = 12;  // 400 kHz (maximum)
  
  if(theDisplay.testConnection()) Serial.println("Display controller found");

  theDisplay.begin();
  theDisplay.print("        SparkFun Rocks!        ");
  
}  // end of setup()

int j=0;
int k=1;

void loop() {
  if(j>31 || j<0) k = -k;
  if(k>0)  theDisplay.scrollDisplayLeft();
  if(k<0)  theDisplay.scrollDisplayRight();
  j += k;
  delay(250);
}  // end of loop()

