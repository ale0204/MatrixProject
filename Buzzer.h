#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

// Musical notes (frequencies in Hz) - Standard tuning (A4 = 440Hz)
namespace MusicNotes {
    // Octave 4 (Middle octave)
    constexpr uint16_t C4  = 262;  // Do
    constexpr uint16_t D4  = 294;  // Re
    constexpr uint16_t E4  = 330;  // Mi
    constexpr uint16_t F4  = 349;  // Fa
    constexpr uint16_t G4  = 392;  // Sol
    constexpr uint16_t A4  = 440;  // La
    constexpr uint16_t B4  = 494;  // Si
    
    // Octave 5 (Higher octave)
    constexpr uint16_t C5  = 523;  // Do
    constexpr uint16_t D5  = 587;  // Re
    constexpr uint16_t E5  = 659;  // Mi
    constexpr uint16_t F5  = 698;  // Fa
    constexpr uint16_t G5  = 784;  // Sol
    constexpr uint16_t A5  = 880;  // La
    constexpr uint16_t B5  = 988;  // Si
    
    // Special tones
    constexpr uint16_t LOW_TONE    = 200;   // Very low (error/death)
    constexpr uint16_t MEDIUM_TONE = 800;   // Medium (neutral)
    constexpr uint16_t HIGH_TONE   = 2000;  // Very high (alert)
}

// Note durations (in milliseconds)
namespace NoteDurations {
    constexpr uint16_t VERY_SHORT = 50;    // Ultra quick
    constexpr uint16_t SHORT      = 100;   // Quick beep
    constexpr uint16_t MEDIUM     = 150;   // Standard note
    constexpr uint16_t LONG       = 250;   // Emphasized note
    constexpr uint16_t VERY_LONG  = 400;   // Hold note
    
    constexpr uint16_t PAUSE_SHORT  = 50;  // Brief silence
    constexpr uint16_t PAUSE_MEDIUM = 100; // Standard pause
    constexpr uint16_t PAUSE_LONG   = 200; // Long pause
}

// Buzzer sound patterns - Context-specific
enum class BuzzerPattern : uint8_t {
    // Menu/UI feedback
    MENU_BEEP,           // Single short beep for menu navigation
    MENU_SELECT,         // Confirm selection
    
    // Game events - Positive
    COLLECT_GOLD,        // Short happy chirp when collecting gold
    LEVEL_COMPLETE,      // Victory fanfare for completing a level
    GAME_WON,            // Epic victory melody for winning the game
    
    // Game events - Negative
    HIT_WALL,            // Quick error beep for hitting wall
    HIT_BOMB,            // Explosive sound for bomb collision
    GAME_OVER,           // Sad descending tones for death
    
    // Special effects
    ROOM_TRANSITION,     // Brief tone when entering new room
    ALARM_SIREN,         // Continuous alternating alarm
    CONTINUOUS           // Simple continuous tone
};

class Buzzer {
private:
    const uint8_t pin;
    
    // Siren timing (for alarm pattern)
    static constexpr uint16_t SIREN_INTERVAL = 300;
    
    // Pattern state variables
    BuzzerPattern currentPattern;
    uint32_t patternStartTime;
    uint32_t lastUpdateTime;
    uint32_t patternDuration;  // 0 = infinite
    uint16_t patternState;     // State machine counter
    uint16_t currentTone;      // Current tone frequency
    bool isActive;
    
    // Internal tone function (doesn't stop pattern)
    void playToneInternal(uint16_t frequency, uint16_t durationMs = 0);

public:
    // Constructor takes pin as argument for reusability
    Buzzer(uint8_t buzzerPin);
    
    // Basic control
    void playTone(uint16_t frequency, uint16_t durationMs = 0);  // duration=0 means continuous
    void stop();
    
    // Pattern control (non-blocking)
    void startPattern(BuzzerPattern pattern, uint32_t durationMs = 0);
    void stopPattern();
    void updatePattern();  // Call in loop() to update pattern
    
    // State queries
    bool isPlaying() const { return isActive; }
    BuzzerPattern getCurrentPattern() const { return currentPattern; }
};

#endif // BUZZER_H
