/**************************************************************************/
/*! 
    @file     BubbleDisplay.h
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
    This is part of an Arduino library to interface with the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller which is connected via the I2C bus.

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

// Command definitions
#define LED_CLEARDISPLAY 0x01
#define LED_RETURNHOME 0x02
#define LED_SETCURSOR 0x03
#define LED_DISPLAYON 0x04
#define LED_DISPLAYOFF 0x05
#define LED_SCROLLRIGHT 0x06
#define LED_SCROLLLEFT 0x07
#define LED_CREATECHAR 0x08
#define LED_DATA 0x09


class BubbleDisplay : public Print {
public:
  BubbleDisplay();  // instantiate
  BubbleDisplay(uint8_t);  // instantiate w address

  void begin();  // initialize the display as if reset

  void clear();  // clears the display buffer and sets the cursor posn to zero
  void home();   // sets the cursor to location 0
  void setCursor(uint8_t);  // sets the cursor location

  void noDisplay();  // disable display
  void display();  // enable display
  void scrollDisplayLeft();  
  void scrollDisplayRight();

  void createChar(uint8_t, uint8_t);  // which char, char defn

  virtual void write(uint8_t);
  virtual void write(const char *str);  
  using Print::write;
  
private:
  void sendCmd(uint8_t);

  uint8_t devAddr;
};

#endif
