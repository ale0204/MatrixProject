#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H

#include <Arduino.h>
#include <LedControl.h>
#include "Constants.h"

/**
 * MatrixDisplay - Wrapper for 8x8 LED matrix controlled by MAX7219.
 * Uses LedControl library for all matrix operations.
 * 
 * IMPORTANT: This is a common cathode matrix with MAX7219 driver.
 * All control MUST go through LedControl (setLed, setRow, etc.)
 */
class MatrixDisplay
{
public:
    MatrixDisplay(Pin dinPin, Pin clkPin, Pin loadPin);

    void init();
    void clear();
    void setBrightness(byte brightness);

    // Single LED control
    void setLed(byte row, byte col, bool state);
    void toggleLed(byte row, byte col);

    // Row/column control
    void setRow(byte row, byte value);
    void setColumn(byte col, byte value);

    // Utility
    void fillAll();
    bool getLed(byte row, byte col) const;

private:
    LedControl lc;
    byte displayBuffer[MatrixConstants::SIZE];  // Track LED states
};

#endif // MATRIX_DISPLAY_H
