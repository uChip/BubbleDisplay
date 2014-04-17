
/**************************************************************************/
/*
    file:     BubbleMeter.ino
    author:   C. Schnarel
    license:  Beerware
	
    This is an example Arduino sketch showing the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller displaying the voltage
    measured on analog input A0.

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
  TWBR = 12;  // Run the I2C bus at its max speed, 400 kHz
  
  if(theDisplay.testConnection()) Serial.println("Display controller found");

  theDisplay.begin();

}  // end of setup()

void loop() {
  int adcValue;
  float voltage;
  
  adcValue = analogRead(A0);  // Input is a pot between Vcc and Gnd (presumably 5V)
  voltage = 5.0 / 1023.0 * adcValue;  // Convert the 10-bit input to a floating point number

// Send the string to the display
  theDisplay.home();
  theDisplay.print(voltage);
  Serial.println(voltage);  // for debug print out the string we sent to the display

  delay(250);
}  // end of loop()

