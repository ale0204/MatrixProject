#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal& lcdRef)
    : lcd(&lcdRef)
{
}

void LCDDisplay::init()
{
    lcd->begin(LCDConstants::COLS, LCDConstants::ROWS);
    lcd->noCursor();
    lcd->noBlink();
    lcd->clear();
}

void LCDDisplay::clear()
{
    lcd->clear();
}

void LCDDisplay::printAt(byte col, byte row, const char* text)
{
    lcd->setCursor(col, row);
    lcd->print(text);
}

void LCDDisplay::printAt(byte col, byte row, const __FlashStringHelper* text)
{
    lcd->setCursor(col, row);
    lcd->print(text);
}

void LCDDisplay::printCentered(byte row, const char* text)
{
    byte len = strlen(text);
    byte col = 0;
    if (len < LCDConstants::COLS)
    {
        col = (LCDConstants::COLS - len) / 2;
    }
    clearLine(row);
    printAt(col, row, text);
}

void LCDDisplay::printCentered(byte row, const __FlashStringHelper* text)
{
    // For flash strings, we need to calculate length differently
    byte len = strlen_P((const char*)text);
    byte col = 0;
    if (len < LCDConstants::COLS)
    {
        col = (LCDConstants::COLS - len) / 2;
    }
    clearLine(row);
    printAt(col, row, text);
}

void LCDDisplay::clearLine(byte row)
{
    lcd->setCursor(0, row);
    for (byte i = 0; i < LCDConstants::COLS; i++)
    {
        lcd->write(' ');
    }
}

void LCDDisplay::showMessage(const char* line1, const char* line2)
{
    clear();
    printCentered(0, line1);
    printCentered(1, line2);
}

void LCDDisplay::showMessage(const __FlashStringHelper* line1, const __FlashStringHelper* line2)
{
    clear();
    printCentered(0, line1);
    printCentered(1, line2);
}

LiquidCrystal* LCDDisplay::getLcd()
{
    return lcd;
}
