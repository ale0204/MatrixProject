#include "GameEngine.h"

GameEngine::GameEngine(MatrixDisplay& matrix, LCDDisplay& lcd, Joystick& joy, Buzzer& buzz)
    : map()
    , player(&map)
    , camera(&player)
    , matrixDisplay(matrix)
    , lcdDisplay(lcd)
    , joystick(joy)
    , buzzer(buzz)
    , exitButton(ExitButtonPins::EXIT_BUTTON_PIN)
    , explosivePlacedTime(0)
    , gameState(GameState::MENU)
    , currentLevel(MapConstants::LEVEL_0)  
    , menuOption(0) 
    , settingsOption(0)  
    , highscoreScrollPos(0)  
    , nameEditPosition(0)
    , pendingHighscore(0)
    , nameEditEnteredTime(0)  
    , score(0)
    , explosivesUsedThisLevel(0)
    , lastUpdateTime(0)
    , lastLCDUpdate(0)
    , lastMenuNavigationTime(0)
    , lastSettingsNavigationTime(0)
    , feedbackTimer(0)
    , messageDisplayStartTime(0)
    , waitingForMessageDisplay(false)
    , stateAfterMessage(GameState::MENU)
    , aboutScrollOffset(0)
    , lastAboutScrollTime(0)
    , howToPlayScrollOffset(0)
    , lastHowToPlayScrollTime(0)
    , lastCameraX(0)
    , lastCameraY(0)
{
    editedName[0] = 'A';
    editedName[1] = 'A';
    editedName[2] = 'A';
    editedName[3] = '\0';
}

void GameEngine::begin()
{
    gameSettings.loadFromEEPROM();
    systemSettings.loadFromEEPROM();
    highscoreManager.loadFromEEPROM();
    
    exitButton.init();
    
    matrixDisplay.setBrightness(systemSettings.getMatrixBrightness());
    lcdDisplay.setBrightness(systemSettings.getLCDBrightness());
    
    showMenu();
}

void GameEngine::loadLevel(uint8_t levelIndex)
{
    currentLevel = levelIndex;
    
    map.loadLevel(levelIndex, &gameSettings);
    
    player.resetGold();
    
    if (levelIndex == gameSettings.getStartingLevel()) {
        uint8_t startingLives = gameSettings.getStartingLives();
        player.setLives(startingLives);
    }
    
    explosivesUsedThisLevel = 0;
    //    
    if (levelIndex == gameSettings.getStartingLevel()) {
        if (levelIndex == MapConstants::LEVEL_2 || levelIndex == MapConstants::LEVEL_3) {
            player.resetExplosives();  
        } else {
            player.setExplosivesCount(0);
        }
    }
    else if (levelIndex == MapConstants::LEVEL_2) {
        player.resetExplosives();
    }
    
    player.setPosition(SpawnConstants::DEFAULT_SPAWN_X, SpawnConstants::DEFAULT_SPAWN_Y);
    
    activeExplosive.deactivate();
    explosivePlacedTime = 0;
    
    camera.update();
    
    playSound(ToneFrequencies::LEVEL_LOAD_HZ, SoundDurations::LEVEL_LOAD_TONE_MS);
    
    lcdDisplay.clear();
    lcdDisplay.printAt(0, 0, "Level ");
    lcdDisplay.printAt(LCDConstants::COLS / 2 - 1, 0, String(levelIndex + 1).c_str());
}

void GameEngine::update()
{
    unsigned long currentTime = millis();
    
    joystick.update();
    exitButton.update();  
    
    // Handle non-blocking message display delays
    if (waitingForMessageDisplay) {
    if (currentTime - messageDisplayStartTime >= TimingConstants::MESSAGE_DISPLAY_MS) {  // 1 second default
            waitingForMessageDisplay = false;
            gameState = stateAfterMessage;
            
            if (gameState == GameState::MENU) {
                showMenu();
            } else if (gameState == GameState::SETTINGS_MENU) {
                showSettingsMenu();
            } else if (gameState == GameState::HIGHSCORE_VIEW) {
                showHighscores();
            }
        }
    return;  // Don't process other inputs while waiting
    }
    
    if (gameState == GameState::MENU)
    {
    unsigned long currentTime = millis();
        
    bool canNavigate = (currentTime - lastMenuNavigationTime >= TimingConstants::MENU_NAVIGATION_COOLDOWN_MS);
        
    if (joystick.getDirection() == JoystickDirection::UP && canNavigate) {
            if (menuOption > 0) {
                menuOption--;
                showMenu();
                playSound(SoundFrequencies::NAVIGATION_BEEP_HZ, SoundDurationConstants::NAVIGATION_BEEP_MS);
                lastMenuNavigationTime = currentTime;
            }
        }
    else if (joystick.getDirection() == JoystickDirection::DOWN && canNavigate) {
            if (menuOption < MenuIndexConstants::MENU_MAX_OPTION) {
                menuOption++;
                showMenu();
                playSound(SoundFrequencies::NAVIGATION_BEEP_HZ, SoundDurationConstants::NAVIGATION_BEEP_MS);
                lastMenuNavigationTime = currentTime;
            }
        }
        
        // Confirm selection
    if (joystick.wasButtonPressed())
        {
            playSoundPattern(BuzzerPattern::MENU_SELECT, SoundDurations::MENU_SELECT_MS);
            
            if (menuOption == MenuIndexConstants::MENU_START_GAME) {
                gameState = GameState::PLAYING;
                uint8_t startLevel = gameSettings.getStartingLevel();
                loadLevel(startLevel);
                
                lastCameraX = camera.getCameraX();
                lastCameraY = camera.getCameraY();
            }
            else if (menuOption == MenuIndexConstants::MENU_SETTINGS) {
                // Settings
                settingsOption = MenuIndexConstants::SETTINGS_STARTING_LEVEL;
                gameState = GameState::SETTINGS_MENU;
                showSettingsMenu();
            }
            else if (menuOption == MenuIndexConstants::MENU_HIGHSCORES) {
                highscoreScrollPos = 0;
                gameState = GameState::HIGHSCORE_VIEW;
                showHighscores();
            }
            else if (menuOption == MenuIndexConstants::MENU_ABOUT) {
                aboutScrollOffset = 0;
                lastAboutScrollTime = currentTime;
                gameState = GameState::ABOUT;
                showAbout();
            }
            else if (menuOption == MenuIndexConstants::MENU_HOW_TO_PLAY) {
                howToPlayScrollOffset = 0;
                lastHowToPlayScrollTime = currentTime;
                gameState = GameState::HOW_TO_PLAY;
                showHowToPlay();
            }
        }
    return;
    }
    
    if (gameState == GameState::ABOUT)
    {
    if (currentTime - lastAboutScrollTime < TimingConstants::TEXT_SCROLL_START_DELAY_MS && aboutScrollOffset == 0) {
            // Wait before starting scroll
        }
    else if (currentTime - lastAboutScrollTime >= TimingConstants::TEXT_SCROLL_INTERVAL_MS) {
            aboutScrollOffset++;
            showAbout();
            lastAboutScrollTime = currentTime;
        }
        
    if (joystick.wasButtonPressed() || exitButton.wasPressed()) {
            aboutScrollOffset = 0;
            gameState = GameState::MENU;
            menuOption = 0;
            showMenu();
        }
    return;
    }
    
    if (gameState == GameState::HOW_TO_PLAY)
    {
    if (currentTime - lastHowToPlayScrollTime < TimingConstants::TEXT_SCROLL_START_DELAY_MS && howToPlayScrollOffset == 0) {
            // Wait before starting scroll
        }
    else if (currentTime - lastHowToPlayScrollTime >= TimingConstants::TEXT_SCROLL_INTERVAL_MS) {
            howToPlayScrollOffset++;
            showHowToPlay();
            lastHowToPlayScrollTime = currentTime;
        }
        
    if (joystick.wasButtonPressed() || exitButton.wasPressed()) {
            howToPlayScrollOffset = 0;
            gameState = GameState::MENU;
            menuOption = 0;
            showMenu();
        }
    return;
    }
    
    if (gameState == GameState::SETTINGS_MENU)
    {
    unsigned long currentTime = millis();
        
    JoystickDirection dir = joystick.getDirection();
        
    bool canNavigate = (currentTime - lastSettingsNavigationTime >= TimingConstants::SETTINGS_NAVIGATION_COOLDOWN_MS);
        
        // UP - Previous setting option
    if (dir == JoystickDirection::UP && canNavigate) {
            if (settingsOption > 0) {
                settingsOption--;
                showSettingsMenu();
                playSound(SoundFrequencies::NAVIGATION_BEEP_HZ, SoundDurationConstants::NAVIGATION_BEEP_MS);
                lastSettingsNavigationTime = currentTime;
            }
        }
        // DOWN - Next setting option
    else if (dir == JoystickDirection::DOWN && canNavigate) {
            if (settingsOption < MenuIndexConstants::SETTINGS_MAX_OPTION) {
                settingsOption++;
                showSettingsMenu();
                playSound(SoundFrequencies::NAVIGATION_BEEP_HZ, SoundDurationConstants::NAVIGATION_BEEP_MS);
                lastSettingsNavigationTime = currentTime;
            }
        }
        // LEFT - Decrease value
    else if (dir == JoystickDirection::LEFT && canNavigate) {
            switch (settingsOption) {
                case MenuIndexConstants::SETTINGS_STARTING_LEVEL: // Starting Level
                    if (gameSettings.getStartingLevel() > 0) {
                        gameSettings.setStartingLevel(gameSettings.getStartingLevel() - 1);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_DIFFICULTY: // Difficulty
                    if (gameSettings.getDifficulty() == GameSettings::Difficulty::NORMAL) {
                        gameSettings.setDifficulty(GameSettings::Difficulty::EASY);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    } else if (gameSettings.getDifficulty() == GameSettings::Difficulty::HARD) {
                        gameSettings.setDifficulty(GameSettings::Difficulty::NORMAL);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_LCD_BRIGHTNESS: // LCD Brightness
                    if (systemSettings.getLCDBrightness() > 0) {
                        systemSettings.setLCDBrightness(systemSettings.getLCDBrightness() - 1);
                        lcdDisplay.setBrightness(systemSettings.getLCDBrightness());
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_MATRIX_BRIGHTNESS: // Matrix Brightness
                    if (systemSettings.getMatrixBrightness() > 0) {
                        systemSettings.setMatrixBrightness(systemSettings.getMatrixBrightness() - 1);
                        matrixDisplay.setBrightness(systemSettings.getMatrixBrightness());
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_SOUND: // Sound
                    systemSettings.toggleSound();
                    showSettingsMenu();
                    playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                    lastSettingsNavigationTime = currentTime;
                    break;
                case MenuIndexConstants::SETTINGS_RESET: // Reset - no action on LEFT/RIGHT
                    break;
            }
        }
        // RIGHT - Increase value
    else if (dir == JoystickDirection::RIGHT && canNavigate) {
            switch (settingsOption) {
                case MenuIndexConstants::SETTINGS_STARTING_LEVEL: // Starting Level
                    if (gameSettings.getStartingLevel() < 3) {
                        gameSettings.setStartingLevel(gameSettings.getStartingLevel() + 1);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_DIFFICULTY: // Difficulty
                    if (gameSettings.getDifficulty() == GameSettings::Difficulty::EASY) {
                        gameSettings.setDifficulty(GameSettings::Difficulty::NORMAL);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    } else if (gameSettings.getDifficulty() == GameSettings::Difficulty::NORMAL) {
                        gameSettings.setDifficulty(GameSettings::Difficulty::HARD);
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_LCD_BRIGHTNESS: // LCD Brightness
                    if (systemSettings.getLCDBrightness() < SystemDefaultConstants::MAX_LCD_BRIGHTNESS) {
                        systemSettings.setLCDBrightness(systemSettings.getLCDBrightness() + 1);
                        lcdDisplay.setBrightness(systemSettings.getLCDBrightness());
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_MATRIX_BRIGHTNESS: // Matrix Brightness
                    if (systemSettings.getMatrixBrightness() < MatrixConstants::MAX_BRIGHTNESS) {
                        systemSettings.setMatrixBrightness(systemSettings.getMatrixBrightness() + 1);
                        matrixDisplay.setBrightness(systemSettings.getMatrixBrightness());
                        showSettingsMenu();
                        playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                        lastSettingsNavigationTime = currentTime;
                    }
                    break;
                case MenuIndexConstants::SETTINGS_SOUND: // Sound
                    systemSettings.toggleSound();
                    showSettingsMenu();
                    playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
                    lastSettingsNavigationTime = currentTime;
                    break;
                case MenuIndexConstants::SETTINGS_RESET: // Reset - no action on LEFT/RIGHT
                    break;
            }
        }
        
        // BUTTON PRESS on Reset option
    if (settingsOption == MenuIndexConstants::SETTINGS_RESET && joystick.wasButtonPressed()) {
            // Reset to defaults
            gameSettings.resetToDefaults();
            systemSettings.resetToDefaults();
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "Reset Done!");
            playSound(SoundFrequencies::RESET_DONE_HZ, SoundDurationConstants::RESET_DONE_MS);
            
            messageDisplayStartTime = millis();
            waitingForMessageDisplay = true;
            stateAfterMessage = GameState::SETTINGS_MENU;
            
            // Reapply brightness after reset
            matrixDisplay.setBrightness(systemSettings.getMatrixBrightness());
            lcdDisplay.setBrightness(systemSettings.getLCDBrightness());
            
            settingsOption = 0;  // Return to first option
            showSettingsMenu();
        }
        
        // EXIT BUTTON - Save and return to menu (pin 13)
    if (exitButton.wasPressed()) {
            gameSettings.saveToEEPROM();
            systemSettings.saveToEEPROM();
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "Settings Saved!");
            playSound(SoundFrequencies::SETTINGS_SAVE_HZ, SoundDurationConstants::SETTINGS_SAVE_MS);
            
            messageDisplayStartTime = millis();
            waitingForMessageDisplay = true;
            stateAfterMessage = GameState::MENU;
            return;
        }
        
        // LONG_PRESS - Save and return to menu
    if (joystick.isLongPress()) {
            gameSettings.saveToEEPROM();
            systemSettings.saveToEEPROM();
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "Settings Saved!");
            playSound(SoundFrequencies::SETTINGS_SAVE_HZ, SoundDurationConstants::SETTINGS_SAVE_MS);
            
            messageDisplayStartTime = millis();
            waitingForMessageDisplay = true;
            stateAfterMessage = GameState::MENU;
            return;
        }
        
    return;
    }
    
    if (gameState == GameState::HIGHSCORE_VIEW)
    {
    JoystickDirection dir = joystick.getDirection();
        
    if (dir == JoystickDirection::DOWN) {
            if (highscoreScrollPos < 1 && (millis() - lastSettingsNavigationTime >= TimingConstants::HIGHSCORE_SCROLL_COOLDOWN_MS)) {
                highscoreScrollPos++;
                showHighscores();
                playSound(SoundFrequencies::HIGHSCORE_SCROLL_HZ, SoundDurationConstants::HIGHSCORE_SCROLL_MS);
                lastSettingsNavigationTime = millis();
            }
        }
    else if (dir == JoystickDirection::UP) {
            if (highscoreScrollPos > 0 && (millis() - lastSettingsNavigationTime >= TimingConstants::HIGHSCORE_SCROLL_COOLDOWN_MS)) {
                highscoreScrollPos--;
                showHighscores();
                playSound(SoundFrequencies::HIGHSCORE_SCROLL_HZ, SoundDurationConstants::HIGHSCORE_SCROLL_MS);
                lastSettingsNavigationTime = millis();
            }
        }
        
    if (joystick.isLongPress()) {
        lcdDisplay.clear();
        lcdDisplay.printCentered(0, "Reset Scores?");
        lcdDisplay.printCentered(1, "Press again");
        playSound(SoundFrequencies::RESET_PROMPT_HZ, SoundDurationConstants::RESET_PROMPT_MS);
        
        while (joystick.isButtonPressed()) {
            joystick.update();
        }
        
        joystick.update();
        joystick.wasButtonPressed();  // instead of a delay, acts the same
        
        unsigned long confirmStart = millis();
        bool confirmed = false;
        
        while (millis() - confirmStart < TimingConstants::CONFIRM_TIMEOUT_MS) { 
            joystick.update();
            if (joystick.wasButtonPressed()) {
                confirmed = true;
                break;
            }
        }
        
        if (confirmed) {
            highscoreManager.resetHighscores();
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "Scores Reset!");
            playSound(SoundFrequencies::RESET_DONE_HZ, SoundDurationConstants::RESET_DONE_MS);
            
            messageDisplayStartTime = millis();
            waitingForMessageDisplay = true;
            stateAfterMessage = GameState::HIGHSCORE_VIEW;
            highscoreScrollPos = 0;
            return;
        } else {
            showHighscores();
        }
        return;
    }
        
    if (joystick.wasButtonPressed() || exitButton.wasPressed()) {
            highscoreScrollPos = 0;  // Reset scroll
            gameState = GameState::MENU;
            menuOption = 0;
            showMenu();
        }
    return;
    }
    
    if (gameState == GameState::NAME_EDIT)
    {
    if (currentTime - nameEditEnteredTime < TimingConstants::NAME_EDIT_INITIAL_DELAY_MS) {
        showNameEditor();
        return;  // Skip input processing
    }
        
    JoystickDirection dir = joystick.getDirection();

    if (dir == JoystickDirection::UP && (currentTime - lastSettingsNavigationTime >= TimingConstants::NAME_CHAR_CHANGE_COOLDOWN_MS)) {
        editedName[nameEditPosition]++;
        if (editedName[nameEditPosition] > 'Z') {
            editedName[nameEditPosition] = 'A';
    }
    nameWasModified = true;
    showNameEditor();
    playSound(SoundFrequencies::NAME_CHAR_EDIT_HZ, SoundDurationConstants::NAME_CHAR_EDIT_MS);
    lastSettingsNavigationTime = currentTime;
    }
    else if (dir == JoystickDirection::DOWN && (currentTime - lastSettingsNavigationTime >= TimingConstants::NAME_CHAR_CHANGE_COOLDOWN_MS)) {
        editedName[nameEditPosition]--;
        if (editedName[nameEditPosition] < 'A') {
            editedName[nameEditPosition] = 'Z';
        }
        nameWasModified = true;              
        showNameEditor();
        playSound(SoundFrequencies::NAME_CHAR_EDIT_HZ, SoundDurationConstants::NAME_CHAR_EDIT_MS);
        lastSettingsNavigationTime = currentTime;
    }
        // RIGHT - Next character (0→1→2)
    else if (dir == JoystickDirection::RIGHT && (currentTime - lastSettingsNavigationTime >= TimingConstants::NAME_CHAR_NAVIGATE_COOLDOWN_MS)) {
        if (nameEditPosition < 2) {
            nameEditPosition++;
            showNameEditor();
            playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
            lastSettingsNavigationTime = currentTime;
        }
    }
        // LEFT - Previous character (2→1→0)
    else if (dir == JoystickDirection::LEFT && (currentTime - lastSettingsNavigationTime >= TimingConstants::SETTINGS_NAVIGATION_COOLDOWN_MS)) 
    {
        if (nameEditPosition > 0) {
            nameEditPosition--;
            showNameEditor();
            playSound(SoundFrequencies::SETTINGS_CHANGE_HZ, SoundDurationConstants::SETTINGS_CHANGE_MS);
            lastSettingsNavigationTime = currentTime;
        }
    }
    
        if ((joystick.wasButtonPressed() || joystick.isLongPress()) && 
            (nameWasModified || (currentTime - nameEditEnteredTime >= TimingConstants::NAME_EDIT_TIMEOUT_MS))) 
    {
        highscoreManager.insertHighscore(editedName, pendingHighscore, gameSettings.getStartingLevel());
        
        lcdDisplay.clear();
        lcdDisplay.printCentered(0, "Highscore Saved!");
        playSound(SoundFrequencies::HIGHSCORE_SAVED_HZ, SoundDurationConstants::HIGHSCORE_SAVED_MS);
        
        gameState = GameState::HIGHSCORE_VIEW;
        feedbackTimer = currentTime;  // Mark time for potential future use
        showHighscores();
    }
        
    return;
    }
    
    buzzer.updatePattern();
    
    // Handle feedback states with non-blocking timers
    if (gameState == GameState::BOMB_FEEDBACK)
    {
    if (currentTime - feedbackTimer >= TimingConstants::BOMB_FEEDBACK_MS)
        {
            if (player.isDead())
            {
                gameState = GameState::GAME_OVER_FEEDBACK;
                feedbackTimer = currentTime;
                
                lcdDisplay.clear();
                lcdDisplay.printCentered(0, "GAME OVER!");
                lcdDisplay.printCentered(1, "No lives left");
                playSoundPattern(BuzzerPattern::GAME_OVER, TimingConstants::GAME_OVER_SOUND_MS);
            }
            else
            {
                gameState = GameState::PLAYING;
            }
        }
    matrixDisplay.draw(map, player, camera);
    return;
    }
    
    if (gameState == GameState::GAME_OVER_FEEDBACK)
    {
    if (currentTime - feedbackTimer >= TimingConstants::GAME_OVER_FEEDBACK_MS)
        {
            score = 0;
            gameState = GameState::MENU;
            showMenu();
            matrixDisplay.clear();
            return;
        }
    matrixDisplay.draw(map, player, camera);
    return;
    }
    
    if (gameState == GameState::LEVEL_COMPLETE_FEEDBACK)
    {
    bool shouldProceed = (currentTime - feedbackTimer >= MessageDurations::LEVEL_COMPLETE_MS);
        
    if (exitButton.isPressed()) {
            shouldProceed = true;
        }
        
    if (shouldProceed)
        {
            if (currentLevel < MapConstants::MAX_LEVEL)
            {
                gameState = GameState::LEVEL_STATS;
                showLevelStats();
            }
            else
            {
                gameState = GameState::GAME_WON_FEEDBACK;
                feedbackTimer = currentTime;
                
                lcdDisplay.clear();
                lcdDisplay.printCentered(0, "YOU WIN!");
                
                char finalScore[LCDConstants::SMALL_BUFFER_SIZE];
                sprintf(finalScore, "Score: %d", score);
                lcdDisplay.printCentered(1, finalScore);
                
                playSoundPattern(BuzzerPattern::GAME_WON, SoundDurations::GAME_WON_MS);
            }
        }
    matrixDisplay.draw(map, player, camera);
    return;
    }
    
    if (gameState == GameState::LEVEL_STATS)
    {
    if (joystick.wasButtonPressed())
        {
            loadLevel(currentLevel + 1);
            lastCameraX = camera.getCameraX();
            lastCameraY = camera.getCameraY();
            gameState = GameState::PLAYING;
        }
    matrixDisplay.draw(map, player, camera);
    return;
    }
    
    if (gameState == GameState::GAME_WON_FEEDBACK)
    {
    if (pendingHighscore > 0 && (currentTime - feedbackTimer >= TimingConstants::GAME_WON_NAME_ENTRY_DELAY_MS)) {
        nameEditPosition = 0;
        nameWasModified = false;
        
        const char* currentName = systemSettings.getPlayerName();
        editedName[0] = currentName[0];
        editedName[1] = currentName[1];
        editedName[2] = currentName[2];
        editedName[3] = '\0';
        
        gameState = GameState::NAME_EDIT;
        nameEditEnteredTime = currentTime;
        lastSettingsNavigationTime = currentTime;  // Reset debounce timer
        showNameEditor();
        return;
    }
        
    if (currentTime - feedbackTimer >= MessageDurations::GAME_WON_MS)
        {
            if (pendingHighscore == 0 && highscoreManager.isHighscore(score)) {
                lcdDisplay.clear();
                lcdDisplay.printCentered(0, "NEW HIGHSCORE!");
                
                char scoreMsg[SystemDefaultConstants::LCD_BUFFER_SIZE];
                uint8_t position = highscoreManager.getHighscorePosition(score);
                sprintf(scoreMsg, "Rank #%d: %d", position + 1, score);
                lcdDisplay.printCentered(1, scoreMsg);
                
                playSoundPattern(BuzzerPattern::COLLECT_GOLD, TimingConstants::TREASURE_COLLECT_SOUND_MS);
                feedbackTimer = currentTime;
                                  
                pendingHighscore = score;
                score = 0;                  
                return;
            } else {
                score = 0;
                gameState = GameState::MENU;
                showMenu();
                matrixDisplay.clear();
            }
            return;
        }
    matrixDisplay.draw(map, player, camera);
    return;
    }
    
    // Normal PLAYING state
    
    if (exitButton.wasPressed()) {
    score = 0;
    activeExplosive.deactivate();
    explosivePlacedTime = 0;
    gameState = GameState::MENU;
    showMenu();
    matrixDisplay.clear();
    return;
    }
    
    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
    {
    lastUpdateTime = currentTime;
        
    handleInput();
    checkExplosivePlacement();
    camera.update();
    checkRoomTransition();
    checkWinCondition();
    }
    
    static unsigned long lastProximityBeep = 0;
    if (player.isNearHiddenTreasure())
    {
    if (currentTime - lastProximityBeep >= TimingConstants::PROXIMITY_BEEP_INTERVAL_MS)
        {
            lastProximityBeep = currentTime;
            playSound(SoundFrequencies::TREASURE_PROXIMITY_HZ, SoundDurationConstants::SHORT_BEEP_MS);
        }
    }
    
    if (activeExplosive.isActive() && 
        explosivePlacedTime != 0 &&
        currentTime >= explosivePlacedTime &&
        (currentTime - explosivePlacedTime >= ExplosiveConstants::EXPLOSION_DELAY_MS))
    {
        handleExplosion();
    }
    
    if (currentTime - lastLCDUpdate >= LCD_UPDATE_INTERVAL)
    {
        lastLCDUpdate = currentTime;
        
        bool recentBombPlaced = (activeExplosive.isActive() && 
                                 explosivePlacedTime != 0 && 
                                 (currentTime - explosivePlacedTime < TimingConstants::BOMB_PLACED_LCD_DISPLAY_MS));
        
        if (!recentBombPlaced) {
            updateLCD();
        }
    }
    
    matrixDisplay.draw(map, player, camera);
    
    if (activeExplosive.isActive())
    {
        uint8_t ex = activeExplosive.getX();
        uint8_t ey = activeExplosive.getY();
        
        uint8_t camX = camera.getCameraX();
        uint8_t camY = camera.getCameraY();
        
        if (ex >= camX && ex < camX + 8 && ey >= camY && ey < camY + 8)
        {
            uint8_t localX = ex - camX;
            uint8_t localY = ey - camY;
            
            bool blink = (matrixDisplay.getFrameCounter() % GameplayConstants::EXPLOSIVE_BLINK_CYCLE < GameplayConstants::EXPLOSIVE_BLINK_ON_FRAMES);
            
            matrixDisplay.setLed(localX, localY, blink);
        }
    }
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
    uint8_t livesBefore = player.getLives();
    
    player.move(dx, dy);
    
    uint8_t goldAfter = player.getGoldCollected();
    uint8_t livesAfter = player.getLives();
    
    if (goldAfter > goldBefore)
    {
    score += GameplayConstants::GOLD_COLLECT_SCORE;
    playSoundPattern(BuzzerPattern::COLLECT_GOLD, SoundDurations::COLLECT_GOLD_MS);
    }
    
    if (livesAfter < livesBefore)
    {
    playSoundPattern(BuzzerPattern::HIT_BOMB, GameplayConstants::EXPLOSION_SOUND_DURATION_MS);
        
    lcdDisplay.clear();
    lcdDisplay.printCentered(0, "BOOM!");
        
    char buffer[LCDConstants::SMALL_BUFFER_SIZE];
    sprintf(buffer, "Lives: %d", livesAfter);
    lcdDisplay.printCentered(1, buffer);
        
    gameState = GameState::BOMB_FEEDBACK;
    feedbackTimer = millis();
    }
}

void GameEngine::updateLCD()
{
    lcdDisplay.clearLine(0);
    lcdDisplay.clearLine(1);
    
    char buffer[DisplayConstants::LCD_BUFFER_SIZE];
    uint8_t collected = player.getGoldCollected();
    uint8_t total = map.getTotalGold();
    uint8_t explosives = player.getExplosivesCount();
    uint8_t lives = player.getLives();
    
    sprintf(buffer, "G:%d/%d E:%d S:%d", collected, total, explosives, score);
    lcdDisplay.printAt(0, 0, buffer);
    
    sprintf(buffer, "Lvl:%d L:%d", currentLevel + 1, lives);
    lcdDisplay.printAt(0, 1, buffer);
}

void GameEngine::showMenu()
{
    lcdDisplay.clear();
    
    if (menuOption == MenuIndexConstants::MENU_START_GAME) {
        lcdDisplay.printAt(0, 0, ">Start Game");
        lcdDisplay.printAt(0, 1, " Settings");
    } else if (menuOption == MenuIndexConstants::MENU_SETTINGS) {
        lcdDisplay.printAt(0, 0, " Start Game");
        lcdDisplay.printAt(0, 1, ">Settings");
    } else if (menuOption == MenuIndexConstants::MENU_HIGHSCORES) {
        lcdDisplay.printAt(0, 0, " Settings");
        lcdDisplay.printAt(0, 1, ">Highscores");
    } else if (menuOption == MenuIndexConstants::MENU_ABOUT) {
        lcdDisplay.printAt(0, 0, " Highscores");
        lcdDisplay.printAt(0, 1, ">About");
    } else if (menuOption == MenuIndexConstants::MENU_HOW_TO_PLAY) {
        lcdDisplay.printAt(0, 0, " About");
        lcdDisplay.printAt(0, 1, ">How to Play");
    }
    
    buzzer.stop();
    matrixDisplay.clear();
    
    if (menuOption == MenuIndexConstants::MENU_START_GAME) {
        drawStartIcon();
    }
    else if (menuOption == MenuIndexConstants::MENU_SETTINGS) {
        drawSettingsIcon();
    }
    else if (menuOption == MenuIndexConstants::MENU_HIGHSCORES) {
        drawTrophyIcon();
    }
    else if (menuOption == MenuIndexConstants::MENU_ABOUT) {
        drawAboutIcon();
    }
    else if (menuOption == MenuIndexConstants::MENU_HOW_TO_PLAY) {
        drawHowToPlayIcon();
    }
}

void GameEngine::showSettingsMenu()
{
    lcdDisplay.clear();
    
    matrixDisplay.clear();
    
    // Display option name on row 0, value with arrows on row 1
    switch (settingsOption) {
    case MenuIndexConstants::SETTINGS_STARTING_LEVEL: // Starting Level
            lcdDisplay.printAt(0, 0, "Starting Level");
            {
                String value = "<     " + String(gameSettings.getStartingLevel() + 1) + "     >";
                lcdDisplay.printAt(0, 1, value.c_str());
            }
            break;
    case MenuIndexConstants::SETTINGS_DIFFICULTY: // Difficulty
            lcdDisplay.printAt(0, 0, "Difficulty");
            switch (gameSettings.getDifficulty()) {
                case GameSettings::Difficulty::EASY:
                    lcdDisplay.printAt(0, 1, "<   Easy   >");
                    break;
                case GameSettings::Difficulty::NORMAL:
                    lcdDisplay.printAt(0, 1, "<  Normal  >");
                    break;
                case GameSettings::Difficulty::HARD:
                    lcdDisplay.printAt(0, 1, "<   Hard   >");
                    break;
            }
            break;
    case MenuIndexConstants::SETTINGS_LCD_BRIGHTNESS: // LCD Brightness
            lcdDisplay.printAt(0, 0, "LCD Bright");
            {
                String value = "<   " + String(systemSettings.getLCDBrightness()) + "   >";
                lcdDisplay.printAt(0, 1, value.c_str());
            }
            break;
    case MenuIndexConstants::SETTINGS_MATRIX_BRIGHTNESS: // Matrix Brightness
            lcdDisplay.printAt(0, 0, "Matrix Bright");
            {
                String value = "<    " + String(systemSettings.getMatrixBrightness()) + "    >";
                lcdDisplay.printAt(0, 1, value.c_str());
                
                matrixDisplay.clear();
                matrixDisplay.setLed(3, 3, true);
                matrixDisplay.setLed(3, 4, true);
                matrixDisplay.setLed(4, 3, true);
                matrixDisplay.setLed(4, 4, true);
            }
            break; 
    case MenuIndexConstants::SETTINGS_SOUND: // Sound
            lcdDisplay.printAt(0, 0, "Sound");
            if (systemSettings.isSoundEnabled()) {
                lcdDisplay.printAt(0, 1, "<    ON    >");
            } else {
                lcdDisplay.printAt(0, 1, "<   OFF    >");
            }
            break;
    case MenuIndexConstants::SETTINGS_RESET: // Reset to Defaults
            lcdDisplay.printAt(0, 0, "Reset Settings");
            lcdDisplay.printAt(0, 1, "  Press Button  ");
            break;
    }
}

void GameEngine::checkRoomTransition()
{
    uint8_t currentCameraX = camera.getCameraX();
    uint8_t currentCameraY = camera.getCameraY();
    
    if (currentCameraX != lastCameraX || currentCameraY != lastCameraY)
    {
    playSoundPattern(BuzzerPattern::ROOM_TRANSITION, SoundDurations::ROOM_TRANSITION_MS);
        
    lastCameraX = currentCameraX;
    lastCameraY = currentCameraY;
    }
}

void GameEngine::checkWinCondition()
{
    // bool shouldExit = false;
    // if (player.isOnExit() && !shouldExit)
    // {
    //     shouldExit = true;
    // }
    // else if(shouldExit)
    // {
    //     shouldExit = false;
    //     return;
    // }
    if (!player.isOnExit())
    return;
    
    uint8_t collected = player.getGoldCollected();
    uint8_t total = map.getTotalGold();
    if (collected == total) {
    score += GameplayConstants::LEVEL_COMPLETE_BONUS;  
    }
    
    uint8_t lives = player.getLives();
    score += lives * GameplayConstants::LIFE_BONUS_MULTIPLIER;
    
    if (currentLevel == MapConstants::LEVEL_3) {
    uint8_t explosivesLeft = player.getExplosivesCount();
        if (explosivesLeft == 3) {
            score += GameplayConstants::EXPLOSIVES_BONUS_THREE;
        } else if (explosivesLeft == 2) {
            score += GameplayConstants::EXPLOSIVES_BONUS_TWO;  
        } else if (explosivesLeft == 1) {
            score += GameplayConstants::EXPLOSIVES_BONUS_ONE;  
        }
    }
    
    float multiplier = gameSettings.getScoreMultiplier();
    uint16_t finalScore = (uint16_t)(score * multiplier);

    lcdDisplay.clear();
    char congratsMsg[SystemDefaultConstants::LCD_BUFFER_SIZE];
    sprintf(congratsMsg, "Congrats lvl %d", currentLevel + 1);
    lcdDisplay.printCentered(0, congratsMsg);
    
    char scoreBuffer[LCDConstants::SMALL_BUFFER_SIZE];
    sprintf(scoreBuffer, "Score: %d", finalScore);
    lcdDisplay.printCentered(1, scoreBuffer);
    
    playSoundPattern(BuzzerPattern::LEVEL_COMPLETE, SoundDurations::LEVEL_COMPLETE_MS);
    
    gameState = GameState::LEVEL_COMPLETE_FEEDBACK;
    feedbackTimer = millis();
}

void GameEngine::checkExplosivePlacement()
{
    if (joystick.isLongPress())
    {
        if (activeExplosive.isActive())
        {
            playSound(SoundFrequencies::ERROR_BEEP_HZ, SoundDurationConstants::ERROR_BEEP_MS);
            return;  
        }
        
        if (player.hasExplosives())
        {
            uint8_t playerX = player.getX();
            uint8_t playerY = player.getY();
            
            explosivePlacedTime = millis();
            activeExplosive.place(playerX, playerY);
            player.setExplosivesCount(player.getExplosivesCount() - 1);
            explosivesUsedThisLevel++;
            playSound(SoundFrequencies::EXPLOSIVE_PLACED_HZ, SoundDurationConstants::SHORT_BEEP_MS);
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "RUN! 5s boom!");
            
            char buffer[LCDConstants::SMALL_BUFFER_SIZE];
            sprintf(buffer, "Left: %d", player.getExplosivesCount());
            lcdDisplay.printCentered(1, buffer);
        }
        else
        {
            playSound(SoundFrequencies::ERROR_BEEP_HZ, SoundDurationConstants::ERROR_BEEP_MS);
        }
    }
}

void GameEngine::handleExplosion()
{
    uint8_t ex = activeExplosive.getX();
    uint8_t ey = activeExplosive.getY();
    
    activeExplosive.deactivate();
    explosivePlacedTime = 0;      
    uint8_t playerX = player.getX();
    uint8_t playerY = player.getY();
    
    if (playerX == ex && playerY == ey)
    {
        player.setLives(0);
        
        lcdDisplay.clear();
        lcdDisplay.printCentered(0, "FATAL BOOM!");
        lcdDisplay.printCentered(1, "Direct hit!");
        
        gameState = GameState::BOMB_FEEDBACK;  
        feedbackTimer = millis();
    }
    else if ((playerX == ex - 1 && playerY == ey) ||               
             (playerX == ex + 1 && playerY == ey) ||  
             (playerX == ex && playerY == ey - 1) ||  
             (playerX == ex && playerY == ey + 1))    
    {
        if (player.getLives() > 0)
        {
            player.setLives(player.getLives() - 1);
            
            lcdDisplay.clear();
            lcdDisplay.printCentered(0, "Hit by blast!");
            
            char buffer[LCDConstants::SMALL_BUFFER_SIZE];
            sprintf(buffer, "Lives: %d", player.getLives());
            lcdDisplay.printCentered(1, buffer);
            
            gameState = GameState::BOMB_FEEDBACK; 
            feedbackTimer = millis();
        }
    }
    
    playSoundPattern(BuzzerPattern::HIT_BOMB, GameplayConstants::EXPLOSION_SOUND_DURATION_MS);
    
    const int8_t explosionPattern[GameplayConstants::EXPLOSION_PATTERN_SIZE][2] = {
        {0, 0},    
        {-1, 0},  
        {1, 0},   
        {0, -1},  
        {0, 1}    
    };
    
    for (int i = 0; i < GameplayConstants::EXPLOSION_PATTERN_SIZE; i++)
    {
        int16_t targetX = (int16_t)ex + explosionPattern[i][0];
        int16_t targetY = (int16_t)ey + explosionPattern[i][1];
        
        if (targetX < 0 || targetX >= MapConstants::WORLD_SIZE || 
            targetY < 0 || targetY >= MapConstants::WORLD_SIZE)
        {
            continue;  // Out of bounds
        }
        
        if (targetX == MapBoundaryConstants::MAP_BOUNDARY_MIN || 
            targetX == MapBoundaryConstants::ROOM_SEPARATOR_LOWER || 
            targetX == MapBoundaryConstants::ROOM_SEPARATOR_UPPER || 
            targetX == MapBoundaryConstants::MAP_BOUNDARY_MAX ||
            targetY == MapBoundaryConstants::MAP_BOUNDARY_MIN || 
            targetY == MapBoundaryConstants::ROOM_SEPARATOR_LOWER || 
            targetY == MapBoundaryConstants::ROOM_SEPARATOR_UPPER || 
            targetY == MapBoundaryConstants::MAP_BOUNDARY_MAX)
        {
            continue; 
        }
        
        uint8_t safeX = (uint8_t)targetX;
        uint8_t safeY = (uint8_t)targetY;
        
        TileType tile = map.getTile(safeX, safeY);
        
        if (tile != TileType::EXIT && tile != TileType::DOOR && tile != TileType::HIDDEN_GOLD)
        {
            map.setTile(safeX, safeY, TileType::EMPTY);
        }
    }
    
    for (int i = 0; i < GameplayConstants::EXPLOSION_PATTERN_SIZE; i++)
    {
        int16_t checkX = (int16_t)ex + explosionPattern[i][0];
        int16_t checkY = (int16_t)ey + explosionPattern[i][1];
        
        if (checkX < 0 || checkX >= MapConstants::WORLD_SIZE || 
            checkY < 0 || checkY >= MapConstants::WORLD_SIZE)
        {
            continue;
        }
        
        uint8_t safeX = (uint8_t)checkX;
        uint8_t safeY = (uint8_t)checkY;
        
        const int8_t neighbors[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        
        for (int j = 0; j < 4; j++)
        {
            int16_t nx = checkX + neighbors[j][0];
            int16_t ny = checkY + neighbors[j][1];
            
            if (nx >= 0 && nx < MapConstants::WORLD_SIZE && 
                ny >= 0 && ny < MapConstants::WORLD_SIZE)
            {
                if (map.getTile(nx, ny) == TileType::HIDDEN_GOLD && 
                    map.getTile(safeX, safeY) == TileType::EMPTY)
                {
                    map.setTile(nx, ny, TileType::GOLD);
                }
            }
        }
    }
}

void GameEngine::playSound(uint16_t frequency, uint16_t duration)
{
    if (systemSettings.isSoundEnabled()) {
    buzzer.playTone(frequency, duration);
    }
}

void GameEngine::playSoundPattern(BuzzerPattern pattern, uint16_t duration)
{
    if (systemSettings.isSoundEnabled()) {
    buzzer.startPattern(pattern, duration);
    }
}

void GameEngine::showHighscores()
{
    lcdDisplay.clear();
    matrixDisplay.clear();      
    char buffer[SystemDefaultConstants::LCD_BUFFER_SIZE];
    
    if (highscoreScrollPos == 0) {
    const HighscoreEntry& entry1 = highscoreManager.getEntry(0);
    const HighscoreEntry& entry2 = highscoreManager.getEntry(1);
        
    if (entry1.score > 0) {
        sprintf(buffer, "1.%c%c%c %d", 
                entry1.name[0], entry1.name[1], entry1.name[2], 
                entry1.score);
    } else 
    {
        sprintf(buffer, "1.--- 0");
    }
    lcdDisplay.printAt(0, 0, buffer);
        
    if (entry2.score > 0) {
        sprintf(buffer, "2.%c%c%c %d", 
                entry2.name[0], entry2.name[1], entry2.name[2], 
                entry2.score);
    } else 
    {
        sprintf(buffer, "2.--- 0");
    }
    lcdDisplay.printAt(0, 1, buffer);
    }
    else {
        const HighscoreEntry& entry2 = highscoreManager.getEntry(1);
        const HighscoreEntry& entry3 = highscoreManager.getEntry(2);
        
        if (entry2.score > 0) {
            sprintf(buffer, "2.%c%c%c %d", 
                    entry2.name[0], entry2.name[1], entry2.name[2], 
                    entry2.score);
        } 
        else {
            sprintf(buffer, "2.--- 0");
        }
    lcdDisplay.printAt(0, 0, buffer);
        
    if (entry3.score > 0) {
        sprintf(buffer, "3.%c%c%c %d", 
                entry3.name[0], entry3.name[1], entry3.name[2], 
                entry3.score);
        lcdDisplay.printAt(0, 1, buffer);
    } else 
    {
        sprintf(buffer, "3.--- 0");
        lcdDisplay.printAt(0, 1, buffer);
    }
    }
    
    lcdDisplay.printAt(10, 1, "H:rst");
}

void GameEngine::showNameEditor()
{
    lcdDisplay.clear();
    
    lcdDisplay.printAt(0, 0, "Enter Name:");
    
    char display[SystemDefaultConstants::LCD_BUFFER_SIZE];
    sprintf(display, " %c %c %c", 
            editedName[0], 
            editedName[1], 
            editedName[2]);
    lcdDisplay.printAt(0, 1, display);
    
    uint8_t cursorPos = 1 + nameEditPosition * 2;
    lcdDisplay.printAt(cursorPos, 1, "_");
    lcdDisplay.printAt(cursorPos, 1, String(editedName[nameEditPosition]).c_str());
}

void GameEngine::showAbout()
{
    lcdDisplay.clear();
    
    const char* fullText = "The Miner by Alexandra Neamtu   Github: github.com/ale0204   ";
    uint8_t textLen = strlen(fullText);
    
    uint8_t offset = aboutScrollOffset % textLen;
    
    char line[SystemDefaultConstants::LCD_BUFFER_SIZE];
    for (uint8_t i = 0; i < LCDConstants::COLS; i++) {
    line[i] = fullText[(offset + i) % textLen];
    }
    line[LCDConstants::COLS] = '\0';
    
    lcdDisplay.printAt(0, 0, line);
    lcdDisplay.printAt(0, 1, "Press to exit");
    
    matrixDisplay.clear();
}

void GameEngine::showHowToPlay()
{
    lcdDisplay.clear();
    
    const char* fullText = "Collect gold! Avoid bombs using light. Place explosives to get hidden gold.   ";
    uint8_t textLen = strlen(fullText);
    
    uint8_t offset = howToPlayScrollOffset % textLen;
    
    char line[SystemDefaultConstants::LCD_BUFFER_SIZE];
    for (uint8_t i = 0; i < LCDConstants::COLS; i++) {
    line[i] = fullText[(offset + i) % textLen];
    }
    line[LCDConstants::COLS] = '\0';
    
    lcdDisplay.printAt(0, 0, line);
    lcdDisplay.printAt(0, 1, "Press to exit");
    
    matrixDisplay.clear();
}

void GameEngine::showLevelStats()
{
    lcdDisplay.clear();
    
    char line1[SystemDefaultConstants::LCD_BUFFER_SIZE];
    sprintf(line1, "Score:%d Life:%d", score, player.getLives());
    lcdDisplay.printAt(0, 0, line1);
    
    char line2[SystemDefaultConstants::LCD_BUFFER_SIZE];
    sprintf(line2, "Exp:%d Press BTN", explosivesUsedThisLevel);
    lcdDisplay.printAt(0, 1, line2);
    
    matrixDisplay.clear();
}

void GameEngine::drawIcon(const byte pattern[MatrixConstants::SIZE])
{
    matrixDisplay.clear();
    for (uint8_t row = 0; row < MatrixConstants::SIZE; row++) {
    for (uint8_t col = 0; col < MatrixConstants::SIZE; col++) {
            bool isLit = (pattern[row] >> (MatrixConstants::SIZE - 1 - col)) & 0x01;
            if (isLit) 
            {
                matrixDisplay.setLed(col, row, true);
            }
        }
    }
}

void GameEngine::drawStartIcon()
{
    const byte pattern[8] = {
    B00000000,
    B00100100,
    B00000000,
    B00000000,
    B01000010,
    B00111100,
    B00000000,
    B00000000

    };
    drawIcon(pattern);
}

void GameEngine::drawSettingsIcon()
{
    const byte pattern[8] = {
    B00111100,
    B00111100,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000
    };
    drawIcon(pattern);
}

void GameEngine::drawTrophyIcon()
{
    const byte pattern[8] = {
    B00111100,
    B01111110,
    B00111100,
    B00011000,
    B00011000,
    B00011000,
    B00111100,
    B01111110
    };
    drawIcon(pattern);
}

void GameEngine::drawAboutIcon()
{
    const byte pattern[8] = {
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B00011000
    };
    drawIcon(pattern);
}

void GameEngine::drawHowToPlayIcon()
{
    const byte pattern[8] = {
    B00111100,
    B01111110,
    B01000010,
    B00001100,
    B00011000,
    B00011000,
    B00000000,
    B00011000
    };
    drawIcon(pattern);
}

