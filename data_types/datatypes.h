#ifndef DataTypes_h
#define DataTypes_h
#include "Arduino.h"

#define INT1_MAX = 0x7f;
#define INT1_MIN = 0x80;
#define UINT1_MAX = 0xff;
#define UINT1_MIN = 0x00;

#define INT2_MAX = 0x7fff;
#define INT2_MIN = 0x8000;
#define UINT2_MAX = 0xffff;
#define UINT2_MIN = 0x0000;

#define INT4_MAX = 0x7fffffffL;
#define INT4_MIN = 0x80000000L;
#define UINT4_MAX = 0xffffffffL;
#define UINT4_MIN = 0x00000000L;

#define INT8_MAX = 0x7fffffffffffffffLL;
#define INT8_MIN = 0x8000000000000000LL;
#define UINT8_MIN = 0xffffffffffffffffULL;
#define UINT8_MIN = 0x0000000000000000ULL;

/*
 * IEEE754 float layout; 
 * 
 * Single Precision
 * 부호 : 1 bit
 * 지수(exponent) : 8 bit
 * 가수(mentissa) : 23 bit
 */
struct IEEEsingle{
    uint32_t mentissa:23; 
    uint8_t exponent:8;
    uint8_t sign:1;
};

// IEEE754 double layout; 
struct IEEEdouble {
    uint32_t filler:29; // it is only able to map 23 bits of the mantisse a filler is added for the remaining bits.
    uint32_t mentissa:23; 
    uint16_t exponent:11;
    uint8_t sign:1;
};

/**
 * 
 * 자료형 ==============================================================================
 * 
 * 연산을 할 때에는 value를 사용.
 * 바이트 배열을 처리할 때에는 bytes를 사용.
 * bytes는 LowByte가 먼저이므로 주의.
 * 
 * TODO
 * 클래스로 처리하고, 상속 구조로 바꾸면 더 편해질 것 같지만, C++ 쓸 줄 모름.
 * 연산자 오버로딩의 경우에도 쉬운 방법이 있을 것 같지만, 능력 부족.
 * 
 */
typedef union Int8 {
  byte bytes[8];
  long long value;
} Int8;

typedef union UInt8 {
  byte bytes[8];
  unsigned long long value;
} UInt8;

typedef union Int4 {
  byte bytes[4];
  long value;
} Int4;

typedef union UInt4 {
  byte bytes[4];
  unsigned long value;
} UInt4;

typedef union Int2 {
  byte bytes[2];
  int value;
} Int2;

typedef union UInt2 {
  byte bytes[2];
  unsigned int value;
} UInt2;

typedef union Int1 {
  byte bytes[1];
  char value;
} Int1;

typedef union UInt1 {
  byte bytes[1];
  byte value;
} UInt1;


typedef union Float4 {
  byte bytes[4];
  float value; // 4 bytes
  IEEEsingle p;
} Float4;

typedef union Float8 { // double->float 변환용으로만 사용한다.
  byte bytes[8];
  double value; // 4 bytes
  IEEEdouble p;
} Float8;

/**
 * 
 * Constructors ==========================================================
 * 
 */

Int1 new_Int1(char val);
Int2 new_Int2(int val);
Int4 new_Int4(long val);
Int8 new_Int8(long long val);

UInt1 new_UInt1(byte val);
UInt2 new_UInt2(unsigned int val);
UInt4 new_UInt4(unsigned long val);
UInt8 new_UInt8(unsigned long long val);

Float4 new_Float4(float val);
//Float8 new_Float8(double val);

Int1 new_Int1(byte arr[]);
Int2 new_Int2(byte arr[]);
Int4 new_Int4(byte arr[]);
Int8 new_Int8(byte arr[]);

/*
 * arr : 맨 왼쪽부터 순서대로라고 가정한다.
 * startIdx : arr 배열에서 값을 읽어올 시작 위치 인덱스
 */
Int1 new_Int1(byte arr[], int startIdx);
Int2 new_Int2(byte arr[], int startIdx);
Int4 new_Int4(byte arr[], int startIdx);
Int8 new_Int8(byte arr[], int startIdx);

UInt1 new_UInt1(byte arr[]);
UInt2 new_UInt2(byte arr[]);
UInt4 new_UInt4(byte arr[]);
UInt8 new_UInt8(byte arr[]);

UInt1 new_UInt1(byte arr[], int startIdx);
UInt2 new_UInt2(byte arr[], int startIdx);
UInt4 new_UInt4(byte arr[], int startIdx);
UInt8 new_UInt8(byte arr[], int startIdx);

Float4 new_Float4(byte arr[]);
Float8 new_Float8(byte arr[]);

Float4 new_Float4(byte arr[], int startIdx);
Float8 new_Float8(byte arr[], int startIdx);

/*
 * IEEE754 배정도 부동소수를 단정도 부동소수로 변환.
 * 
 * array : IEEE 배정도 부동소수 (8바이트). 
 * 부호비트가 맨 왼쪽에 있다고 본다. 아니라면, 뒤집어서 입력할 것.
 */
Float4 conv_double_to_float(byte array[]);
Float4 conv_double_to_float(Float8 val);

/**
 * 
 * Operators ========================================================================
 * 
 * 경우의 수가 너무 많으므로 필요할 때마다 추가해야할 듯.
 * template 같은 걸 쓰면 될 것 같은데, 어떻게 쓰는건지 모르겠음.
 * 또는, .value를 사용해서 연산하는데 편할 듯.
 */

Int1 operator+(const Int1& a, const Int1& b);
Int2 operator+(const Int1& a, const int b);
Int2 operator+(const int a, const Int1& b);
Int2 operator+(const Int2& a, const Int2& b);
Int2 operator+(const Int2& a, const int b);
Int2 operator+(const int a, const Int2& b);

/**
 * 
 * To HEX String ======================================================
 * 
 */

// HighByte가 먼저 출력됨.
String toHexString(Int1 value);
String toHexString(Int2 value);
String toHexString(Int4 value);
String toHexString(Int8 value);

String toHexString(UInt1 value);
String toHexString(UInt2 value);
String toHexString(UInt4 value);
String toHexString(UInt8 value);

String toHexString(Float4 value);
//String toHexString(Float8 value);

// doNotRev :  true이면 LowByte가 먼저 출력됨.
String toHexString(Int1 value, bool doNotRev);
String toHexString(Int2 value, bool doNotRev);
String toHexString(Int4 value, bool doNotRev);
String toHexString(Int8 value, bool doNotRev);

String toHexString(UInt1 value, bool doNotRev);
String toHexString(UInt2 value, bool doNotRev);
String toHexString(UInt4 value, bool doNotRev);
String toHexString(UInt8 value, bool doNotRev);

String toHexString(Float4 value, bool doNotRev);
//String toHexString(Float8 value, bool doNotRev);

/**
 * 
 * To String ======================================================
 * 
 */

String toString(Int1 value);
String toString(Int2 value);
String toString(Int4 value);
String toString(Int8 value);

String toString(UInt1 value);
String toString(UInt2 value);
String toString(UInt4 value);
String toString(UInt8 value);

/*
   decimalPlace : 소수점 이하 자릿수
 */
String toString(Float4 value, int decimalPlace);
String toString(Float4 value);
//String toString(Float8 value, int decimalPlace);
//String toString(Float8 value);

/**
 * 
 * Utilities ======================================================
 * 
 */

/*
  바이트 배열을 16진수 문자열로.
  array : 원본 배열
  len : 배열 길이
*/
String array_to_string(byte array[], unsigned int len);

/*
  바이트 배열의 순서를 뒤집기.
  array : 원본 배열
  len : 배열 길이
  result : 뒤집힌 배열이 저장될 새로운 배열
*/
void array_reverse(byte array[], unsigned int len, byte result[]);

#endif
