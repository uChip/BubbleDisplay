
/**************************************************************************/
/*
    file:     Display_Firmware.h
    author:   C. Schnarel
    license:  Beerware
	
    This is part of an Arduino library to interface with the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller which is connected via
    the I2C bus.

    Display controller I2C device firmware

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

    HISTORY

    2014-Apr-20  - First release, C. Schnarel
*/
/**************************************************************************/

// Include libraries this sketch will use
#include <Wire.h>
#include "CharGenROM.h"
#include "BubbleCommands.h"

// Define pins used in this sketch
// debug LED
#define LED 13
// ADC0-ADC3
#define DIGIT_1  A3
#define DIGIT_2  A2
#define DIGIT_3  A1
#define DIGIT_4  A0

//BOARD 22MAR2014
// ADC6, ADC7
//#define DIGIT_5  A6
//#define DIGIT_6  A7
// PB0, PB1
//#define DIGIT_7  8
//#define DIGIT_8  9

//BOARD 07APR2014
// ADC6, ADC7
#define DIGIT_5  8
#define DIGIT_6  9
// PB0, PB1
#define DIGIT_7  10
#define DIGIT_8  11

// Segments written as an 8-bit register (port D)

// This sets the delay time for frame rate
// The value is repeated for each of 8 digits on the display so 
//   frame rate = 1 / (8 * DIGIT_TIME) = 1mS -> 125 Hz
#define DIGIT_TIME 1

// Declare global variables
// Incoming display data is stored in displayBuff at
// the index value stored in cursor.
// cursor in incremented after storing the data.
// Since cursor is an unsigned 8-bit value it automatically
// wraps back to the beginning if incremented past the end.
// There are therefore no illegal values for cursor.
uint8_t cursor = 0;
// The display refresh routine shows 8 characters
// starting at the index value stored in scroll.
// Since we don't want to show data outside the buffer
// scroll must be constrained to always be 8 less
// than the buffer length; (256-8) =< 248.
uint8_t scroll = 0;
// The display digit lines (cathodes) are only pulsed
// when the enable variable holds a value of true
boolean enable = true;

// Default startup data
char banner[] = { 'S', 'P', 'A', 'R', 'K', 'F', 'U', 'N' };

// This is the display buffer.  It is interpreted as ASCII data and
// holds up to 256 characters (0-255)
char displayBuff[256];

// Data from the I2C bus is copied into this buffer for processing
// Since no command plus parameters is more than 3 bytes long
// only three bytes are needed
byte rcvArray[3];


void setup() {
  // set up the debug LED
  pinMode(LED, OUTPUT);
  
  // set up the segment control port
  DDRD = 0xFF;
  PORTD = 0x00;
  
  // set up the digit control pins
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);
  pinMode(DIGIT_5, OUTPUT);
  pinMode(DIGIT_6, OUTPUT);
  pinMode(DIGIT_7, OUTPUT);
  pinMode(DIGIT_8, OUTPUT);
  // initialize all digits to off
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  digitalWrite(DIGIT_5, LOW);
  digitalWrite(DIGIT_6, LOW);
  digitalWrite(DIGIT_7, LOW);
  digitalWrite(DIGIT_8, LOW);

  // Initialize the display data buffer and refresh variables
  clearDisplay();

  // Preload the display with something interesting while
  // waiting for data or commands to come in on the bus
  for(int i=0;i<8;i++){
    displayBuff[i] = banner[i];
  }

  // Set up the I2C port.
  // By giving begin the parameter "4" we are telling wire to
  // set up as an I2C slave device listening for data sent to
  // address 4.
  Wire.begin(4);                // join i2c bus with address #4
  
  // Registering the receiveEvent(int) routine to be called
  // whenever data comes in (sent to our address)
  Wire.onReceive(receiveEvent); // register event

}  // End of setup()

void loop() { // Do this over and over

  // Display 8 chars of the displayBuff starting at the scroll posn

  // Take the character value stored in the displayBuff at index scroll and
  // use that value to look up the segment values in the character generator
  // table, chargen.  Send the segment values to the segment lines, PORTD.
  PORTD = chargen[displayBuff[scroll + 0]];
  
  // Only pulse the digit line (cathode) high if the
  // display is enabled (the enable variable is true)
  // The digit line is pulsed high to turn on the transistor driver which
  // allows the LED current to flow to ground lighting the segments.
  if(enable) digitalWrite(DIGIT_1, HIGH);
  
  // wait out the time to show this digit
  delay(DIGIT_TIME);
  // always turn the digit off again even if the display is not enabled
  digitalWrite(DIGIT_1, LOW);

  // Now repeat the same steps for each of the other digits in the display
  PORTD = chargen[displayBuff[scroll + 1]];
  if(enable) digitalWrite(DIGIT_2, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_2, LOW);

  PORTD = chargen[displayBuff[scroll + 2]];
  if(enable) digitalWrite(DIGIT_3, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_3, LOW);

  PORTD = chargen[displayBuff[scroll + 3]];
  if(enable) digitalWrite(DIGIT_4, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_4, LOW);

  PORTD = chargen[displayBuff[scroll + 4]];
  if(enable) digitalWrite(DIGIT_5, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_5, LOW);

  PORTD = chargen[displayBuff[scroll + 5]];
  if(enable) digitalWrite(DIGIT_6, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_6, LOW);

  PORTD = chargen[displayBuff[scroll + 6]];
  if(enable) digitalWrite(DIGIT_7, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_7, LOW);

  PORTD = chargen[displayBuff[scroll + 7]];
  if(enable) digitalWrite(DIGIT_8, HIGH);
  delay(DIGIT_TIME);
  digitalWrite(DIGIT_8, LOW);
}  // End of loop().  Finished with multiplexing the display one time

// This function executes whenever data is received from I2C bus
// addressed for this device.
// Function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  // We never expect to receive commands plus parameters longer than 3 bytes.
  // Since this is a dedicated controller about the only way to recover
  // from the error is to start all over again.
  if(howMany > 3) reboot();

  // read the data into the array for processing
  for(int i=0;i<howMany;i++){
    rcvArray[i] = Wire.read(); // receive byte as a character
  }

  // based on the value of the first byte, the command, decide
  // which code to execute.
  switch(rcvArray[0]){
  case LED_CLEARDISPLAY:
    // reinitialize all display controls to their default values
    clearDisplay();
    break;
  case LED_HOMECURSOR:
    // the next received data will be stored in displayBuff at index 0
    cursor = 0;
    break;
  case LED_HOMESCROLL:
    // start displaying characters from displayBuff starting at index 0
    scroll = 0;
    break;
  case LED_DISPLAYON:
    // allow the digit lines to be pulsed
    enable = true;
    break;
  case LED_DISPLAYOFF:
    // do not pulse the digit lines
    enable = false;
    break;
  case LED_SCROLLLEFT:
    // Although the index increases (goes right) the characters
    // appear to have shifted left
    scroll++;
    if(scroll>256-8) scroll = 256-8; //don't go past the end
    break;
  case LED_SCROLLRIGHT:
    // Although the index decreases (goes left) the characters
    // appear to have shifted right
    scroll--;
    if(scroll>256-8) scroll = 0; //this would only be true if
    // scroll wrapped when decremented past 0
    break;
  case LED_SETCURSOR:
    // Allow the application to set where the next character goes.
    // Since the parameter is a byte, there are no illegal values.
    cursor = rcvArray[1];
    break;
  case LED_SETSCROLL:
    // Allow the application to set the scroll position, but
    // not higher than 8 from the end of displayBuff.
    scroll = rcvArray[1];
    if(scroll>256-8) scroll = 256-8; //don't go past the end
    break;
  case LED_CREATECHAR:
    // The application can override any character generator definition.
    // Valid characters are 0 to 127 so constrain the parameter to that.
    // The new definition will persist until the display controller is
    // restarted.
    chargen[rcvArray[1] & 0x7F] = rcvArray[2];
    break;
  case LED_DATA:
    // New data to be displayed.  Valid values are 0 to 7F (0-127).
    // If more data is provided than the buffer will hold, the cursor
    // automatically wraps back to the beginning.
    displayBuff[cursor++] = rcvArray[1] & 0x7F;
    break;
  case LED_RESTART:
    // Resets the display controller.
    reboot();
    break;
  default:
    // Invalid command.  Reset the display controller to try to recover.
    reboot();
  }
}

// initialize the control and data
void clearDisplay(){
  // reset display controls to their defaults
  cursor = 0;  // next data char goes into start of buffer
  scroll = 0;  // display refresh from start of buffer
  enable = true;  // display defaults to on (digit lines pulsed)

  // fill the display buffer with spaces
  for(int i=0;i<256;i++){
    displayBuff[i] = ' ';
  }
}

// software reset
void reboot(){
  asm volatile ("  jmp 0");  
}

