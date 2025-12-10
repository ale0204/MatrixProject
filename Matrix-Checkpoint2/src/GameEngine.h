#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <Arduino.h>
#include "Map.h"
#include "Player.h"
#include "CameraController.h"
#include "MatrixDisplay.h"
#include "LCDDisplay.h"
#include "Joystick.h"
#include "Buzzer.h"
#include "Constants.h"

enum class GameState : uint8_t
{
    MENU,
    PLAYING
};

class GameEngine
{
private:
    Map map;
    Player player;
    CameraController camera;
    MatrixDisplay& matrixDisplay;
    LCDDisplay& lcdDisplay;
    Joystick& joystick;
    Buzzer& buzzer;
    
    GameState gameState;
    uint8_t currentLevel;
    unsigned long lastUpdateTime;
    unsigned long lastLCDUpdate;
    
    uint8_t lastCameraX;
    uint8_t lastCameraY;
    
    static const unsigned long UPDATE_INTERVAL = 200;
    static const unsigned long LCD_UPDATE_INTERVAL = 500;

public:
    GameEngine(MatrixDisplay& matrix, LCDDisplay& lcd, Joystick& joy, Buzzer& buzz);
    
    void begin();
    void update();
    void loadLevel(uint8_t levelIndex);

private:
    void handleInput();
    void updateLCD();
    void checkWinCondition();
    void showMenu();
    void checkRoomTransition();
};

#endif // GAME_ENGINE_H
