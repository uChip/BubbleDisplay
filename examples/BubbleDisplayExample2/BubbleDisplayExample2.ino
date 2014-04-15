
#include <Wire.h>
#include "BubbleDisplay.h"
#include "BubbleCommands.h"

BubbleDisplay theDisplay;

char banner[] = "        SparkFun Rocks!        ";

void setup() {
  Serial.begin(115200);

  Wire.begin();
  TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz
  //TWBR = 78;  // 25 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
  //TWBR = 158;  // 12.5 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
  
  if(theDisplay.testConnection()) Serial.println("Controller Found");

  theDisplay.begin();
  delay(5);

  LEDdisplay(banner);
  
  delay(12000); // give time for the banner to scroll by
}  // end of setup()

void loop() {
  int sensorValue;
  float voltage;
  char strBuff[20];
  
  sensorValue = analogRead(A0);  // Input is a pot between Vcc and Gnd (presumably 5V)
  voltage = 5.0 / 1023.0 * sensorValue;  // Convert the 10-bit input to a floating point number
  dtostrf(voltage, 4, 2, strBuff);  // convert the number to a string

// Send the string to the display
  theDisplay.print(strBuff);
  Serial.println(strBuff);  // for debug print out the string we sent to the display

  delay(250);
}  // end of loop()

//-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-
//  Display Controller Functions
//-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-

boolean  LEDdisplay(char* string){
  int len = 0;
  int i;
  
  theDisplay.clear();
  delay(5);
  theDisplay.print(string);
  
  for(i=0;i<22;i++) {
    theDisplay.scrollDisplayLeft();
    delay(250);
  }
  
  for(i=0;i<8;i++) {
    theDisplay.scrollDisplayRight();
    delay(250);
  }

  for(i=0;i<22;i++) {
    theDisplay.scrollDisplayRight();
    delay(250);
  }
  theDisplay.clear();
}


