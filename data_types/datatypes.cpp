#include "Arduino.h"
#include "datatypes.h"

#define INT8_CHAR_BUFF_SIZE 21
#define DECIMAL_PLACE 6

/*
  바이트 배열을 역순으로
*/
void array_reverse(byte array[], unsigned int len, byte result[]){
  for (int i=0; i<len;i++){
    result[i] = array[len-1-i];
  }
}

/*
  캐릭터 배열을 역순으로.
  len번째 요소에 널문자가 삽입됨.
*/
void char_array_reverse(char array[], unsigned int len, char result[]){  
  for (int i=0; i<len;i++){
    result[i] = array[len-1-i];
  }
  result[len]='\0';
}

/*
   바이트 배열을 16진 문자열로.
*/
String array_to_string(byte array[], unsigned int len){
  char result[len*2+1];
  for (unsigned int i = 0; i < len; i++) {
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    result[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
    result[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
  }
  result[len * 2] = '\0';
  return String(result);
}

/*
 * IEEE double procision을 single precision으로 변환.
 * 
 * https://github.com/RobTillaart/Arduino/blob/master/libraries/IEEE754tools/IEEE754tools.h
 */
Float4 conv_double_to_float(byte array[]){
  Float4 fl;
  Float8 dbl;
  
  for (int i=0; i<8; i++){
      //dbl.bytes[i] = array[i];
      dbl.bytes[i] = array[7-i];
  }
  
  int exponent = dbl.p.exponent-1023 +127; // exponent adjust
  // TODO check exponent overflow.
  if (exponent >=0 || exponent <= 255) {
        fl.p.sign = dbl.p.sign;
        fl.p.exponent = exponent;  
        fl.p.mentissa = dbl.p.mentissa;  // note this one clips the mantisse 
        return fl;
    }
    return fl; // error
}

Float4 conv_double_to_float(Float8 val){
  byte temp[8];
  array_reverse(val.bytes, 8, temp);
  return conv_double_to_float(temp);
}

// to String =====================================================================

String toString(Int1 value){
  return String((int)value.value);
}

String toString(UInt1 value){
  return String(value.value);
}

String toString(Int2 value){
  return String(value.value);
}

String toString(UInt2 value){
  return String(value.value);
}

String toString(Int4 value){
  return String(value.value);
}

String toString(UInt4 value){
  return String(value.value);
}

String toString(Int8 value){
  int m;
  int i=0;
  long long tmp = value.value;
  char buff[INT8_CHAR_BUFF_SIZE], rev_buff[INT8_CHAR_BUFF_SIZE];
  bool isMinus = tmp<0;
  if (isMinus){
    // 값이 음수인 경우, 
    // 문자열에 부호를 추가하고, -1을 곱해서 양수로 만든 다음 나머지 작업을 한다.
    // 부호 추가는 맨 뒤에.
    tmp *=-1;
  }
  while (tmp/10>0) {
    m = tmp%10;
    buff[i]=(char)(m+0x30);
    tmp /= 10;    
    i++;
  }
  buff[i]=(char)(tmp+0x30);
  if (isMinus){
    i++;
    buff[i] = '-'; // 부호를 추가
  }
  //buff[i+1] = '\0';
  
  //char arr[i+1];
  char_array_reverse(buff, i+1, rev_buff);
  rev_buff[i+1] = '\0';
  return String(rev_buff);
}

String toString(UInt8 value){
  int m;
  int i=0;
  unsigned long long tmp = value.value;
  char buff[INT8_CHAR_BUFF_SIZE], rev_buff[INT8_CHAR_BUFF_SIZE];
  while (tmp/10>0) {
    m = tmp%10;
    buff[i]=(char)(m+0x30);
    tmp /= 10;    
    i++;
  }
  buff[i]=(char)(tmp+0x30);
  //buff[i+1] = '\0';

  //char arr[i+1];
  char_array_reverse(buff, i+1, rev_buff);
  rev_buff[i+1] = '\0';
  return String(rev_buff);
}

String toString(Float4 value){
  return toString(value, DECIMAL_PLACE);
}

String toString(Float4 value, int decimalPlace){
  return String(value.value, decimalPlace);
}

//String toString(Float8 value){
//  return toString(value, DECIMAL_PLACE);
//}

//String toString(Float8 value, int decimalPlace){
//  return String(value.value, decimalPlace);
//}

// to HEX String ===============================================================================

String toHexString(Int1 value){
  return array_to_string(value.bytes, 1);
}

String toHexString(UInt1 value){
  return array_to_string(value.bytes, 1);
}

String toHexString(Int2 value){
  byte rev_arr[2];
  array_reverse(value.bytes, 2, rev_arr);
  return array_to_string(rev_arr, 2);
}

String toHexString(UInt2 value){
  byte rev_arr[2];
  array_reverse(value.bytes, 2, rev_arr);
  return array_to_string(rev_arr, 2);
}

String toHexString(Int4 value){
  byte rev_arr[4];
  array_reverse(value.bytes, 4, rev_arr);
  return array_to_string(rev_arr, 4);
}

String toHexString(UInt4 value){
  byte rev_arr[4];
  array_reverse(value.bytes, 4, rev_arr);
  return array_to_string(rev_arr, 4);
}

String toHexString(Int8 value){
  byte rev_arr[8];
  array_reverse(value.bytes, 8, rev_arr);
  return array_to_string(rev_arr, 8);
}

String toHexString(UInt8 value){
  byte rev_arr[8];
  array_reverse(value.bytes, 8, rev_arr);
  return array_to_string(rev_arr, 8);
}

String toHexString(Float4 value){
  byte rev_arr[4];
  array_reverse(value.bytes, 4, rev_arr);
  return array_to_string(rev_arr, 4);
}

//String toHexString(Float8 value){
//  byte rev_arr[8];
//  array_reverse(value.bytes, 8, rev_arr);
//  return array_to_string(rev_arr, 8);
//}

String toHexString(Int1 value, bool doNotRev){
  return toHexString(value);
}

String toHexString(UInt1 value, bool doNotRev){
  return toHexString(value);
}

String toHexString(Int2 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 2);
  } else {
    return toHexString(value);
  }
}

String toHexString(UInt2 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 2);
  } else {
    return toHexString(value);
  }
}

String toHexString(Int4 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 4);
  } else {
    return toHexString(value);
  }
}

String toHexString(UInt4 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 4);
  } else {
    return toHexString(value);
  }
}

String toHexString(Int8 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 8);
  } else {
    return toHexString(value);
  }
}

String toHexString(UInt8 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 8);
  } else {
    return toHexString(value);
  }
}

String toHexString(Float4 value, bool doNotRev){
  if (doNotRev){
    return array_to_string(value.bytes, 4);
  } else {
    return toHexString(value);
  }
}

//String toHexString(Float8 value, bool doNotRev){
//  if (doNotRev){
//    return array_to_string(value.bytes, 8);
//  } else {
//    return toHexString(value);
//  }
//}

// Constructors =========================================================================
Int1 new_Int1(byte arr[]){
  return new_Int1(arr, 0);
}

Int1 new_Int1(byte arr[], int startIdx){
  Int1 v;
  v.bytes[0] = arr[startIdx];
  return v;
}

UInt1 new_UInt1(byte arr[]){
  return new_UInt1(arr, 0);
}

UInt1 new_UInt1(byte arr[], int startIdx){
  UInt1 v;
  v.bytes[0] = arr[startIdx];
  return v;
}

Int2 new_Int2(byte arr[]){
  return new_Int2(arr, 0);
}

Int2 new_Int2(byte arr[], int startIdx){
  Int2 v;
  for (int i=0; i<2; i++) {
    v.bytes[i] = arr[startIdx + 2-1-i];
  }  
  return v;
}

UInt2 new_UInt2(byte arr[]){
  return new_UInt2(arr, 0);
}

UInt2 new_UInt2(byte arr[], int startIdx){
  UInt2 v;
  for (int i=0; i<2; i++) {
    v.bytes[i] = arr[startIdx + 2-1-i];
  }  
  return v;
}

Int4 new_Int4(byte arr[]){
  return new_Int4(arr, 0);
}

Int4 new_Int4(byte arr[], int startIdx){
  Int4 v;
  for (int i=0; i<4; i++) {
    v.bytes[i] = arr[startIdx + 4-1-i];
  }  
  return v;
}

UInt4 new_UInt4(byte arr[]){
  return new_UInt4(arr, 0);
}

UInt4 new_UInt4(byte arr[], int startIdx){
  UInt4 v;
  for (int i=0; i<4; i++) {
    v.bytes[i] = arr[startIdx + 4-1-i];
  }  
  return v;
}

Int8 new_Int8(byte arr[]){
  return new_Int8(arr, 0);
}

Int8 new_Int8(byte arr[], int startIdx){
  Int8 v;
  for (int i=0; i<8; i++) {
    v.bytes[i] = arr[startIdx + 8-1-i];
  }  
  return v;
}

UInt8 new_UInt8(byte arr[]){
  return new_UInt8(arr, 0);
}

UInt8 new_UInt8(byte arr[], int startIdx){
  UInt8 v;
  for (int i=0; i<8; i++) {
    v.bytes[i] = arr[startIdx + 8-1-i];
  }  
  return v;
}

Float4 new_Float4(byte arr[]){
  return new_Float4(arr, 0);
}

Float4 new_Float4(byte arr[], int startIdx){
  Float4 v;
  for (int i=0; i<4; i++) {
    v.bytes[i] = arr[startIdx + 4-1-i];
  }  
  return v;
}

Float8 new_Float8(byte arr[]){
  return new_Float8(arr, 0);
}

Float8 new_Float8(byte arr[], int startIdx){
  Float8 v;
  for (int i=0; i<8; i++) {
    v.bytes[i] = arr[startIdx + 8-1-i];
  }  
  return v;
}

Int1 new_Int1(char val){
  Int1 v;
  v.value = val;
  return v;
}

Int2 new_Int2(int val){
  Int2 v;
  v.value = val;
  return v;
}

Int4 new_Int4(long val){
  Int4 v;
  v.value = val;
  return v;
}

Int8 new_Int8(long long val){
  Int8 v;
  v.value = val;
  return v;
}

UInt1 new_UInt1(byte val){
  UInt1 v;
  v.value = val;
  return v;
}

UInt2 new_UInt2(unsigned int val){
  UInt2 v;
  v.value = val;
  return v;
}

UInt4 new_UInt4(unsigned long val){
  UInt4 v;
  v.value = val;
  return v;
}

UInt8 new_UInt8(unsigned long long val){
  UInt8 v;
  v.value = val;
  return v;
}

Float4 new_Float4(float val){
  Float4 v;
  v.value = val;
  return v;
}

//Float8 new_Float8(double val){
//  Float8 v;
//  v.value = val;
//  return v;
//}

// 연산자 오버로딩 ========================================================================

Int1 operator+(const Int1& a, const Int1& b){
  Int1 val;
  val.value = a.value + b.value;
  return val;
}

Int2 operator+(const Int1& a, const int b){
  Int2 val;
  val.value = a.value + b;
  return val;
}

Int2 operator+(const int a, const Int1& b){
  Int2 val;
  val.value = a + b.value;
  return val;
}

Int2 operator+(const Int2& a, const Int2& b){
  Int2 val;
  val.value = a.value + b.value;
  return val;
}

Int2 operator+(const Int2& a, const int b){
  Int2 val;
  val.value = a.value + b;
  return val;
}

Int2 operator+(const int a, const Int2& b){
  Int2 val;
  val.value = a + b.value;
  return val;
}
