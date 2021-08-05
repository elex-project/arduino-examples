# include "crc16.h"

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  byte array[] = {0x7e, 0x01, 0x01, 0x00, 0x00};
  unsigned int crc16 = crc(array, 3);

  byte high = highByte(crc16);
  byte low = lowByte(crc16);
  
  Serial.print(crc16, HEX); Serial.print(" = ");
  Serial.print(high, HEX); Serial.print(" ");
  Serial.println(low, HEX);
  delay(5000);
}
