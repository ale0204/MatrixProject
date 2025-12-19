#include "SystemSettings.h"
#include <EEPROM.h>
#include <string.h>
#include "Constants.h"

SystemSettings::SystemSettings()
    : lcdBrightness(SystemDefaultConstants::DEFAULT_LCD_BRIGHTNESS),      // Default bright
      matrixBrightness(8),     
      soundEnabled(true)
{
    strcpy(playerName, "PLAYER");  // Default name
}

void SystemSettings::setPlayerName(const char* name)
{
    if (name == nullptr) return;
    
    strncpy(playerName, name, SystemDefaultConstants::PLAYER_NAME_LENGTH);
    playerName[3] = '\0';  // Ensure null termination
}

void SystemSettings::setLCDBrightness(uint8_t brightness)
{
    lcdBrightness = brightness;
}

void SystemSettings::setMatrixBrightness(uint8_t brightness)
{
    if (brightness <= MatrixConstants::MAX_BRIGHTNESS) {
        matrixBrightness = brightness;
    }
}

void SystemSettings::setSoundEnabled(bool enabled)
{
    soundEnabled = enabled;
}

void SystemSettings::loadFromEEPROM()
{
    // Check magic byte
    uint8_t magic = EEPROM.read(EEPROM_ADDR);
    if (magic != MAGIC_BYTE) {
        // First time - use defaults
        resetToDefaults();
        return;
    }
    
    for (uint8_t i = 0; i < SystemDefaultConstants::PLAYER_NAME_LENGTH; i++) {
        playerName[i] = EEPROM.read(EEPROM_ADDR + 1 + i);
    }
    playerName[3] = '\0';
    
    // Load settings
    lcdBrightness = EEPROM.read(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_LCD_BRIGHTNESS_OFFSET);
    matrixBrightness = EEPROM.read(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_MATRIX_BRIGHTNESS_OFFSET);
    soundEnabled = EEPROM.read(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_SOUND_ENABLED_OFFSET);
    
    if (matrixBrightness > MatrixConstants::MAX_BRIGHTNESS) {
        matrixBrightness = SystemDefaultConstants::DEFAULT_MATRIX_BRIGHTNESS;
    }
}

void SystemSettings::saveToEEPROM()
{
    EEPROM.update(EEPROM_ADDR, MAGIC_BYTE);
    
    for (uint8_t i = 0; i < SystemDefaultConstants::PLAYER_NAME_LENGTH; i++) {
        EEPROM.update(EEPROM_ADDR + 1 + i, playerName[i]);
    }
    
    EEPROM.update(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_LCD_BRIGHTNESS_OFFSET, lcdBrightness);
    EEPROM.update(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_MATRIX_BRIGHTNESS_OFFSET, matrixBrightness);
    EEPROM.update(EEPROM_ADDR + EEPROMOffsets::SYSTEM_SETTINGS_SOUND_ENABLED_OFFSET, soundEnabled ? 1 : 0);
}

void SystemSettings::resetToDefaults()
{
    strcpy(playerName, "PLAYER");
    lcdBrightness = SystemDefaultConstants::DEFAULT_LCD_BRIGHTNESS;
    matrixBrightness = SystemDefaultConstants::DEFAULT_MATRIX_BRIGHTNESS;
    soundEnabled = true;
    saveToEEPROM();
}
