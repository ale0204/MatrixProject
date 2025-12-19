#ifndef SYSTEM_SETTINGS_H
#define SYSTEM_SETTINGS_H

#include <Arduino.h>
#include "Constants.h"

class SystemSettings
{
private:
    char playerName[SystemDefaultConstants::PLAYER_NAME_LENGTH + 1];
    uint8_t lcdBrightness;
    uint8_t matrixBrightness;
    bool soundEnabled;
    
    static const uint16_t EEPROM_ADDR = 10;      
    static const uint8_t MAGIC_BYTE = 0xB6;  
    
public:
    SystemSettings();
    
    const char* getPlayerName() const { return playerName; }
    void setPlayerName(const char* name);
    
    uint8_t getLCDBrightness() const { return lcdBrightness; }
    void setLCDBrightness(uint8_t brightness);
    
    uint8_t getMatrixBrightness() const { return matrixBrightness; }
    void setMatrixBrightness(uint8_t brightness);
    
    bool isSoundEnabled() const { return soundEnabled; }
    void setSoundEnabled(bool enabled);
    void toggleSound() { soundEnabled = !soundEnabled; }
    
    void loadFromEEPROM();
    void saveToEEPROM();
    void resetToDefaults();
};

#endif // SYSTEM_SETTINGS_H
