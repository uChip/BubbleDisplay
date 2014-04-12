
#include <Wire.h>

#define DISPLAY_ADDR 4

char banner[] = "        SparkFun Rocks!        ";

void setup() {
  Serial.begin(115200);

  LEDbegin(DISPLAY_ADDR);

  LEDdisplay(banner);
  
  delay(12000); // give time for the banner to scroll by
}  // end of setup

void loop() {
  int sensorValue;
  float voltage;
  char strBuff[20];
  
  sensorValue = analogRead(A0);  // Input is a pot between Vcc and Gnd (presumably 5V)
  voltage = 5.0 / 1023.0 * sensorValue;  // Convert the 10-bit input to a floating point number
  dtostrf(voltage, 4, 2, strBuff);  // convert the number to a string

// Send the string to the display
  LEDdisplay(strBuff);
  Serial.println(strBuff);  // for debug print out the string we sent to the display

  delay(250);
}

//-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-
//  Display Controller Functions
//-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-

void LEDbegin(byte address){
  Wire.begin();
  TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz
  //TWBR = 78;  // 25 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
  //TWBR = 158;  // 12.5 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
}

boolean  LEDdisplay(char* string){
  int len = 0;
  
  while(string[len++] != 0); // gets the length of the string
  if(len>255) len = 255; // don't let it go longer that the receive buffer in the display

  Wire.beginTransmission(DISPLAY_ADDR);
  Wire.write(0x40);  // set the scroll mode
  Wire.write(byte(len));  // set the scroll mode
  for(int i=0;i<len;i++){
    Wire.write(string[i]);
  }
  
  return (Wire.endTransmission() == 0);
}


