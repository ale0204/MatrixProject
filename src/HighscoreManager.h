#ifndef HIGHSCORE_MANAGER_H
#define HIGHSCORE_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Constants.h"

struct HighscoreEntry
{
    char name[HighscoreConstants::HIGHSCORE_NAME_LENGTH + 1];
    uint16_t score;
    uint8_t level;
    
    HighscoreEntry() : score(0), level(0) {
        for (uint8_t i = 0; i < HighscoreConstants::HIGHSCORE_NAME_LENGTH; i++) {
            name[i] = HighscoreConstants::DEFAULT_NAME_CHAR;
        }
        name[HighscoreConstants::HIGHSCORE_NAME_LENGTH] = '\0';
    }
};


class HighscoreManager
{
private:
    HighscoreEntry entries[HighscoreConstants::MAX_HIGHSCORE_ENTRIES];
    
    static const uint16_t EEPROM_ADDR = 20;      
    static const uint8_t MAGIC_BYTE = 0xC7; 
    
public:
    HighscoreManager();
    
    bool isHighscore(uint16_t score) const;
    uint8_t getHighscorePosition(uint16_t score) const;
    void insertHighscore(const char* name, uint16_t score, uint8_t level);
    const HighscoreEntry& getEntry(uint8_t index) const { return entries[index]; }
    
    // EEPROM Management
    void loadFromEEPROM();
    void saveToEEPROM();
    void resetToDefaults();
    void resetHighscores();
};

#endif // HIGHSCORE_MANAGER_H
