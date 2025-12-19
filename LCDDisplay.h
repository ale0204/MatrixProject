#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Constants.h"

class LCDDisplay
{
public:
    LCDDisplay(LiquidCrystal& lcdRef);

    void init();
    void setBrightness(uint8_t brightness);  // 0-255 PWM value
    void clear();

    // Print at specific position
    void printAt(byte col, byte row, const char* text);
    void printAt(byte col, byte row, const __FlashStringHelper* text);

    // Print centered text
    void printCentered(byte row, const char* text);
    void printCentered(byte row, const __FlashStringHelper* text);

    // Clear a single line
    void clearLine(byte row);

    // Show a two-line message (convenience method)
    void showMessage(const char* line1, const char* line2);
    void showMessage(const __FlashStringHelper* line1, const __FlashStringHelper* line2);

    // Access to underlying LCD for advanced operations
    LiquidCrystal& getLcd();

private:
    LiquidCrystal& lcd;
    uint8_t ledPin;
    uint8_t currentBrightness;
};

#endif // LCD_DISPLAY_H
