# MatrixProject - Introduction to Robotics

## Robotics Matrix Game Project - University of Bucharest, FMI  
### Introduction to Robotics (2025 - 2026)

Welcome to my LED Matrix game project developed for the **Introduction to Robotics** course!  
This repository contains the full implementation of my **8x8 LED Matrix Game**, built using **Arduino**, an **LCD display**, and **joystick input**, following the official project requirements.

This project started from a basic interactive demo for **Checkpoint 1** expanding into a fully featured game with menus, settings, animations, and scoring.

---

- **Student:** Neamtu Alexandra  
- **University:** University of Bucharest  
- **Faculty:** Faculty of Mathematics and Informatics  
- **Course:** Introduction to Robotics  
- **Academic Year:** 2025-2026, Semester 1

---

## Project Overview

This repository is dedicated exclusively to the **Matrix Game Project**, which is a standalone project.

The project is built around:
- An **8x8 LED matrix controlled via MAX7219**
- A **16x2 LCD display** for menu and game information
- A **joystick** for navigation and control
- A **modular C++ architecture** using multiple classes for clean design

The final result is a complete interactive game called **"The Miner"** that includes:
- A visual **LCD-based menu system**
- **Joystick-controlled gameplay** with intuitive controls
- **LED matrix animations** and smooth rendering
- **Progressive difficulty** across 4 handcrafted levels
- **Highscore system** with EEPROM persistence
- **Settings and sound control** with full customization

---

## Backstory & Inspiration

This project draws inspiration from **"The Wisdom of the Elders"** side mission in *Red Dead Redemption 2*, my favorite game. In that mission, Arthur Morgan investigates a mysterious curse affecting the people of Butcher Creek. The investigation leads him to Elysian Pool and into an abandoned mine where toxic waste and arsenic have been poisoning the water supply.

What captivated me most was the **mine exploration sequence** where Arthur must use explosives to clear blocked paths while searching for valuables scattered throughout the cave. The dark, atmospheric tunnels combined with strategic explosive usage created a memorable gameplay experience. Although this Arduino game doesn't tie directly with RDR2's story, I transformed that atmospheric mine exploration concept into an 8x8 LED matrix puzzle game, capturing the essence of navigating dark tunnels, collecting gold, and using explosives strategically to reveal hidden treasures.

---

## Game Description

**The Miner** is a top-down exploration game where you control a miner navigating through a multi-level cave system displayed on an 8x8 LED matrix. Your objective is to collect all visible gold pieces while avoiding hidden bombs that become visible only when light is detected. The game features four progressively challenging levels with room-based navigation, a light-sensing mechanic for bomb detection, and explosive items to reveal hidden treasures within walls.

### Key Features

- **Progressive Difficulty**: Four handcrafted levels with increasing complexity
- **Light-Based Mechanics**: Photoresistor-controlled bomb visibility system
- **Explosive Puzzles**: Strategic explosive placement to destroy walls and reveal hidden gold
- **Scoring System**: Multiple bonus calculations with difficulty multipliers
- **EEPROM Persistence**: Saves top 3 highscores and player settings permanently
- **Sound Effects**: Dynamic buzzer melodies for game events
- **Comprehensive Settings**: Customize brightness, difficulty, sound, and starting level
- **Dual Display**: 8x8 LED matrix for gameplay + 16x2 LCD for information
- **Proximity Detection**: Audio feedback when near hidden treasures

---

## How to Play

### Main Menu Navigation

- **Joystick UP/DOWN**: Navigate menu options
- **Joystick Button**: Select option
- **Menu Options**:
  - Start Game
  - Settings
  - Highscores
  - About
  - How to Play

### In-Game Controls

| Input | Action |
|-------|--------|
| **Joystick** | Move the player (UP/DOWN/LEFT/RIGHT) |
| **Long Press Joystick Button** | Place explosive (available in Level 3-4) |
| **Exit Button (Pin 13)** | Return to main menu |

### Gameplay Mechanics

1. **Objective**: Collect all visible gold pieces and reach the exit door
2. **Bombs**: Hidden bombs become visible only when you shine light on them (cover the photoresistor with your hand)
3. **Explosives**: Long-press the joystick button to place an explosive, then move away. After 5 seconds, it explodes in a **cross pattern** (up, down, left, right + center), destroying walls and revealing hidden gold
4. **Proximity Detection**: When near hidden gold embedded in walls, you'll hear periodic beeping sounds guiding you
5. **Room Transitions**: The 8x8 viewport smoothly moves between four quadrants of the 16x16 world map as you explore
6. **Lives System**: Hit a bomb and lose a life. If an explosive hits you directly, you lose, otherwise(if you're in the near proximity, up, down, left, right, you lose a life). Game over when all lives are lost.

### Scoring System

Your final score is calculated based on multiple factors:

| Bonus Type | Points |
|------------|--------|
| **Gold Collection** | +10 points per gold piece |
| **Level Completion** | +50 points |
| **Lives Bonus** | +15 points per remaining life |
| **Explosives Bonus** (Level 3 only) | +10/20/30 points based on unused explosives |

**Difficulty Multipliers**:
- Easy: 0.8x
- Normal: 1.0x
- Hard: 1.2x

### Settings Menu

Customize your experience:

- **Starting Level**: Choose which level to begin from (1-4)
- **Difficulty**: 
  - Easy (4 lives, fewer bombs)
  - Normal (3 lives, standard)
  - Hard (2 lives, more bombs)
- **LCD Brightness**: Adjust LCD backlight (0-255, PWM controlled)
- **Matrix Brightness**: Adjust LED matrix intensity (0-15)
- **Sound**: Toggle sound effects ON/OFF
- **Reset**: Restore all settings to factory defaults

Press the **Exit Button** or **long-press the joystick** in settings to save and return to menu.

---

## Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Main microcontroller |
| 8x8 LED Matrix with MAX7219 | 1 | Game display |
| 16x2 LCD Display | 1 | Menu and game information |
| Joystick Module | 1 | Player input and menu navigation |
| Buzzer | 1 | Sound effects |
| Photoresistor | 1 | Light detection for bomb visibility |
| Push Button | 1 | Exit/Save button |
| Resistors (10k and 220) | 3 | Photoresistor voltage divider, button and for MAX7219 |
| Breadboard | 1 | Component connections |
| Jumper Wires | around 30 | Circuit connections |

---

## Hardware Setup

![Hardware Photo](hardware_matrix.png)  
*Physical hardware setup on breadboard*

### Pin Configuration

| Component | Pin | Type |
|-----------|-----|------|
| **Matrix (MAX7219)** |  |  |
| - DIN | 12 | Digital |
| - CLK | 11 | Digital |
| - LOAD (CS) | 10 | Digital |
| **LCD (16x2)** |  |  |
| - RS | 2 | Digital |
| - E | 8 | Digital |
| - D4 | 7 | Digital |
| - D5 | 6 | Digital |
| - D6 | 5 | Digital |
| - D7 | 4 | Digital |
| - LED (Backlight) | 9 | PWM |
| **Joystick** |  |  |
| - VRx | A0 | Analog |
| - VRy | A1 | Analog |
| - SW | A2 | Digital |
| **Buzzer** | 3 | Digital |
| **Photoresistor** | A3 | Analog |
| **Exit Button** | 13 | Digital |

### Wiring Notes

- **Photoresistor**: Connected in voltage divider configuration with 10kΩ pull-down resistor
- **Push Button**: Connected with 10k pull-down resistor
- **LCD Backlight**: Driven via PWM on pin 9 for brightness control
- **Joystick**: Center button connected to A2 with internal pull-up

---

## Video Demonstration

Watch the full gameplay and feature demonstration:

**[YouTube Demo Video](https://youtu.be/H0vetHM-Wng?si=7Vo4IzWAbMuWqmax)**

The video includes:
- A short demo of the game
- Menu navigation and settings configuration
- Explosive mechanics demonstration
- Light-based bomb detection showcase
- Highscore system and name entry

---

## Implementation Details

### Project Structure

```
MatrixProject/
├── proiect1.ino               # Arduino main entry point
├── Constants.h                # Pin definitions and game constants
│
├── GameEngine.cpp/h           # Main game loop and state management
├── Map.cpp/h                  # 16x16 world tile storage and level data
├── Player.cpp/h               # Player movement and collision detection
├── CameraController.cpp/h     # 8x8 viewport management
├── ActiveExplosive.cpp/h      # Explosive timing and destruction logic
│
├── MatrixDisplay.cpp/h        # LED matrix rendering with MAX7219
├── LCDDisplay.cpp/h           # LCD text display wrapper
├── Joystick.cpp/h             # Analog input handling and debouncing
├── Buzzer.cpp/h               # Sound pattern playback system
├── PhotoResistor.cpp/h        # Light sensor with smoothing
├── PushButton.cpp/h           # Button debouncing and long-press detection
│
├── HighscoreManager.cpp/h     # EEPROM-based top-3 score tracking
├── GameSettings.cpp/h         # Game configuration persistence
├── SystemSettings.cpp/h       # Hardware settings (brightness, sound)
│
└── README.md
```

### Architecture Overview

The codebase is organized into **modular components** for maintainability and clarity:

#### Core Game Files
- **GameEngine**: Main game loop, state machine, and coordination between all systems
- **Map**: Stores the 16x16 tile grid, handles level layouts, and tile manipulation
- **Player**: Movement logic, collision detection, gold collection, and bomb interaction

#### Display & Input
- **MatrixDisplay**: Renders the 8x8 viewport on LED matrix with camera support and light-based bomb visibility
- **LCDDisplay**: Manages 16x2 LCD text output with PWM brightness control
- **Joystick**: Reads analog input, detects directions, and handles button presses
- **CameraController**: Manages the 8x8 viewport window within the 16x16 world map

#### Game Systems
- **HighscoreManager**: EEPROM-based top-3 score tracking with 3-letter player names
- **GameSettings**: Stores game configuration (difficulty, starting level) in EEPROM
- **SystemSettings**: Manages hardware settings (brightness, sound) with EEPROM persistence
- **ActiveExplosive**: Handles explosive placement, countdown timing, and cross-pattern destruction

#### Hardware Abstraction
- **Buzzer**: Plays melody sequences for different game events (death, win, explosion, etc.)
- **PhotoResistor**: Reads light levels with moving average smoothing for stable bomb detection
- **PushButton**: Provides debounced button input with long-press detection
- **Constants.h**: Centralized definitions for pins, timing constants, and game balance parameters

The architecture **separates concerns** effectively: game logic, hardware interaction, and data persistence are handled by distinct modules, making the codebase easy to understand, test, and modify.

---

## Key Code Snippets

### 1. Proximity Detection for Hidden Gold

When the player is near hidden gold embedded in walls, the game triggers audio feedback to guide exploration.

**File**: `Player.cpp`

```cpp
bool Player::isNearHiddenTreasure() const {
    // Check all 8 adjacent tiles around the player
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;  // Skip player's own position
            
            int16_t checkX = x + dx;
            int16_t checkY = y + dy;
            
            // Validate bounds
            if (checkX >= 0 && checkX < MapConstants::WORLD_SIZE &&
                checkY >= 0 && checkY < MapConstants::WORLD_SIZE) {
                
                if (map->getTile(checkX, checkY) == TileType::HIDDEN_GOLD) {
                    return true;  // Found hidden treasure nearby
                }
            }
        }
    }
    return false;
}
```

**Key Design**: Uses 3x3 grid scanning around player position to detect hidden treasures in walls, enabling the proximity beeping mechanic.

---

### 2. Light-Based Bomb Visibility

Bombs are invisible by default and only appear when the photoresistor detects light (player covers sensor with hand).

**File**: `MatrixDisplay.cpp`

```cpp
void MatrixDisplay::draw(Map& map, Player& player, CameraController& camera) {
    bool hasLight = photoResistor.isBright();  // Check if light is detected
    
    for (uint8_t y = 0; y < MatrixConstants::SIZE; y++) {  // SIZE = 8
        for (uint8_t x = 0; x < MatrixConstants::SIZE; x++) {
            int16_t worldX = camera.getCameraX() + x;
            int16_t worldY = camera.getCameraY() + y;
            
            TileType tile = map.getTile(worldX, worldY);
            bool shouldLight = false;
            
            if (tile == TileType::BOMB) {
                shouldLight = hasLight;  // Bombs only visible with light
            } else if (tile == TileType::GOLD || tile == TileType::WALL) {
                shouldLight = true;  // Always visible
            }
            
            setLed(x, y, shouldLight);
        }
    }
}
```

**Key Design**: Integrates photoresistor readings directly into the render loop, creating a dynamic visibility system that encourages strategic light usage.

---

### 3. Explosive Cross-Pattern Destruction

Explosives destroy tiles in a 5-tile cross pattern (center + cardinal directions) and reveal hidden gold in adjacent walls.

**File**: `GameEngine.cpp`

```cpp
void GameEngine::handleExplosion() {
    int16_t ex = activeExplosive.getX();
    int16_t ey = activeExplosive.getY();
    
    // Define cross-shaped explosion pattern
    const int8_t explosionPattern[GameplayConstants::EXPLOSION_PATTERN_SIZE][2] = {
        {0, 0},    // Center
        {-1, 0},   // Left
        {1, 0},    // Right
        {0, -1},   // Up
        {0, 1}     // Down
    };
    
    // Destroy tiles in cross pattern
    for (int i = 0; i < GameplayConstants::EXPLOSION_PATTERN_SIZE; i++) {
        int16_t targetX = ex + explosionPattern[i][0];
        int16_t targetY = ey + explosionPattern[i][1];
        
        TileType tile = map.getTile(targetX, targetY);
        
        // Don't destroy special tiles
        if (tile != TileType::EXIT && tile != TileType::DOOR && 
            tile != TileType::HIDDEN_GOLD) {
            map.setTile(targetX, targetY, TileType::EMPTY);
        }
    }
    
    // Reveal hidden gold in adjacent wall tiles
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            int16_t nx = ex + dx;
            int16_t ny = ey + dy;
            
            if (map.getTile(nx, ny) == TileType::HIDDEN_GOLD) {
                map.setTile(nx, ny, TileType::GOLD);  // Make it collectible
            }
        }
    }
    
    activeExplosive.deactivate();
    buzzer.playExplosionSound();
}
```

**Key Design**: Separates destruction pattern from gold revelation logic, allowing walls with hidden gold to survive the blast but become accessible.

---

### 4. Camera Viewport Management

The camera system tracks the player and updates the 8x8 viewport window within the 16x16 world, implementing room-based transitions.

**File**: `CameraController.cpp`

```cpp
void CameraController::update() {
    uint8_t px = player->getX();
    uint8_t py = player->getY();
    
    // Snap camera to 8x8 grid boundaries based on player position
    cameraX = (px / MatrixConstants::SIZE) * MatrixConstants::SIZE;  // SIZE = 8
    cameraY = (py / MatrixConstants::SIZE) * MatrixConstants::SIZE;
    
    // Clamp camera to world bounds (16x16 world = 2x2 rooms of 8x8)
    if (cameraX + MatrixConstants::SIZE > MapConstants::WORLD_SIZE) {
        cameraX = MapConstants::WORLD_SIZE - MatrixConstants::SIZE;
    }
    if (cameraY + MatrixConstants::SIZE > MapConstants::WORLD_SIZE) {
        cameraY = MapConstants::WORLD_SIZE - MatrixConstants::SIZE;
    }
}
```

**Key Design**: Uses integer division to snap the camera to 8x8 room boundaries, creating discrete room transitions as the player crosses thresholds.

---

### 5. EEPROM Highscore Persistence

Saves the top 3 highscores permanently to Arduino's EEPROM memory with validation using a magic byte.

**File**: `HighscoreManager.cpp`

```cpp
void HighscoreManager::saveToEEPROM() {
    uint16_t addr = HighscoreConstants::EEPROM_START_ADDR;
    
    // Write validation marker
    EEPROM.update(addr++, HighscoreConstants::MAGIC_BYTE);  // 0xB7
    
    // Save all 3 highscore entries
    for (uint8_t i = 0; i < HighscoreConstants::MAX_HIGHSCORE_ENTRIES; i++) {
        // Save 3-character name
        EEPROM.update(addr++, entries[i].name[0]);
        EEPROM.update(addr++, entries[i].name[1]);
        EEPROM.update(addr++, entries[i].name[2]);
        
        // Save 16-bit score (big-endian)
        EEPROM.update(addr++, (entries[i].score >> 8) & 0xFF);  // High byte
        EEPROM.update(addr++, entries[i].score & 0xFF);         // Low byte
        
        // Save level reached
        EEPROM.update(addr++, entries[i].level);
    }
}

void HighscoreManager::loadFromEEPROM() {
    uint16_t addr = HighscoreConstants::EEPROM_START_ADDR;
    
    // Validate EEPROM data
    if (EEPROM.read(addr++) != HighscoreConstants::MAGIC_BYTE) {
        initializeDefaults();  // First boot or corrupted data
        return;
    }
    
    // Load all entries
    for (uint8_t i = 0; i < HighscoreConstants::MAX_HIGHSCORE_ENTRIES; i++) {
        entries[i].name[0] = EEPROM.read(addr++);
        entries[i].name[1] = EEPROM.read(addr++);
        entries[i].name[2] = EEPROM.read(addr++);
        entries[i].score = (EEPROM.read(addr++) << 8) | EEPROM.read(addr++);
        entries[i].level = EEPROM.read(addr++);
    }
}
```

**Key Design**: Uses `EEPROM.update()` instead of `write()` to reduce wear, and implements a magic byte validation system to detect first boot or data corruption.

---

### 6. Non-Blocking Explosive Timer

Handles explosive countdown without freezing gameplay using `millis()` timing.

**File**: `GameEngine.cpp`

```cpp
void GameEngine::update() {
    unsigned long currentTime = millis();
    
    // Check if explosive should detonate
    if (activeExplosive.isActive() && 
        explosivePlacedTime != 0 &&
        currentTime >= explosivePlacedTime &&
        (currentTime - explosivePlacedTime >= ExplosiveConstants::EXPLOSION_DELAY_MS)) {
        
        handleExplosion();  // Trigger explosion after 5 seconds
        explosivePlacedTime = 0;  // Reset timer
    }
    
    // Animate explosive with blink effect
    if (activeExplosive.isActive()) {
        uint8_t localX = activeExplosive.getX() - camera.getCameraX();
        uint8_t localY = activeExplosive.getY() - camera.getCameraY();
        
        // Blink based on frame counter (6 frames on, 6 frames off)
        bool blink = (matrixDisplay.getFrameCounter() % GameplayConstants::EXPLOSIVE_BLINK_CYCLE 
                      < GameplayConstants::EXPLOSIVE_BLINK_ON_FRAMES);
        
        matrixDisplay.setLed(localX, localY, blink);
    }
}
```

**Key Design**: Avoids `delay()` calls by tracking placement time with `millis()`, allowing the game loop to continue running while the explosive counts down.

---

### 7. Photoresistor Smoothing

Averages multiple readings to reduce sensor noise for stable bomb detection.

**File**: `PhotoResistor.cpp`

```cpp
void PhotoResistor::update() {
    rawValue = analogRead(PhotoResistorPins::SENSOR_PIN);  // A3
    
    // Moving average filter with circular buffer
    totalSum -= readings[readIndex];           // Remove oldest reading
    readings[readIndex] = rawValue;            // Store new reading
    totalSum += rawValue;                      // Add to sum
    
    // Move to next index (circular)
    readIndex = (readIndex + 1) % PhotoResistorConstants::SMOOTHING_SAMPLES;
    
    // Calculate running average
    smoothedValue = totalSum / PhotoResistorConstants::SMOOTHING_SAMPLES;
}

bool PhotoResistor::isBright() const {
    return smoothedValue > brightThreshold;  // Default threshold: 700
}
```

**Key Design**: Implements a circular buffer-based moving average filter (10 samples) to eliminate flickering caused by photoresistor noise, ensuring stable bomb visibility.

---

## Game Features

### Implemented Features

- **4 Progressive Levels** with unique handcrafted layouts
- **EEPROM Persistent Storage** for settings and highscores
- **Non-Blocking Timing** for smooth gameplay without `delay()`
- **Photoresistor-Based Bomb Visibility** - dynamic light detection
- **Explosive Placement System** with 5-second countdown and cross-pattern destruction
- **Real-Time Score Calculation** with multiple bonus systems
- **Comprehensive Menu System** with scrolling text for long options
- **PWM Brightness Control** for both LCD and matrix
- **Debounced Input Handling** with long-press detection
- **Room-Based Camera System** with smooth transitions
- **Proximity Audio Feedback** when near hidden treasures
- **Lives System** with difficulty-based starting lives
- **Victory/Game Over Screens** with statistics display
- **About Screen** with author information
- **How to Play Screen** with game instructions

### Gameplay Balance

| Difficulty | Starting Lives | Bomb Count | Score Multiplier |
|------------|---------------|------------|------------------|
| Easy | 4 | Reduced | 0.8x |
| Normal | 3 | Standard | 1.0x |
| Hard | 2 | Increased | 1.2x |

---

## Technical Highlights

### Memory Optimization
- Used `uint8_t` and `uint16_t` types to minimize RAM usage
- Stored constants in program memory with `constexpr`
- Efficient tile representation using enums
- Circular buffers for sensor smoothing

### Non-Blocking Architecture
- All timing based on `millis()` instead of `delay()`
- Smooth animations and responsive input
- Background explosive countdown
- Frame-based game loop

### Hardware Abstraction
- Clean separation between hardware and game logic
- Easy to modify pin configurations in `Constants.h`
- Modular component design allows easy testing
- PWM control for brightness on both displays

### Data Persistence
- Settings survive power cycles
- Top 3 highscores permanently saved
- EEPROM wear reduction using `update()` instead of `write()`
- Magic byte validation for data integrity

---

## Final Thoughts

Working on this project has been an incredibly rewarding experience. From the initial concept inspired by Red Dead Redemption 2 to the final implementation with all its features, every challenge taught me something new. I gained valuable knowledge in embedded systems programming, hardware integration, game design, and problem-solving under real-time constraints.

Debugging timing issues, optimizing memory usage, and implementing smooth gameplay mechanics pushed me to think creatively and understand the Arduino platform at a deeper level.

This project has strengthened my appreciation for the complexity behind even simple games and the importance of clean, modular code architecture, and its been a pleasure working on it
