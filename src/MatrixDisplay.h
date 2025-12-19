#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H

#include <Arduino.h>
#include <LedControl.h>
#include "Map.h"
#include "Player.h"
#include "CameraController.h"
#include "Constants.h"
#include "PhotoResistor.h"

class MatrixDisplay
{
private:
    LedControl lc;
    uint8_t brightness;
    uint8_t frameCounter;
    PhotoResistor* photoResistor;

public:
    MatrixDisplay(uint8_t dinPin, uint8_t clkPin, uint8_t csPin);
    
    void begin();
    void draw(Map& map, Player& player, CameraController& camera);
    void setBrightness(uint8_t level);
    uint8_t getBrightness() const { return brightness; }
    void clear();
    void setPhotoResistor(PhotoResistor* pr);
    
    uint8_t getFrameCounter() const { return frameCounter; }
    void setLed(uint8_t x, uint8_t y, bool state);

private:
    void drawTile(uint8_t localX, uint8_t localY, TileType tile);
    void drawPlayer(uint8_t localX, uint8_t localY);
};

#endif // MATRIX_DISPLAY_H
