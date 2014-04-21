/**************************************************************************/
/*
    file:     BubbleDisplay.h
    author:   C. Schnarel
    license:  Beerware
	
    This is part of an Arduino library to interface with the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller which is connected via
    the I2C bus.

    Display controller I2C device class header file

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

	@section  HISTORY

    2014-Apr  - First release, C. Schnarel
*/
/**************************************************************************/

#ifndef _BubbleDisplay_h
#define _BubbleDisplay_h

#include <inttypes.h>
#include <Wire.h>
#include "Print.h"

// I2C bus address of the display controller
#define LED_DEFAULTADDR 0x04


class BubbleDisplay : public Print {
public:
  BubbleDisplay();  // instantiate
  BubbleDisplay(uint8_t);  // instantiate w address
  bool testConnection();  // check that the display controller responds on the bus

  void begin();  // initialize the display as if reset

  void clear();  // clears the display buffer and sets the cursor posn to zero
  void home();   // sets the cursor to location 0
  void setCursor(uint8_t);  // sets the cursor location
  void setBrightness(uint8_t);  // sets the LED brightness 0-250

  void noDisplay();  // disable display
  void display();  // enable display
  void scrollDisplayLeft();  
  void scrollDisplayRight();
  void restart();

  void createChar(uint8_t, uint8_t);  // which char, char defn

  virtual size_t write(uint8_t);
  //virtual void write(const char *str);  
  using Print::write;
  
private:
  void sendCmd(uint8_t);

  uint8_t devAddr;
};

#endif
