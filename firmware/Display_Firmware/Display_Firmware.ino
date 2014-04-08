
// Basic framework for starting a new Arduino sketch

// Include libraries this sketch will use
#include <Wire.h>
#include "CharGenROM.h"

// Define pins used in this sketch
// debug LED
#define LED 13
// ADC0-ADC3
#define DIGIT_1  A3
#define DIGIT_2  A2
#define DIGIT_3  A1
#define DIGIT_4  A0
// ADC6, ADC7
#define DIGIT_5  A6
#define DIGIT_6  A7
// PB0, PB1
#define DIGIT_7  8
#define DIGIT_8  9

// Segments written as an 8-bit register (port D)

// Command Byte Definition
// Bit-7: Upsidedown Display - useful when display needs to be mounted upsidedown
// Bits-6,5: Mode - selects refresh mode
    // 0 - standard mode displays first 8 chars of displayBuff
    // 1 - scrolling mode displays N chars of displayBuff then jumps back to beginning
    // 2 - not yet defined
    // 3 - not yet defined
#define MODE_FLAG 0x60
// common commands
 // simple 8-char right side up
#define STD 0x00
 // scroll right side up
#define SCROLL 0x40
 // simple 8-char upsidedown
#define USD 0x80
 // scroll upsidedown
#define USDSCROLL 0xC0
 // easter egg
#define EASTEREGG 0xFF

// This sets the delay time for the scrolling.
//   Value is in milliseconds so default of 500ul means scroll rate is two char per second.
#define LOOP_DURATION  500ul

// This sets the delay time for frame rate
// The value is repeated for each of 8 digits on the display so frame rate = 1 / (8 * DIGIT_TIME) = 1mS -> 125 Hz
#define DIGIT_TIME 1

// Instantiate objects used in this project

// Declare global variables
unsigned long looptime;

char banner[] = {'S', 'P', 'A', 'r', 'k', 'F', 'u', 'n'};

union TheData {
  struct controlStruct {
    byte controlByte;
    byte lengthByte;
    char displayBuff[255];
  }cntl;
  byte rcvArray[257];
} fromMaster;

int buffOffset;

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
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  digitalWrite(DIGIT_5, LOW);
  digitalWrite(DIGIT_6, LOW);
  digitalWrite(DIGIT_7, LOW);
  digitalWrite(DIGIT_8, LOW);
  // set up the I2C port
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  
  // initialize the control, length and frame buffer values
  fromMaster.cntl.controlByte = 0;
  fromMaster.cntl.lengthByte = 0;
  for(byte i=0;i<8;i++){
    fromMaster.cntl.displayBuff[i] = banner[i];
  }

  // set up the scroll delay
  looptime = millis() + LOOP_DURATION;
  buffOffset = 0;
}

void loop() {
  // Do loopy application stuff
  switch(fromMaster.cntl.controlByte){
  case STD:
    digitalWrite(LED, HIGH);
    displayFrame(0);
    digitalWrite(LED, LOW);
    break;
  case SCROLL:
    displayFrame(buffOffset);
    break;
  default:
    break;
  }
  
  if(millis() > looptime){
    looptime += LOOP_DURATION;
    buffOffset++;
    if(buffOffset > int(fromMaster.cntl.lengthByte - 8)) buffOffset = 0;
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  int i;

  if(howMany >257) reboot();

  for(i=0;i<howMany;i++){
    fromMaster.rcvArray[i] = Wire.read(); // receive byte as a character
  }
  
  if(fromMaster.cntl.controlByte & MODE_FLAG == SCROLL) buffOffset = 0;
}

void displayFrame(int index){
  // display the first 8 chars of the displayBuff
    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 0]];
    digitalWrite(DIGIT_1, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_1, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 1]];
    digitalWrite(DIGIT_2, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_2, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 2]];
    digitalWrite(DIGIT_3, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_3, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 3]];
    digitalWrite(DIGIT_4, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_4, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 4]];
    digitalWrite(DIGIT_5, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_5, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 5]];
    digitalWrite(DIGIT_6, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_6, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 6]];
    digitalWrite(DIGIT_7, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_7, LOW);

    PORTD = ~chargen[fromMaster.cntl.displayBuff[index + 7]];
    digitalWrite(DIGIT_8, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_8, LOW);
}

void reboot(){
}
