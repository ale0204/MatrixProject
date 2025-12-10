#include "GameEngine.h"

GameEngine::GameEngine(MatrixDisplay& matrix, LCDDisplay& lcd, Joystick& joy, Buzzer& buzz)
    : map()
    , player(&map)
    , camera(&player)
    , matrixDisplay(matrix)
    , lcdDisplay(lcd)
    , joystick(joy)
    , buzzer(buzz)
    , gameState(GameState::MENU)
    , currentLevel(MapConstants::LEVEL_1)
    , lastUpdateTime(0)
    , lastLCDUpdate(0)
    , lastCameraX(0)
    , lastCameraY(0)
{
}

void GameEngine::begin()
{
    showMenu();
}

void GameEngine::loadLevel(uint8_t levelIndex)
{
    currentLevel = levelIndex;
    
    map.loadLevel(levelIndex);
    
    player.resetGold();
    player.setPosition(SpawnConstants::DEFAULT_SPAWN_X, SpawnConstants::DEFAULT_SPAWN_Y);
    
    camera.update();
    
    buzzer.playTone(ToneFrequencies::LEVEL_LOAD_HZ, SoundDurations::LEVEL_LOAD_TONE_MS);
    
    lcdDisplay.clear();
    lcdDisplay.printAt(0, 0, "Level ");
    lcdDisplay.printAt(LCDConstants::COLS / 2 - 1, 0, String(levelIndex + 1).c_str());
}

void GameEngine::update()
{
    unsigned long currentTime = millis();
    
    joystick.update();
    
    if (gameState == GameState::MENU)
    {
        if (joystick.wasButtonPressed())
        {
            buzzer.startPattern(BuzzerPattern::MENU_SELECT, SoundDurations::MENU_SELECT_MS);
            gameState = GameState::PLAYING;
            
            loadLevel(MapConstants::LEVEL_1);
            
            lastCameraX = camera.getCameraX();
            lastCameraY = camera.getCameraY();
        }
        return;
    }
    
    buzzer.updatePattern();
    
    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
    {
        lastUpdateTime = currentTime;
        
        handleInput();
        camera.update();
        checkRoomTransition();
        checkWinCondition();
    }
    
    if (currentTime - lastLCDUpdate >= LCD_UPDATE_INTERVAL)
    {
        lastLCDUpdate = currentTime;
        updateLCD();
    }
    
    matrixDisplay.draw(map, player, camera);
}

void GameEngine::handleInput()
{
    int8_t dx = 0;
    int8_t dy = 0;
    
    JoystickDirection dir = joystick.getDirection();
    
    switch (dir)
    {
        case JoystickDirection::UP:
            dy = -1;
            break;
        case JoystickDirection::DOWN:
            dy = 1;
            break;
        case JoystickDirection::LEFT:
            dx = -1;
            break;
        case JoystickDirection::RIGHT:
            dx = 1;
            break;
        case JoystickDirection::NONE:
            return;
    }
    
    uint8_t goldBefore = player.getGoldCollected();
    
    player.move(dx, dy);
    
    uint8_t goldAfter = player.getGoldCollected();
    if (goldAfter > goldBefore)
    {
        buzzer.startPattern(BuzzerPattern::COLLECT_GOLD, SoundDurations::COLLECT_GOLD_MS);
    }
}

void GameEngine::updateLCD()
{
    lcdDisplay.clearLine(0);
    lcdDisplay.clearLine(1);
    
    char buffer[DisplayConstants::LCD_BUFFER_SIZE];
    uint8_t collected = player.getGoldCollected();
    uint8_t total = map.getTotalGold();
    
    sprintf(buffer, "Gold: %d/%d", collected, total);
    lcdDisplay.printAt(0, 0, buffer);
    
    sprintf(buffer, "Level: %d", currentLevel + 1);
    lcdDisplay.printAt(0, 1, buffer);
}

void GameEngine::showMenu()
{
    lcdDisplay.clear();
    lcdDisplay.printCentered(0, "THE MINER");
    lcdDisplay.printCentered(1, "Press to Play");
    
    buzzer.stop();
    matrixDisplay.clear();
}

void GameEngine::checkRoomTransition()
{
    uint8_t currentCameraX = camera.getCameraX();
    uint8_t currentCameraY = camera.getCameraY();
    
    if (currentCameraX != lastCameraX || currentCameraY != lastCameraY)
    {
        buzzer.startPattern(BuzzerPattern::ROOM_TRANSITION, SoundDurations::ROOM_TRANSITION_MS);
        
        lastCameraX = currentCameraX;
        lastCameraY = currentCameraY;
    }
}

void GameEngine::checkWinCondition()
{
    if (!player.isOnExit())
    {
        return;
    }
    
    lcdDisplay.clear();
    lcdDisplay.printCentered(0, "LEVEL COMPLETE!");
    
    buzzer.startPattern(BuzzerPattern::LEVEL_COMPLETE, SoundDurations::LEVEL_COMPLETE_MS);
    
    delay(MessageDurations::LEVEL_COMPLETE_MS);
    
    if (currentLevel < MapConstants::MAX_LEVEL)
    {
        loadLevel(currentLevel + 1);
        
        lastCameraX = camera.getCameraX();
        lastCameraY = camera.getCameraY();
    }
    else
    {
        lcdDisplay.clear();
        lcdDisplay.printCentered(0, "YOU WIN!");
        lcdDisplay.printCentered(1, "All levels done");
        
        buzzer.startPattern(BuzzerPattern::GAME_WON, SoundDurations::GAME_WON_MS);
        
        delay(MessageDurations::GAME_WON_MS);
        
        gameState = GameState::MENU;
        showMenu();
    }
}
