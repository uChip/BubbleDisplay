
// Basic framework for starting a new Arduino sketch

// Include libraries this sketch will use
#include <Wire.h>
#include "CharGenROM.h"

// Define pins used in this sketch
// ADC0-ADC3
#define DIGIT_1  A0
#define DIGIT_2  A1
#define DIGIT_3  A2
#define DIGIT_4  A3
// ADC6, ADC7
#define DIGIT_5  5
#define DIGIT_6  6
// PB0, PB1
#define DIGIT_7  8
#define DIGIT_8  9

// Segments written as an 8-bit register



// This sets the delay time for the scrolling.
//   Value is in milliseconds so default of 1000ul means one char per second.
#define LOOP_DURATION  1000ul

// Instantiate objects used in this project

// Declare global variables
unsigned long looptime;

union TheData {
  struct controlStruct {
    byte controlByte;
    byte lengthByte;
    char displayBuff[255];
  }cntl;
  byte rcvArray[257];
} fromMaster;

byte buffOffset;

void setup() {
  DDRD = B11111111; //set PORTD as outputs
  PORTD = B11111111; //initialize PORTD to all segments off

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
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

    looptime = millis() + LOOP_DURATION; 
}

void loop() {
  // Do loopy application stuff
  switch(fromMaster.cntl.controlByte){
  case STD:
    displayFrame();
    break;
  case SCROLL:
    scrollFrame(buffOffset);
    break;
  case default:
    break;
  }
  
  if(looptime > millis()){
    looptime += LOOP_DURATION;
    buffOffset++;
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
}

void displayFrame(){
  // display the first 8 chars of the displayBuff
    PORTD = charROM[fromMaster.cntl.displayBuff[0]];
    digitalWrite(DIGIT_1, HIGH);
    delay(1);
    digitalWrite(DIGIT_1, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[1]];
    digitalWrite(DIGIT_2, HIGH);
    delay(1);
    digitalWrite(DIGIT_2, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[2]];
    digitalWrite(DIGIT_3, HIGH);
    delay(1);
    digitalWrite(DIGIT_3, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[3]];
    digitalWrite(DIGIT_4, HIGH);
    delay(1);
    digitalWrite(DIGIT_4, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[4]];
    digitalWrite(DIGIT_5, HIGH);
    delay(1);
    digitalWrite(DIGIT_5, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[5]];
    digitalWrite(DIGIT_6, HIGH);
    delay(1);
    digitalWrite(DIGIT_6, LOW);
    PORTD = charROM[fromMaster.cntl.displayBuff[6]];
    digitalWrite(DIGIT_7, HIGH);
    delay(1);
    digitalWrite(DIGIT_7, LOW);
    PORTD = charROM[fromMaster.dcntl.isplayBuff[7]];
    digitalWrite(DIGIT_8, HIGH);
    delay(1);
    digitalWrite(DIGIT_8, LOW);
}


