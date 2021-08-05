#include "Arduino.h"
#include "datetime.h"

unsigned long DateTime::get(){
  return _set_time + _elapsed_ms_after_set_time/1000;
}

void DateTime::set(unsigned long sec_since_epoch){
  _set_time = sec_since_epoch;
  _elapsed_ms_after_set_time = 0;
}

void DateTime::update(){
  _current_ts = millis();
  if (_current_ts < _last_ts) {
    _set_time = _set_time + _elapsed_ms_after_set_time/1000;
    _elapsed_ms_after_set_time = _current_ts + (MAX_UL - _last_ts);

  } else {
    _elapsed_ms_after_set_time += _current_ts;
    
  }  

  _last_ts = _current_ts;
}
