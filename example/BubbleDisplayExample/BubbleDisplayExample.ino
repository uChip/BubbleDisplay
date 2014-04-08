
#include <Wire.h>

#define DISPLAY_ADDR 4

uint8_t sendBuff[] = {0x40, 26, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
//uint8_t sendBuff[] = {0x40, 26, 'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N', 'M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};

void setup() {
  Serial.begin(115200);

delay(5000);

  Serial.println ();
  Serial.println ("Preparing to send...");
  byte count = 0;
  
  Wire.begin();
  TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz
  //TWBR = 78;  // 25 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler
  //TWBR = 158;  // 12.5 kHz 
  //TWSR |= _BV (TWPS0);  // change prescaler

  Wire.beginTransmission(DISPLAY_ADDR);
  for(int i=0;i<28;i++){
    Wire.write(sendBuff[i]);
  }
  if (Wire.endTransmission() == 0){
    Serial.println("Success!");
  }

}  // end of setup

void loop() {
Serial.println ("Loop.");
delay(20000);
}
