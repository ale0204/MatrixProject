#include "Buzzer.h"

Buzzer::Buzzer(uint8_t buzzerPin)
    : pin{buzzerPin},
      currentTone{MusicNotes::MEDIUM_TONE},
      isActive{false},
      currentPattern{BuzzerPattern::MENU_BEEP},
      patternStartTime{0},
      lastUpdateTime{0},
      patternDuration{0},
      patternState{0}
{
    pinMode(pin, OUTPUT);
}

void Buzzer::playTone(uint16_t frequency, uint16_t durationMs)
{
    // Stop any running pattern first - reset all pattern state
    if (patternDuration > 0) {
        noTone(pin);
        patternState = 0;
        patternDuration = 0;
        isActive = false;
    }
    
    if (durationMs == 0) {
        // Continuous tone
        tone(pin, frequency);
    }
    else {
        // Tone with duration (Arduino handles auto-stop)
        tone(pin, frequency, durationMs);
    }
    isActive = true;
}

void Buzzer::playToneInternal(uint16_t frequency, uint16_t durationMs)
{
    // Internal function for patterns - doesn't stop pattern state
    if (durationMs == 0) {
        tone(pin, frequency);
    }
    else {
        tone(pin, frequency, durationMs);
    }
}

void Buzzer::stop()
{
    noTone(pin);
    isActive = false;
    patternState = 0;
    patternDuration = 0;
}

void Buzzer::startPattern(BuzzerPattern pattern, uint32_t durationMs)
{
    currentPattern = pattern;
    patternState = 0;
    patternStartTime = millis();
    lastUpdateTime = millis();
    patternDuration = durationMs;
    isActive = true;
    
    // Start with appropriate tone for the pattern
    switch (pattern)
    {
        case BuzzerPattern::CONTINUOUS:
            playToneInternal(currentTone);
            break;
        case BuzzerPattern::ALARM_SIREN:
            playToneInternal(MusicNotes::MEDIUM_TONE);
            break;
        default:
            // Most patterns are handled in updatePattern()
            break;
    }
}

void Buzzer::stopPattern()
{
    stop();
}

void Buzzer::updatePattern()
{
    // Don't update if not active OR no pattern duration set
    if (!isActive || patternDuration == 0) {
        return;
    }
    
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - lastUpdateTime;
    
    // Check if pattern duration has expired (if not infinite)
    if (patternDuration > 0 && (currentTime - patternStartTime >= patternDuration))
    {
        stop();
        return;
    }
    
    switch (currentPattern)
    {
        // ===== MENU / UI FEEDBACK =====
        case BuzzerPattern::MENU_BEEP:
            // Single short beep for navigation
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::VERY_SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            } 
            else if (patternState == 1 && elapsed >= NoteDurations::VERY_SHORT)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::MENU_SELECT:
            // Double beep for selection
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            } 
            else if (patternState == 1 && elapsed >= NoteDurations::SHORT)
            {
                noTone(pin);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::PAUSE_SHORT)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::SHORT);
                patternState = 3;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 3 && elapsed >= NoteDurations::SHORT)
            {
                stop();
            }
            break;
        
        // ===== POSITIVE GAME EVENTS =====
        case BuzzerPattern::COLLECT_GOLD:
            // Quick happy chirp: C5 -> E5
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::VERY_SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::VERY_SHORT)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::SHORT);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::SHORT)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::LEVEL_COMPLETE:
            // Victory fanfare: C5 -> E5 -> G5 (major chord)
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::MEDIUM);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::MEDIUM);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::G5, NoteDurations::LONG);
                patternState = 3;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 3 && elapsed >= NoteDurations::LONG)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::GAME_WON:
            // Epic victory: C5 -> E5 -> G5 -> C6 (ascending triumph)
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::MEDIUM);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::MEDIUM);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::G5, NoteDurations::MEDIUM);
                patternState = 3;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 3 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::C5 * 2, NoteDurations::VERY_LONG); // C6 (octave higher)
                patternState = 4;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 4 && elapsed >= NoteDurations::VERY_LONG)
            {
                stop();
            }
            break;
        
        // ===== NEGATIVE GAME EVENTS =====
        case BuzzerPattern::HIT_WALL:
            // Quick error beep
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::LOW_TONE, NoteDurations::VERY_SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::VERY_SHORT)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::HIT_BOMB:
            // Explosive sound: HIGH -> MEDIUM -> LOW (rapid descent)
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::HIGH_TONE, NoteDurations::VERY_SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::VERY_SHORT)
            {
                playToneInternal(MusicNotes::MEDIUM_TONE, NoteDurations::VERY_SHORT);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::VERY_SHORT)
            {
                playToneInternal(MusicNotes::LOW_TONE, NoteDurations::MEDIUM);
                patternState = 3;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 3 && elapsed >= NoteDurations::MEDIUM)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::GAME_OVER:
            // Sad descending: E5 -> C5 -> G4 -> C4 (defeat)
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::E5, NoteDurations::MEDIUM);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::MEDIUM);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::G4, NoteDurations::MEDIUM);
                patternState = 3;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 3 && elapsed >= NoteDurations::MEDIUM)
            {
                playToneInternal(MusicNotes::C4, NoteDurations::VERY_LONG);
                patternState = 4;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 4 && elapsed >= NoteDurations::VERY_LONG)
            {
                stop();
            }
            break;
        
        // ===== SPECIAL EFFECTS =====
        case BuzzerPattern::ROOM_TRANSITION:
            // Brief ascending tone when entering new room
            if (patternState == 0)
            {
                playToneInternal(MusicNotes::G4, NoteDurations::VERY_SHORT);
                patternState = 1;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 1 && elapsed >= NoteDurations::VERY_SHORT)
            {
                playToneInternal(MusicNotes::C5, NoteDurations::SHORT);
                patternState = 2;
                lastUpdateTime = currentTime;
            }
            else if (patternState == 2 && elapsed >= NoteDurations::SHORT)
            {
                stop();
            }
            break;
            
        case BuzzerPattern::CONTINUOUS:
            // Already playing, nothing to update
            break;
            
        case BuzzerPattern::ALARM_SIREN:
            // Alternating high/low alarm
            if (elapsed >= SIREN_INTERVAL)
            {
                if (patternState == 0)
                {
                    playToneInternal(MusicNotes::HIGH_TONE);
                    patternState = 1;
                }
                else
                {
                    playToneInternal(MusicNotes::MEDIUM_TONE);
                    patternState = 0;
                }
                lastUpdateTime = currentTime;
            }
            break;
    }
}
