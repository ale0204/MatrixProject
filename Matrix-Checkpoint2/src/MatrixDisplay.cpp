#include "MatrixDisplay.h"

MatrixDisplay::MatrixDisplay(uint8_t dinPin, uint8_t clkPin, uint8_t csPin)
    : lc(dinPin, clkPin, csPin, MatrixConstants::DEVICE_COUNT)
    , brightness(DisplayConstants::DEFAULT_MATRIX_BRIGHTNESS)
    , frameCounter(0)
{
}

void MatrixDisplay::begin()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, brightness);
    clear();
}

void MatrixDisplay::clear()
{
    lc.clearDisplay(0);
}

void MatrixDisplay::setBrightness(uint8_t level)
{
    if (level > MatrixConstants::MAX_BRIGHTNESS)
    {
        level = MatrixConstants::MAX_BRIGHTNESS;
    }
    
    brightness = level;
    lc.setIntensity(0, brightness);
}

void MatrixDisplay::draw(Map& map, Player& player, CameraController& camera)
{
    frameCounter++;
    
    clear();
    
    for (uint8_t localY = 0; localY < MapConstants::ROOM_SIZE; localY++)
    {
        for (uint8_t localX = 0; localX < MapConstants::ROOM_SIZE; localX++)
        {
            uint8_t globalX = camera.getCameraX() + localX;
            uint8_t globalY = camera.getCameraY() + localY;
            
            TileType tile = map.getTile(globalX, globalY);
            
            drawTile(localX, localY, tile);
        }
    }
    
    uint8_t playerX = player.getX();
    uint8_t playerY = player.getY();
    
    if (camera.isInViewport(playerX, playerY))
    {
        uint8_t localPlayerX, localPlayerY;
        if (camera.globalToLocal(playerX, playerY, localPlayerX, localPlayerY))
        {
            drawPlayer(localPlayerX, localPlayerY);
        }
    }
}

void MatrixDisplay::drawTile(uint8_t localX, uint8_t localY, TileType tile)
{
    bool ledState = false;
    
    switch (tile)
    {
        case TileType::EMPTY:
            ledState = false;
            break;
        
        case TileType::WALL:
            ledState = true;
            break;
        
        case TileType::GOLD:
            ledState = (frameCounter % DisplayConstants::GOLD_BLINK_CYCLE < DisplayConstants::GOLD_BLINK_ON_FRAMES);
            break;
        
        case TileType::DOOR:
            ledState = false;
            break;
        
        case TileType::EXIT:
            ledState = false;
            break;
    }
    
    lc.setLed(0, localY, localX, ledState);
}

void MatrixDisplay::drawPlayer(uint8_t localX, uint8_t localY)
{
    lc.setLed(0, localY, localX, true);
}
