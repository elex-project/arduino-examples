#include "datatypes.h"

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
}

void loop() {
  Int1 i1;
  i1.value = 255;
  print_test("Int1", toHexString(i1), toString(i1), sizeof(i1));
  
  UInt1 u1;
  u1.value = 255;
  print_test("UInt1", toHexString(u1), toString(u1), sizeof(u1));
  

  Int2 i2;
  i2.value = -5536;
  print_test("Int2", toHexString(i2), toString(i2), sizeof(i2));

  UInt2 u2;
  u2.value = 60000;
  print_test("UInt2", toHexString(u2), toString(u2), sizeof(u2));


  Int4 i4;
  i4.value = 0xf0e0d0c0;
  print_test("Int4", toHexString(i4), toString(i4), sizeof(i4));

  UInt4 u4;
  u4.value = 0xf0e0d0c0;
  print_test("UInt4", toHexString(u4), toString(u4), sizeof(u4));


  Int8 i8 = new_Int8(500);
  print_test("Int8", toHexString(i8), toString(i8), sizeof(i8));
  i8.value = 0xF0000000F0E0D0C0;
  print_test("Int8", toHexString(i8), toString(i8), sizeof(i8));

  UInt8 u8;
  u8.value = 0xF0000000F0E0D0C0;
  u8.value *= 300;
  print_test("UInt8", toHexString(u8), toString(u8), sizeof(u8));


  Float4 f4;
  f4.value = 3.141592;
  print_test("Float4", toHexString(f4), toString(f4), sizeof(f4));

  
  /*
   * double -> float
   */
  byte ieee[8] = { // 3.141592
    0x40, 0x09, 0x21, 0xfa, 0xfc, 0x8b, 0x00, 0x7a
  };
  f4 = conv_double_to_float(ieee);
  print_test("Double -> Float4", toHexString(f4), toString(f4), sizeof(f4));

  i2 = new_Int2(ieee, 2); // 0x21fa
  print_test("Int2 from byte[]", toHexString(i2), toString(i2), sizeof(i2));

  /*
   * Operator
   */
  Int1 _i1;
  _i1.value = -100;
  i1 = i1+_i1;
  print_test("Int1 + Int1", toHexString(i1), toString(i1), sizeof(i1));

  i2 = 10+i1+100;
  print_test("Int1 + int", toHexString(i2), toString(i2), sizeof(i2));

  //Serial.println(crc(ieee, 2));
  //Int8 as = new_Int8(500);
  
  delay(5000);
}

void print_test(String tag, String hexStr, String val, int size){
  Serial.print(tag); Serial.print(" ("); Serial.print(size); Serial.print(")\n");
  Serial.print("\t"); Serial.print(hexStr); Serial.print("\t"); Serial.print(val);
  Serial.println("\n");
}
