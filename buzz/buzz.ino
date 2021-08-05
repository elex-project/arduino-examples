
#include "muze.h"

#define PIN_BUZZ 3

unsigned long last_time_millis, current_time_millis;

Muze muze = Muze(PIN_BUZZ);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_BUZZ, OUTPUT);

  Serial.begin(115200);
  last_time_millis = millis();

  muze.setScore(GREEN_SLEEVES);
}

void loop() {
  current_time_millis = millis();
  if (current_time_millis < last_time_millis) {
    last_time_millis = current_time_millis;
    return;
  }

  muze.play();

  last_time_millis = current_time_millis;
}

