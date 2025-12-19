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
#include "ActiveExplosive.h"
#include "GameSettings.h"
#include "SystemSettings.h"
#include "HighscoreManager.h"
#include "Constants.h"

enum class GameState : uint8_t
{
    MENU,
    SETTINGS_MENU,
    HIGHSCORE_VIEW,
    NAME_EDIT,
    ABOUT,
    HOW_TO_PLAY,
    PLAYING,
    BOMB_FEEDBACK,
    GAME_OVER_FEEDBACK,
    LEVEL_COMPLETE_FEEDBACK,
    LEVEL_STATS,
    GAME_WON_FEEDBACK
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
    PushButton exitButton;
    GameSettings gameSettings;
    SystemSettings systemSettings;
    HighscoreManager highscoreManager;
    
    ActiveExplosive activeExplosive;
    unsigned long explosivePlacedTime;
    GameState gameState;
    uint8_t currentLevel;
    uint8_t menuOption;
    uint8_t settingsOption;
    uint8_t highscoreScrollPos;
    
    char editedName[4];
    uint8_t nameEditPosition;
    uint16_t pendingHighscore;
    unsigned long nameEditEnteredTime;
    bool nameWasModified;
    uint16_t score;
    uint8_t explosivesUsedThisLevel;
    unsigned long lastUpdateTime;
    unsigned long lastLCDUpdate;
    unsigned long lastMenuNavigationTime;
    unsigned long lastSettingsNavigationTime;
    unsigned long feedbackTimer;
    
    unsigned long messageDisplayStartTime;
    bool waitingForMessageDisplay;
    GameState stateAfterMessage;
    
    uint8_t aboutScrollOffset;
    unsigned long lastAboutScrollTime;
    
    uint8_t howToPlayScrollOffset;
    unsigned long lastHowToPlayScrollTime;
    
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
    void checkExplosivePlacement();
    void handleExplosion();
    void showMenu();
    void showSettingsMenu();
    void showHighscores();
    void showNameEditor();
    void showAbout();
    void showHowToPlay();
    void showLevelStats();
    void checkRoomTransition();
    
    void playSound(uint16_t frequency, uint16_t duration);
    void playSoundPattern(BuzzerPattern pattern, uint16_t duration);
    
    void drawIcon(const byte pattern[8]);
    void drawStartIcon();
    void drawSettingsIcon();
    void drawTrophyIcon();
    void drawAboutIcon();
    void drawHowToPlayIcon();
};

#endif // GAME_ENGINE_H
