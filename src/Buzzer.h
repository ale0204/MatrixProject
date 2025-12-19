#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

namespace MusicNotes {
    constexpr uint16_t C4  = 262;
    constexpr uint16_t D4  = 294;
    constexpr uint16_t E4  = 330;
    constexpr uint16_t F4  = 349;
    constexpr uint16_t G4  = 392;
    constexpr uint16_t A4  = 440;
    constexpr uint16_t B4  = 494;
    
    constexpr uint16_t C5  = 523;
    constexpr uint16_t D5  = 587;
    constexpr uint16_t E5  = 659;
    constexpr uint16_t F5  = 698;
    constexpr uint16_t G5  = 784;
    constexpr uint16_t A5  = 880;
    constexpr uint16_t B5  = 988;
    
    constexpr uint16_t LOW_TONE    = 200;
    constexpr uint16_t MEDIUM_TONE = 800;
    constexpr uint16_t HIGH_TONE   = 2000;
}

namespace NoteDurations {
    constexpr uint16_t VERY_SHORT = 50;
    constexpr uint16_t SHORT      = 100;
    constexpr uint16_t MEDIUM     = 150;
    constexpr uint16_t LONG       = 250;
    constexpr uint16_t VERY_LONG  = 400;
    
    constexpr uint16_t PAUSE_SHORT  = 50;
    constexpr uint16_t PAUSE_MEDIUM = 100;
    constexpr uint16_t PAUSE_LONG   = 200;
}

enum class BuzzerPattern : uint8_t {
    MENU_BEEP,
    MENU_SELECT,
    
    COLLECT_GOLD,
    LEVEL_COMPLETE,
    GAME_WON,
    
    HIT_WALL,
    HIT_BOMB,
    GAME_OVER,
    
    ROOM_TRANSITION,
    ALARM_SIREN,
    CONTINUOUS
};

class Buzzer {
private:
    const uint8_t pin;
    static constexpr uint16_t SIREN_INTERVAL = 300;
    
    BuzzerPattern currentPattern;
    uint32_t patternStartTime;
    uint32_t lastUpdateTime;
    uint32_t patternDuration;
    uint16_t patternState;
    uint16_t currentTone;
    bool isActive;
    
    void playToneInternal(uint16_t frequency, uint16_t durationMs = 0);

public:
    Buzzer(uint8_t buzzerPin);
    
    void playTone(uint16_t frequency, uint16_t durationMs = 0);
    void stop();
    
    void startPattern(BuzzerPattern pattern, uint32_t durationMs = 0);
    void stopPattern();
    void updatePattern();
    
    bool isPlaying() const { return isActive; }
    BuzzerPattern getCurrentPattern() const { return currentPattern; }
};

#endif
