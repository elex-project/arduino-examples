#include <avr/wdt.h>

void setup() {
 wdt_disable(); // 셋업 중에는 워치독 사용을 중지한다.
  Serial.begin(9600);
  Serial.println("setup()");
  wdt_enable(WDTO_4S);
}

void loop() {
  wdt_reset(); // 워치독 타이머를 리셋한다.
  //wdt_reset();
  unsigned long currentMillis = millis();
  Serial.println(currentMillis);
  if (currentMillis>10000) {
    
    while(1){
      Serial.println("delay... ");
      delay(1000);
    }
  }

  
  Serial.println("loop()");

  delay(1000);
}
