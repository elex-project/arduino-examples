#ifndef Elex_Muze_lib
#define Elex_Muze_lib

#include "Arduino.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_C1_S 35
#define NOTE_D1_F 35
#define NOTE_D1  37
#define NOTE_D1_S 39
#define NOTE_E1_S 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_F1_S 46
#define NOTE_G1_F 46
#define NOTE_G1  49
#define NOTE_G1_S 52
#define NOTE_A1_F 52
#define NOTE_A1  55
#define NOTE_A1_S 58
#define NOTE_B1_F 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_C2_S 69
#define NOTE_D2_F 69
#define NOTE_D2  73
#define NOTE_D2_S 78
#define NOTE_E2_F 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_F2_S 93
#define NOTE_G2_F 93
#define NOTE_G2  98
#define NOTE_G2_S 104
#define NOTE_A2_F 104
#define NOTE_A2  110
#define NOTE_A2_S 117
#define NOTE_B2_F 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_C3_S 139
#define NOTE_D3_F 139
#define NOTE_D3  147
#define NOTE_D3_S 156
#define NOTE_E3_F 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_F3_S 185
#define NOTE_G3_F 185
#define NOTE_G3  196
#define NOTE_G3_S 208
#define NOTE_A3_F 208
#define NOTE_A3  220
#define NOTE_A3_S 233
#define NOTE_B3_F 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_C4_S 277
#define NOTE_D4_F 277
#define NOTE_D4  294
#define NOTE_D4_S 311
#define NOTE_E4_F 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_F4_S 370
#define NOTE_G4_F 370
#define NOTE_G4  392
#define NOTE_G4_S 415
#define NOTE_A4_F 415
#define NOTE_A4  440
#define NOTE_A4_S 466
#define NOTE_B4_F 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_C5_S 554
#define NOTE_D5_F 554
#define NOTE_D5  587
#define NOTE_D5_S 622
#define NOTE_E5_F 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_F5_S 740
#define NOTE_G5_F 740
#define NOTE_G5  784
#define NOTE_G5_S 831
#define NOTE_A5_F 831
#define NOTE_A5  880
#define NOTE_A5_S 932
#define NOTE_B5_F 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_C6_S 1109
#define NOTE_D6_F 1109
#define NOTE_D6  1175
#define NOTE_D6_S 1245
#define NOTE_E6_F 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_F6_S 1480
#define NOTE_G6_F 1480
#define NOTE_G6  1568
#define NOTE_G6_S 1661
#define NOTE_A6_F 1661
#define NOTE_A6  1760
#define NOTE_A6_S 1865
#define NOTE_B6_F 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_C7_S 2217
#define NOTE_D7_F 2217
#define NOTE_D7  2349
#define NOTE_D7_S 2489
#define NOTE_E7_F 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_F7_S 2960
#define NOTE_G7_F 2960
#define NOTE_G7  3136
#define NOTE_G7_S 3322
#define NOTE_A7_F 3322
#define NOTE_A7  3520
#define NOTE_A7_S 3729
#define NOTE_B7_F 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_C8_S 4435
#define NOTE_D8_F 4435
#define NOTE_D8  4699
#define NOTE_D8_S 4978

#define NOTE_REST 0

#define NOTE_LEN_4 720
#define NOTE_LEN_2 1440 // NOTE_LEN_4 * 2
#define NOTE_LEN_1 2880 // NOTE_LEN_4 * 4
#define NOTE_LEN_8 360 // NOTE_LEN_4 / 2
#define NOTE_LEN_16 180 // NOTE_LEN_4 / 4
#define NOTE_LEN_32 90 // NOTE_LEN_4 / 8

#define NOTE_LEN_2_DOT 2160 // NOTE_LEN_2 * 1.5
#define NOTE_LEN_4_DOT 1080 // NOTE_LEN_4 * 1.5
#define NOTE_LEN_8_DOT 540 // NOTE_LEN_8 * 1.5
#define NOTE_LEN_16_DOT 270 // NOTE_LEN_16 * 1.5
#define NOTE_LEN_32_DOT 135 // NOTE_LEN_32 * 1.5

#define NOTE_LEN_4_TRIPLET 240 // NOTE_LEN_4 / 3
#define NOTE_LEN_8_TRIPLET 120 // NOTE_LEN_8 / 3
#define NOTE_LEN_16_TRIPLET 60 // NOTE_LEN_16 / 3
#define NOTE_LEN_32_TRIPLET 30 // NOTE_LEN_32 / 3
/*
   재생 가능한 곡 리스트
*/
typedef enum _Score {
  GREEN_SLEEVES = 0,
  MINIONS_0,
} Score;

/*
   음의 높이와 길이
*/
typedef struct _Melody {
  unsigned int pitch;
  unsigned int len;
} Melody;

/*
   노래하는 클래스
*/
class Muze {
  public:
    // 핀 번호
    Muze(int pin);
    // 핀 번호, 재생할 곡
    Muze(int pin, Score score);

  public:
    // 메인 루프에서 호출하면 재생된다.
    boolean play();
    // 곡의 빠르기를 지정
    void setTempo(unsigned int tempo);
    // 재생할 곡을 선
    void setScore(Score score);
    // 재생 중인가?
    bool isPlaying();

  private:
    // 핀 번호
    int _pin;
    // 음표 데이터 배열
    Melody* _melody;
    // 데이터의 크기
    unsigned int _melody_size;
    // 템포
    unsigned int _tempo = 100;
    // 데이터의 현재 재생 인덱스
    unsigned int _cue = 0;
    // 현재 시간, 다음 재생 이벤트 발생 시간
    unsigned long _current_ts = 0, _next_ts = 0;
    // 재생 중?
    bool _isPlaying;
    // 소리 발생
    void _buzz();
    // 재생 시간 계산
    unsigned long _duration(unsigned long len);
};

#endif

