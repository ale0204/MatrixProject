# The Miner - Arduino Matrix Game

## Backstory

This project draws inspiration from "The Wisdom of the Elders" side mission in Red Dead Redemption 2, my favorite game. In that mission, Arthur Morgan investigates a mysterious curse affecting the people of Butcher Creek. The investigation leads him to Elysian Pool and into an abandoned mine where toxic waste and arsenic have been poisoning the water supply.

What captivated me most was the mine exploration sequence where Arthur must use explosives to clear blocked paths while searching for valuables scattered throughout the cave. Although this Arduino game doesnt tie with RDR2's story, I transformed that atmospheric mine exploration concept into an 8x8 LED matrix puzzle game, capturing the essence of navigating dark tunnels, collecting gold, and using explosives strategically.

## Game Description

The Miner is a top-down exploration game where you control a miner navigating through a multi-level cave system displayed on an 8x8 LED matrix. Your objective is to collect all visible gold pieces while avoiding hidden bombs that become visible only when light is detected. The game features four progressively challenging levels with room-based navigation, a light-sensing mechanic for bomb detection, and explosive items to reveal hidden treasures within walls.

Key features include:
- Progressive difficulty across 4 levels
- Photoresistor-based bomb visibility mechanic
- Explosive system to reveal hidden gold in walls
- Lives and scoring system with difficulty multipliers
- EEPROM-based highscore tracking with player names
- Comprehensive settings menu for customization

## How to Play

### Main Menu Navigation
- Use the joystick UP/DOWN to navigate menu options
- Press the joystick button to select
- Options: Start Game, Settings, Highscores, About, How to Play

### In-Game Controls
- **Joystick**: Move the player (UP/DOWN/LEFT/RIGHT)
- **Long Press Joystick Button**: Place explosive (available in Level 2-3)
- **Exit Button (Pin 13)**: Return to main menu

### Gameplay Mechanics
1. **Objective**: Collect all visible gold and reach the exit door
2. **Bombs**: Hidden bombs become visible only when you use light (cover the photoresistor)
3. **Explosives**: Long-press to place, then move away. After 5 seconds, it explodes in a cross pattern, destroying walls and revealing hidden gold
4. **Proximity Detection**: When near hidden gold in walls, you'll hear periodic beeping sounds
5. **Room Transitions**: The 8x8 viewport moves between four quadrants of the 16x16 world map

### Scoring System
- Gold collection: +10 points
- Level completion bonus: +50 points
- Lives bonus: 15 points per remaining life
- Explosives bonus (Level 3): +10/20/30 points based on unused explosives
- Difficulty multipliers: Easy (0.8x), Normal (1.0x), Hard (1.2x)

### Settings Menu
- **Starting Level**: Choose which level to begin from (0-3)
- **Difficulty**: Easy (4 lives, fewer bombs) / Normal (3 lives) / Hard (2 lives, more bombs)
- **LCD Brightness**: Adjust LCD backlight (0-255)
- **Matrix Brightness**: Adjust LED matrix intensity (0-15)
- **Sound**: Toggle sound effects ON/OFF
- **Reset**: Restore all settings to defaults

Press the Exit Button or long-press the joystick in settings to save and return to menu.

## Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Main microcontroller |
| 8x8 LED Matrix (MAX7219) | 1 | Game display |
| 16x2 LCD Display | 1 | Menu and game information |
| Joystick Module | 1 | Player input and menu navigation |
| Buzzer | 1 | Sound effects |
| Photoresistor | 1 | Light detection for bomb visibility |
| Push Button | 1 | Exit/Save button |
| Resistors (10kΩ) | 2 | Photoresistor voltage divider and button pull-down |
| Breadboard | 1 | Component connections |
| Jumper Wires | ~30 | Circuit connections |

## Hardware Setup

![Hardware Photo](placeholder_image.jpg)
*Hardware photo will be added soon*

### Pin Configuration
- **Matrix**: DIN=12, CLK=11, LOAD=10
- **LCD**: RS=2, E=3, D4=4, D5=5, D6=6, D7=7, LED=9 (PWM)
- **Joystick**: VRx=A0, VRy=A1, SW=8
- **Buzzer**: Pin 13 (shared with built-in LED)
- **Photoresistor**: A3
- **Exit Button**: Pin 13

## Video Demonstration

Watch the full gameplay and menu demonstration here:
[https://youtu.be/H0vetHM-Wng?si=7Vo4IzWAbMuWqmax](https://youtu.be/H0vetHM-Wng?si=7Vo4IzWAbMuWqmax)

The video includes complete walkthrough of all game features, menu navigation, settings configuration, and gameplay across all four levels.

## Code Structure

The project is organized into modular components for maintainability and clarity:

### Core Game Files
- **GameEngine.cpp/h**: Main game loop, state management, and game logic coordination
- **Map.cpp/h**: 16x16 world tile data storage, level layouts, and tile manipulation
- **Player.cpp/h**: Player movement, collision detection, gold collection, and bomb interaction

### Display & Input
- **MatrixDisplay.cpp/h**: LED matrix rendering with camera viewport support and light-based bomb visibility
- **LCDDisplay.cpp/h**: LCD text display with brightness control
- **Joystick.cpp/h**: Analog input reading, direction detection, and button handling
- **CameraController.cpp/h**: 8x8 viewport management within the 16x16 world

### Game Systems
- **HighscoreManager.cpp/h**: EEPROM-based top-3 score tracking with player names
- **GameSettings.cpp/h**: Game configuration (difficulty, starting level) with EEPROM persistence
- **SystemSettings.cpp/h**: Hardware settings (brightness, sound) with EEPROM storage
- **ActiveExplosive.cpp/h**: Explosive placement, timing, and cross-pattern destruction logic

### Hardware Abstraction
- **Buzzer.cpp/h**: Sound pattern playback (melody sequences for different game events)
- **PhotoResistor.cpp/h**: Light level reading with smoothing for bomb visibility detection
- **PushButton.cpp/h**: Button debouncing and long-press detection
- **Constants.h**: Centralized pin definitions, timing constants, and game balance parameters

The architecture separates concerns effectively: game logic, hardware interaction, and data persistence are handled by distinct modules, making the codebase easy to understand and modify.

## Features Implemented
- 4 progressive levels with unique layouts
- EEPROM persistent storage for settings and highscores
- Non-blocking timing for smooth gameplay
- Photoresistor-based dynamic bomb visibility
- Explosive placement with 5-second countdown and cross-pattern destruction
- Real-time score calculation with multiple bonus systems
- Comprehensive menu system with scrolling text
- PWM brightness control for both LCD and matrix
- Debounced input handling with long-press detection
- Room-based camera system with transition sounds

---

**Author**: Alexandra Neamtu  
**Course**: Robotics, Year 3  
**Date**: December 2024
