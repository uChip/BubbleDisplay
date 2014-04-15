
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
// ADC6, ADC7
#define DIGIT_5  A6
#define DIGIT_6  A7
// PB0, PB1
#define DIGIT_7  8
#define DIGIT_8  9

// Segments written as an 8-bit register (port D)

// This sets the delay time for frame rate
// The value is repeated for each of 8 digits on the display so 
//   frame rate = 1 / (8 * DIGIT_TIME) = 1mS -> 125 Hz
#define DIGIT_TIME 1

// Declare global variables
uint8_t cursor = 0;
uint8_t scroll = 0;
boolean enable = true;

// Default startup data
char banner[] = {'S', 'P', 'A', 'r', 'k', 'F', 'u', 'n'};

char displayBuff[256];
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
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  digitalWrite(DIGIT_5, LOW);
  digitalWrite(DIGIT_6, LOW);
  digitalWrite(DIGIT_7, LOW);
  digitalWrite(DIGIT_8, LOW);

  clearDisplay();

  for(int i=0;i<8;i++){
    displayBuff[i] = banner[i];
  }

  // set up the I2C port
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  
}

void loop() {

  // display 8 chars of the displayBuff starting at the scroll posn

    PORTD = ~chargen[displayBuff[scroll + 0]];
    if(enable) digitalWrite(DIGIT_1, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_1, LOW);

    PORTD = ~chargen[displayBuff[scroll + 1]];
    if(enable) digitalWrite(DIGIT_2, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_2, LOW);

    PORTD = ~chargen[displayBuff[scroll + 2]];
    if(enable) digitalWrite(DIGIT_3, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_3, LOW);

    PORTD = ~chargen[displayBuff[scroll + 3]];
    if(enable) digitalWrite(DIGIT_4, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_4, LOW);

    PORTD = ~chargen[displayBuff[scroll + 4]];
    if(enable) digitalWrite(DIGIT_5, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_5, LOW);

    PORTD = ~chargen[displayBuff[scroll + 5]];
    if(enable) digitalWrite(DIGIT_6, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_6, LOW);

    PORTD = ~chargen[displayBuff[scroll + 6]];
    if(enable) digitalWrite(DIGIT_7, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_7, LOW);

    PORTD = ~chargen[displayBuff[scroll + 7]];
    if(enable) digitalWrite(DIGIT_8, HIGH);
    delay(DIGIT_TIME);
    digitalWrite(DIGIT_8, LOW);
}

// This function executes whenever data is received from master
// Function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  if(howMany > 3) reboot();

  for(int i=0;i<howMany;i++){
    rcvArray[i] = Wire.read(); // receive byte as a character
  }

  processCommand();
}


void processCommand(){
    switch(rcvArray[0]){
    case LED_CLEARDISPLAY:
      clearDisplay();
    break;
    case LED_HOMECURSOR:
      cursor = 0;
    break;
    case LED_HOMESCROLL:
      scroll = 0;
    break;
    case LED_DISPLAYON:
      enable = true;
    break;
    case LED_DISPLAYOFF:
      enable = false;
    break;
    case LED_SCROLLLEFT:
      scroll++;
      if(scroll>255-8) scroll = 255-8; //don't go past the end
    break;
    case LED_SCROLLRIGHT:
      scroll--;
      if(scroll>255-8) scroll = 0; //don't go past the beginning
    break;
    case LED_SETCURSOR:
      cursor = rcvArray[1];
    break;
    case LED_SETSCROLL:
      scroll = rcvArray[1];
    break;
    case LED_CREATECHAR:
      chargen[rcvArray[1]] = rcvArray[2];
    break;
    case LED_DATA:
      displayBuff[cursor++] = rcvArray[1];
    break;
    default:
      reboot();
    }
}

void clearDisplay(){
  // initialize the control and data
  cursor = 0;
  scroll = 0;
  enable = true;

  for(int i=0;i<256;i++){
    displayBuff[i] = ' ';
  }
}

void reboot(){
  asm volatile ("  jmp 0");  
}
