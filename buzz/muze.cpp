#include "Arduino.h"
#include "muze.h"

#define GAP_BETWEEN_NOTES 5

Melody _green_sleeves[] = {
  {NOTE_G5, NOTE_LEN_8},
  {NOTE_B5_F, NOTE_LEN_4}, {NOTE_C6, NOTE_LEN_8}, {NOTE_D6, NOTE_LEN_8_DOT}, {NOTE_E6, NOTE_LEN_16}, {NOTE_D6, NOTE_LEN_8},
  {NOTE_C6, NOTE_LEN_4}, {NOTE_A5, NOTE_LEN_8}, {NOTE_F5, NOTE_LEN_8_DOT}, {NOTE_G5, NOTE_LEN_16}, {NOTE_A5, NOTE_LEN_8},
  {NOTE_B5_F, NOTE_LEN_4}, {NOTE_G5, NOTE_LEN_8}, {NOTE_G5, NOTE_LEN_8_DOT}, {NOTE_F5_S, NOTE_LEN_16}, {NOTE_G5, NOTE_LEN_8},
  {NOTE_A5, NOTE_LEN_4}, {NOTE_F5_S, NOTE_LEN_8}, {NOTE_D5, NOTE_LEN_4}, {NOTE_G5, NOTE_LEN_8},

  {NOTE_B5_F, NOTE_LEN_4}, {NOTE_C6, NOTE_LEN_8}, {NOTE_D6, NOTE_LEN_8_DOT}, {NOTE_E6, NOTE_LEN_16}, {NOTE_D6, NOTE_LEN_8},
  {NOTE_C6, NOTE_LEN_4}, {NOTE_A5, NOTE_LEN_8}, {NOTE_F5, NOTE_LEN_8_DOT}, {NOTE_G5, NOTE_LEN_16}, {NOTE_A5, NOTE_LEN_8},
  {NOTE_B5_F, NOTE_LEN_8_DOT}, {NOTE_A5, NOTE_LEN_16}, {NOTE_G5, NOTE_LEN_8}, {NOTE_F5_S, NOTE_LEN_8_DOT}, {NOTE_E5, NOTE_LEN_16}, {NOTE_F5_S, NOTE_LEN_8},
  {NOTE_G5, NOTE_LEN_2_DOT},

  {NOTE_F6, NOTE_LEN_4_DOT}, {NOTE_F6, NOTE_LEN_8_DOT}, {NOTE_E6, NOTE_LEN_16}, {NOTE_D6, NOTE_LEN_8},
  {NOTE_C6, NOTE_LEN_4}, {NOTE_A5, NOTE_LEN_8}, {NOTE_F5, NOTE_LEN_8_DOT}, {NOTE_G5, NOTE_LEN_16}, {NOTE_A5, NOTE_LEN_8},
  {NOTE_B5_F, NOTE_LEN_4}, {NOTE_G5, NOTE_LEN_8}, {NOTE_G5, NOTE_LEN_8_DOT}, {NOTE_F5_S, NOTE_LEN_16}, {NOTE_G5, NOTE_LEN_8},
  {NOTE_A5, NOTE_LEN_4}, {NOTE_F5_S, NOTE_LEN_8}, {NOTE_D5, NOTE_LEN_4_DOT}, 

  {NOTE_F6, NOTE_LEN_4_DOT}, {NOTE_F6, NOTE_LEN_8_DOT}, {NOTE_E6, NOTE_LEN_16}, {NOTE_D6, NOTE_LEN_8},
  {NOTE_C6, NOTE_LEN_4}, {NOTE_A5, NOTE_LEN_8}, {NOTE_F5, NOTE_LEN_8_DOT}, {NOTE_G5, NOTE_LEN_16}, {NOTE_A5, NOTE_LEN_8},
  {NOTE_B5_F, NOTE_LEN_8_DOT}, {NOTE_A5, NOTE_LEN_16}, {NOTE_G5, NOTE_LEN_8}, {NOTE_F5_S, NOTE_LEN_8_DOT}, {NOTE_E5, NOTE_LEN_16}, {NOTE_F5_S, NOTE_LEN_8},
  {NOTE_G5, NOTE_LEN_2_DOT}
};

Melody _minions[] = {
  {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_4}, {NOTE_G3, NOTE_LEN_16}, {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_16}, {NOTE_G3, NOTE_LEN_4},
  {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_4}, {NOTE_G3, NOTE_LEN_16}, {NOTE_G3, NOTE_LEN_8}, {NOTE_G3, NOTE_LEN_16}, {NOTE_A5, NOTE_LEN_8}, {NOTE_B5, NOTE_LEN_8},

};

Muze::Muze(int pin){
  pinMode(pin, OUTPUT);
  _pin = pin;
}

Muze::Muze(int pin, Score score){
  pinMode(pin, OUTPUT);
  _pin = pin;
  setScore(score);
}

boolean Muze::play(){
  _current_ts = millis();

  if (_current_ts > _next_ts) {
    if (_cue < _melody_size) {
      _buzz();
      _isPlaying = true;
    } else {
      noTone(_pin);
      _isPlaying = false;
    }
  }
  return isPlaying();
}

void Muze::setTempo(unsigned int tempo){
  _tempo = tempo;
}

void Muze::setScore(Score score){
  switch (score){
    
    case MINIONS_0:
      break;
      
    case GREEN_SLEEVES:
    default:
      _melody = _green_sleeves;
      _melody_size = sizeof(_green_sleeves) / sizeof(Melody);
      _tempo = 100;
      break;
  }
  
  _cue = 0;
  _next_ts = 0;
  _isPlaying = false;
}

bool Muze::isPlaying(){
  return _isPlaying;
}

void Muze::_buzz() {
  
  long duration = _duration(_melody[_cue].len);
  tone(_pin, _melody[_cue].pitch, duration-GAP_BETWEEN_NOTES);
  _next_ts = _current_ts + duration;
  _cue ++;
  
}

unsigned long Muze::_duration(unsigned long len) {
  return len  * 60000 / _tempo / NOTE_LEN_4;
}


