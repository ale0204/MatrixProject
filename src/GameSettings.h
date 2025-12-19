#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <Arduino.h>
#include "Constants.h"

class GameSettings
{
private:
    uint8_t startingLevel;   
    uint8_t difficulty;      
    static const uint16_t EEPROM_ADDR = 0;      
    static const uint8_t MAGIC_BYTE = 0xA5;
    
public:
    GameSettings();
    
    // Starting Level
    uint8_t getStartingLevel() const { return startingLevel; }
    void setStartingLevel(uint8_t level);
    
    // Difficulty
    enum Difficulty : uint8_t {
        EASY = 0,
        NORMAL = 1,
        HARD = 2
    };
    
    uint8_t getDifficulty() const { return difficulty; }
    void setDifficulty(uint8_t diff);
    const char* getDifficultyName() const;
    
    // Score Multiplier (calculated based on each starting level)
    float getScoreMultiplier() const;
    
    // EEPROM Management
    void loadFromEEPROM();
    void saveToEEPROM();
    void resetToDefaults();
    
    uint8_t getMaxBombsForLevel(uint8_t level) const;
    uint8_t getMinBombsForLevel(uint8_t level) const;
    uint8_t getStartingLives() const;
};

#endif // GAME_SETTINGS_H
