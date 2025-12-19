#include "GameSettings.h"
#include <EEPROM.h>

GameSettings::GameSettings()
    : startingLevel(MapConstants::LEVEL_0),
      difficulty(NORMAL)
{
}

void GameSettings::setStartingLevel(uint8_t level)
{
    if (level <= MapConstants::MAX_LEVEL) {
        startingLevel = level;
    }
}

void GameSettings::setDifficulty(uint8_t diff)
{
    if (diff <= HARD) {
        difficulty = diff;
    }
}

const char* GameSettings::getDifficultyName() const
{
    switch (difficulty) {
        case EASY:   return "Easy";
        case NORMAL: return "Normal";
        case HARD:   return "Hard";
        default:     return "Normal";
    }
}

float GameSettings::getScoreMultiplier() const
{
    float baseMult;
    
    // Starting level bonus
    switch (startingLevel) {
        case 0: baseMult = DifficultyConstants::SCORE_MULT_LEVEL_0; break;
        case 1: baseMult = DifficultyConstants::SCORE_MULT_LEVEL_1; break;
        case 2: baseMult = DifficultyConstants::SCORE_MULT_LEVEL_2; break;
        case 3: baseMult = DifficultyConstants::SCORE_MULT_LEVEL_3; break;
        default: baseMult = DifficultyConstants::SCORE_MULT_LEVEL_0; break;
    }
    
    // Difficulty multiplier bonus
    switch (difficulty) {
        case EASY:   return baseMult * DifficultyConstants::SCORE_MULT_EASY;
        case NORMAL: return baseMult * DifficultyConstants::SCORE_MULT_NORMAL;
        case HARD:   return baseMult * DifficultyConstants::SCORE_MULT_HARD;
        default:     return baseMult;
    }
}

uint8_t GameSettings::getMaxBombsForLevel(uint8_t level) const
{
        uint8_t baseBombs;
    switch (level) {
        case MapConstants::LEVEL_0: baseBombs = DifficultyConstants::LEVEL_0_BASE_BOMBS; break;
        case MapConstants::LEVEL_1: baseBombs = DifficultyConstants::LEVEL_1_BASE_BOMBS; break;
        case MapConstants::LEVEL_2: baseBombs = DifficultyConstants::LEVEL_2_BASE_BOMBS; break;
        case MapConstants::LEVEL_3: baseBombs = DifficultyConstants::LEVEL_3_BASE_BOMBS; break;
        default: baseBombs = DifficultyConstants::LEVEL_1_BASE_BOMBS; break;
    }
    
        switch (difficulty) {
        case EASY:   return baseBombs > 0 ? baseBombs - DifficultyConstants::EASY_BOMB_REDUCTION : 0;
        case NORMAL: return baseBombs;
        case HARD:   return baseBombs + DifficultyConstants::HARD_BOMB_INCREASE; 
        default:     return baseBombs;
    }
}

uint8_t GameSettings::getMinBombsForLevel(uint8_t level) const
{
    uint8_t maxBombs = getMaxBombsForLevel(level);
    return maxBombs > DifficultyConstants::MIN_BOMBS_REDUCTION ? maxBombs - DifficultyConstants::MIN_BOMBS_REDUCTION : 0;
}

// placeRandomBombs(min, max) need a range, and chooses a random number in that range
// thats why we need both min and max functions

uint8_t GameSettings::getStartingLives() const
{
    switch (difficulty) {
        case EASY:   return DifficultyConstants::EASY_LIVES;
        case HARD:   return DifficultyConstants::HARD_LIVES;
        case NORMAL: return DifficultyConstants::NORMAL_LIVES;
        default:     return DifficultyConstants::NORMAL_LIVES;
    }
}

void GameSettings::loadFromEEPROM()
{
    uint8_t magic = EEPROM.read(EEPROM_ADDR);
    if (magic != MAGIC_BYTE) {
        resetToDefaults();
        return;
    }
    
    // Load settings
    startingLevel = EEPROM.read(EEPROM_ADDR + 1);
    difficulty = EEPROM.read(EEPROM_ADDR + 2);
    
    // Validation
    if (startingLevel > MapConstants::MAX_LEVEL) {
        startingLevel = MapConstants::LEVEL_0;
    }
    if (difficulty > HARD) {
        difficulty = NORMAL;
    }
}

void GameSettings::saveToEEPROM()
{
    EEPROM.update(EEPROM_ADDR, MAGIC_BYTE);
    EEPROM.update(EEPROM_ADDR + 1, startingLevel);
    EEPROM.update(EEPROM_ADDR + 2, difficulty);
}

void GameSettings::resetToDefaults()
{
    startingLevel = MapConstants::LEVEL_0;
    difficulty = NORMAL;
    saveToEEPROM();
}
