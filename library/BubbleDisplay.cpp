/**************************************************************************/
/*! 
    @file     BubbleDisplay.cpp
    @author   C. Schnarel
	@license  Beerware
	
    This is part of an Arduino library to interface with the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller which is connected via the I2C
    bus.

    Display Controller I2C device class file

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

	@section  HISTORY

    2014-Apr-24  - First release, C. Schnarel
*/
/**************************************************************************/

#include "BubbleDisplay.h"

/** Default constructor, uses default I2C address.
 * @see LED_DEFAULTADDR
 */
BubbleDisplay::BubbleDisplay() {
    devAddr = LED_DEFAULTADDR;
}

/** Specific address constructor.
 * @param address I2C address
 */
BubbleDisplay::BubbleDisplay(uint8_t address) {
    devAddr = address;
}

/** Power on and prepare for general usage.
 * The controller is ready to use automatically upon power-up.   The begin()
 * function sets the same values as power up since a reset of the
 * Arduino did not necessarily restart the display controller.
 */
void BubbleDisplay::begin() {
  sendCmd(LED_CLEARDISPLAY);	
  sendCmd(LED_DISPLAYON);	
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return true if connection is valid, false otherwise
 */
bool BubbleDisplay::testConnection() {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

/** Clears the display buffer and sets the cursor and scroll posns to zero
 */
void BubbleDisplay::clear(){
  sendCmd(LED_CLEARDISPLAY);	
}

/** Sets the cursor posn to zero.
 *  Also sets the scroll posn to zero.
 */
void BubbleDisplay::home(){
  sendCmd(LED_RETURNHOME);	
}

/** Sets the cursor location
 */
void BubbleDisplay::setCursor(uint8_t position){
    Wire.beginTransmission(devAddr);
    Wire.write(LED_SETCURSOR);
    Wire.write(position);
    Wire.endTransmission();
}

/** Disable display
 */
void BubbleDisplay::noDisplay(){
  sendCmd(LED_DISPLAYOFF);	
}

/** Enable display
 */
void BubbleDisplay::display(){
  sendCmd(LED_DISPLAYON);	
}

/** Scroll the display one char to the left
 */
void BubbleDisplay::scrollDisplayLeft(){
  sendCmd(LED_SCROLLLEFT);	
}
  
/** Scroll the display one char to the right
 */
void BubbleDisplay::scrollDisplayRight(){
  sendCmd(LED_SCROLLRIGHT);	
}

/** Replaces char in the character generator with defn
 */
void BubbleDisplay::createChar(uint8_t char, uint8_t defn){
    Wire.beginTransmission(devAddr);
    Wire.write(LED_CREATECHAR);
    Wire.write(char);
    Wire.write(defn);
    Wire.endTransmission();
}

/** write a char to the current cursor position.
 *  Cursor automatically increments to next position (255 max)
 */
virtual void BubbleDisplay::write(uint8_t value){
    Wire.beginTransmission(devAddr);
    Wire.write(LED_DATA);
    Wire.write(value);
    Wire.endTransmission();
}

/** Write a null-terminated string to the display starting at the
 *  current cursor posn.  Cursor automatically increments to next
 *  posn (255 max)
 */
virtual void BubbleDisplay::write(const char *str){
    Wire.beginTransmission(devAddr);
    Wire.write(LED_DATA);
    int i=0;
    while(*str && i<256){
        Wire.write(*str);
        str++;
        i++;
    }
    Wire.endTransmission();
}
  
/** which char, char defn
 */
void BubbleDisplay::sendCmd(uint8_t command)){
    Wire.beginTransmission(devAddr);
    Wire.write(command);
    Wire.endTransmission();
}

/* End of BubbleDisplay.cpp */