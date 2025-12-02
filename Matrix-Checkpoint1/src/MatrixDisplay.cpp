#include "MatrixDisplay.h"

MatrixDisplay::MatrixDisplay(Pin dinPin, Pin clkPin, Pin loadPin)
    : lc(dinPin, clkPin, loadPin, MatrixConstants::DEVICE_COUNT)
{
    // Initialize buffer to all zeros
    for (byte i = 0; i < MatrixConstants::SIZE; i++)
    {
        displayBuffer[i] = 0;
    }
}

void MatrixDisplay::init()
{
    // Wake up MAX7219 from power-saving mode
    lc.shutdown(0, false);

    // Set brightness
    lc.setIntensity(0, MatrixConstants::BRIGHTNESS);

    // Clear display
    clear();
}

void MatrixDisplay::clear()
{
    lc.clearDisplay(0);
    for (byte i = 0; i < MatrixConstants::SIZE; i++)
    {
        displayBuffer[i] = 0;
    }
}

void MatrixDisplay::setBrightness(byte brightness)
{
    // Clamp to valid range (0-15)
    if (brightness > MatrixConstants::MAX_BRIGHTNESS)
    {
        brightness = MatrixConstants::MAX_BRIGHTNESS;
    }
    lc.setIntensity(0, brightness);
}

void MatrixDisplay::setLed(byte row, byte col, bool state)
{
    if (row >= MatrixConstants::SIZE || col >= MatrixConstants::SIZE)
    {
        return;  // Out of bounds
    }

    lc.setLed(0, row, col, state);

    // Update buffer
    if (state)
    {
        displayBuffer[row] |= (1 << col);
    }
    else
    {
        displayBuffer[row] &= ~(1 << col);
    }
}

void MatrixDisplay::toggleLed(byte row, byte col)
{
    setLed(row, col, !getLed(row, col));
}

void MatrixDisplay::setRow(byte row, byte value)
{
    if (row >= MatrixConstants::SIZE)
    {
        return;
    }

    lc.setRow(0, row, value);
    displayBuffer[row] = value;
}

void MatrixDisplay::setColumn(byte col, byte value)
{
    if (col >= MatrixConstants::SIZE)
    {
        return;
    }

    lc.setColumn(0, col, value);

    // Update buffer for each row
    for (byte row = 0; row < MatrixConstants::SIZE; row++)
    {
        if (value & (1 << row))
        {
            displayBuffer[row] |= (1 << col);
        }
        else
        {
            displayBuffer[row] &= ~(1 << col);
        }
    }
}

void MatrixDisplay::fillAll()
{
    for (byte row = 0; row < MatrixConstants::SIZE; row++)
    {
        setRow(row, 0xFF);
    }
}

bool MatrixDisplay::getLed(byte row, byte col) const
{
    if (row >= MatrixConstants::SIZE || col >= MatrixConstants::SIZE)
    {
        return false;
    }

    return (displayBuffer[row] & (1 << col)) != 0;
}
