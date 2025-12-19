#include "HighscoreManager.h"
#include "Constants.h"

HighscoreManager::HighscoreManager()
{
}

bool HighscoreManager::isHighscore(uint16_t score) const
{
    return score > entries[HighscoreConstants::HIGHSCORE_THIRD_PLACE].score || entries[HighscoreConstants::HIGHSCORE_THIRD_PLACE].score == 0;
}

uint8_t HighscoreManager::getHighscorePosition(uint16_t score) const
{
            
    if (score > entries[HighscoreConstants::HIGHSCORE_FIRST_PLACE].score || entries[HighscoreConstants::HIGHSCORE_FIRST_PLACE].score == 0) {
        return HighscoreConstants::HIGHSCORE_FIRST_PLACE;
    }
    if (score > entries[HighscoreConstants::HIGHSCORE_SECOND_PLACE].score || entries[HighscoreConstants::HIGHSCORE_SECOND_PLACE].score == 0) {
        return HighscoreConstants::HIGHSCORE_SECOND_PLACE;
    }
    if (score > entries[HighscoreConstants::HIGHSCORE_THIRD_PLACE].score || entries[HighscoreConstants::HIGHSCORE_THIRD_PLACE].score == 0) {
        return HighscoreConstants::HIGHSCORE_THIRD_PLACE;
    }
    
    return HighscoreConstants::HIGHSCORE_NOT_QUALIFIED;  }

void HighscoreManager::insertHighscore(const char* name, uint16_t score, uint8_t level)
{
    uint8_t position = getHighscorePosition(score);
    
    if (position == HighscoreConstants::HIGHSCORE_NOT_QUALIFIED) {
        return;      
    }
    
    for (int8_t i = HighscoreConstants::HIGHSCORE_THIRD_PLACE; i > position; i--) {
        entries[i] = entries[i - 1];
    }
    
    for (uint8_t i = 0; i < HighscoreConstants::HIGHSCORE_NAME_LENGTH; i++) {
        entries[position].name[i] = name[i];
    }
    entries[position].name[HighscoreConstants::HIGHSCORE_NAME_LENGTH] = '\0';
    entries[position].score = score;
    entries[position].level = level;
    
    saveToEEPROM();
}

void HighscoreManager::loadFromEEPROM()
{
    uint8_t magic = EEPROM.read(EEPROM_ADDR);
    
    if (magic != MAGIC_BYTE) {
        resetToDefaults();
        return;
    }
    
    uint16_t addr = EEPROM_ADDR + HighscoreConstants::EEPROM_MAGIC_OFFSET;
    
    for (uint8_t i = 0; i < HighscoreConstants::MAX_HIGHSCORE_ENTRIES; i++) {
        for (uint8_t j = 0; j < HighscoreConstants::HIGHSCORE_NAME_LENGTH; j++) {
            entries[i].name[j] = EEPROM.read(addr++);
        }
        entries[i].name[HighscoreConstants::HIGHSCORE_NAME_LENGTH] = '\0';
        
        uint8_t lowByte = EEPROM.read(addr++);
        uint8_t highByte = EEPROM.read(addr++);
        entries[i].score = (highByte << HighscoreConstants::SCORE_HIGH_BYTE_SHIFT) | lowByte;
        
        // Level (1 byte)
        entries[i].level = EEPROM.read(addr++);
    }
}

void HighscoreManager::saveToEEPROM()
{
    EEPROM.update(EEPROM_ADDR, MAGIC_BYTE);
    
    uint16_t addr = EEPROM_ADDR + HighscoreConstants::EEPROM_MAGIC_OFFSET;
    
    for (uint8_t i = 0; i < HighscoreConstants::MAX_HIGHSCORE_ENTRIES; i++) 
    {
        for (uint8_t j = 0; j < HighscoreConstants::HIGHSCORE_NAME_LENGTH; j++) 
        {
            EEPROM.update(addr++, entries[i].name[j]);
        }
        
        EEPROM.update(addr++, entries[i].score & HighscoreConstants::BYTE_MASK);
        EEPROM.update(addr++, (entries[i].score >> HighscoreConstants::SCORE_HIGH_BYTE_SHIFT) & HighscoreConstants::BYTE_MASK);
        
        // Level
        EEPROM.update(addr++, entries[i].level);
    }
}

void HighscoreManager::resetToDefaults()
{
    for (uint8_t i = 0; i < HighscoreConstants::MAX_HIGHSCORE_ENTRIES; i++) 
    {
        for (uint8_t j = 0; j < HighscoreConstants::HIGHSCORE_NAME_LENGTH; j++) 
        {
            entries[i].name[j] = HighscoreConstants::DEFAULT_NAME_CHAR;
        }
        entries[i].name[HighscoreConstants::HIGHSCORE_NAME_LENGTH] = '\0';
        entries[i].score = 0;
        entries[i].level = 0;
    }
    
    saveToEEPROM();
}

void HighscoreManager::resetHighscores()
{
        resetToDefaults();
}
