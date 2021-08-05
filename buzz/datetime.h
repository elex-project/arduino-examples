#ifndef Elex_DateTime_lib
#define Elex_DateTime_lib

#include "Arduino.h"

#define MAX_UL 0xfffffffful

class DateTime {
  public:
  /*
   * 매 루프마다 반복 실행해 줄 것.
   */
    void update();
    /**
     * 현재 시간 설정 (초)
     * 기준 시간은 알아서 정할 것.
     */
    void set(unsigned long sec_since_epoch);
    /*
     * 현재 시간 (초)
     */
    unsigned long get();
  private:
    // 시간 값이 설정된 기준 시간. 오버플로가 발생한 때에도 업데이트된다.
    unsigned long _set_time;
    // 기준 시간 이후 경과한 시간 (밀리초)
    unsigned long _elapsed_ms_after_set_time;
    // 매 루프마다 업데이트됨.
    unsigned long _current_ts, _last_ts;
};

#endif
