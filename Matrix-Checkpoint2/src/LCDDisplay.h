#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Constants.h"

/**
 * LCDDisplay - Wrapper for 16x2 LCD using LiquidCrystal library.
 * Provides convenient methods for common LCD operations.
 */
class LCDDisplay
{
public:
    LCDDisplay(LiquidCrystal& lcdRef);

    void init();
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
};

#endif // LCD_DISPLAY_H
