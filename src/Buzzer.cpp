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
        tone(pin, frequency, durationMs);
    }
    isActive = true;
}

void Buzzer::playToneInternal(uint16_t frequency, uint16_t durationMs)
{
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
            break;
    }
}

void Buzzer::stopPattern()
{
    stop();
}

void Buzzer::updatePattern()
{
    if (!isActive || patternDuration == 0) {
        return;
    }
    
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - lastUpdateTime;
    
    if (patternDuration > 0 && (currentTime - patternStartTime >= patternDuration))
    {
        stop();
        return;
    }
    
    switch (currentPattern)
    {
        // ===== MENU / UI FEEDBACK =====
        case BuzzerPattern::MENU_BEEP:
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
