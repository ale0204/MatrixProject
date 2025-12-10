# Matrix Project - Checkpoint 2

### Task Description
Implementation of "The Miner" - a complete 16x16 matrix-based adventure game for the "Introduction to Robotics" course. This checkpoint delivers a fully playable game with 3 levels, menu system, sound effects, gold collection mechanics, and multi-room navigation. The game demonstrates advanced embedded systems concepts including camera viewport management, state machines, non-blocking sound patterns, and modular clean architecture.

### Game Concept: "The Miner"

**Story:** The player is a miner exploring underground mines searching for gold. The mine is divided into multiple chambers (rooms) connected by passages, with walls blocking certain paths and gold scattered throughout.

**Core Mechanics:**
- Navigate through a 16x16 world displayed as an 8x8 viewport (camera system)
- Collect gold pieces (slow-blinking LEDs) to increase score
- Navigate between rooms through passages (unlit LEDs in walls)
- Complete levels by reaching the EXIT tile
- 3 progressively complex levels with different room layouts

**Visual Elements:**
- **Walls:** Solid LEDs (always on) - impassable obstacles
- **Gold:** Slow-blinking LEDs - collectible items
- **Doors:** Unlit LEDs in walls - passages between rooms
- **Exit:** Unlit LED - level completion point
- **Player:** Solid LED (always on) - your position

---

### Level Design

#### Level 1: Two Rooms (Tutorial)
**Layout:** Northwest (NW) and Northeast (NE) rooms accessible

**Room 1 (NW - Top Left):**
- Starting position at (1,1)
- Contains gold pieces scattered among walls
- Internal walls create maze-like paths
- Exit passage on the right wall (X=7) leading to Room 2

**Room 2 (NE - Top Right):**
- More gold to collect
- Different wall configuration
- EXIT tile located at (15,2) on the right wall
- Reaching EXIT completes Level 1

**Objective:** Learn basic movement, gold collection, and room transitions.

---

#### Level 2: Three Rooms (Intermediate)
**Layout:** Northwest, Northeast, and Southwest rooms accessible

**Room 1 (NW):** 
- Identical layout to Level 1
- Now has TWO passages: right (to NE) and bottom (to SW)

**Room 2 (NE):**
- Similar to Level 1 but with more gold
- Passage to return to NW room

**Room 3 (SW - New!):**
- Accessed via bottom passage from NW
- Contains gold among walls
- EXIT tile at (3,15) on bottom-left
- Southeast room is completely blocked (all walls)

**Objective:** Navigate between three rooms efficiently to collect all gold.

---

#### Level 3: Four Rooms (Complete Mine)
**Layout:** All four rooms accessible (NW, NE, SW, SE)

**Room 1 (NW):**
- Same layout as previous levels
- Passages right and down

**Room 2 (NE):**
- Passage down to SE room added
- Gold scattered throughout

**Room 3 (SW):**
- Gold placement remains
- Player can now access SE room

**Room 4 (SE - New!):**
- Fully accessible final room
- Contains gold
- EXIT tile at (15,13) on right wall
- Completing this level wins the game

**Objective:** Explore all four quadrants of the mine to find all gold and reach the exit.

---

### Game Flow

**1. Startup:**
- LCD displays "THE MINER" title
- Shows "Loading..." message
- Plays startup tone
- Transitions to main menu

**2. Main Menu:**
- LCD shows "THE MINER" and "Press to Play"
- Matrix display is cleared
- Press joystick button to start

**3. Gameplay:**
- **Movement:** Use joystick to move player (up/down/left/right)
- **Gold Collection:** Walk over gold to collect (plays sound, updates LCD)
- **Room Transitions:** Walk through doors to change rooms (plays transition sound)
- **Level Completion:** Reach EXIT to advance to next level (plays victory fanfare)

**4. Level Progression:**
- Level 1 → Level 2 → Level 3 → Victory
- Each level displays "LEVEL COMPLETE!" message
- Automatic progression to next level
- After Level 3: "YOU WIN! All levels done"

**5. Victory:**
- Game won message displayed
- Epic victory melody plays
- Returns to main menu

---

### Technical Implementation

#### Camera Viewport System
The game uses a **camera viewport** to display 8x8 sections of the 16x16 world:

```
16x16 World divided into 4 rooms:
┌────────┬────────┐
│ NW     │ NE     │  Each room = 8x8 tiles
│ (0,0)  │ (8,0)  │  Camera shows ONE room at a time
├────────┼────────┤
│ SW     │ SE     │  Camera switches when player moves
│ (0,8)  │ (8,8)  │  between rooms
└────────┴────────┘
```

The `CameraController` automatically tracks the player and switches rooms:
- Player at (3,5) → Camera at (0,0) shows NW room
- Player at (10,3) → Camera at (8,0) shows NE room
- Player at (5,12) → Camera at (0,8) shows SW room
- Player at (14,11) → Camera at (8,8) shows SE room

---

### Sound System

The game features **non-blocking audio patterns** using the buzzer:

**Sound Effects:**
- **Menu Select:** Double beep (C5 → E5) when starting game
- **Gold Collection:** Happy chirp (C5 → E5) when collecting gold
- **Room Transition:** Brief ascending tone (G4 → C5) when entering new room
- **Level Complete:** Victory fanfare (C5 → E5 → G5) when reaching exit
- **Game Won:** Epic melody (C5 → E5 → G5 → C6) after completing all levels
- **Level Load:** Confirmation beep (1000Hz) when loading new level

All sounds use the `BuzzerPattern` system with proper note durations and frequencies defined in `Constants.h`.

---

### Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Microcontroller board |
| 8x8 LED Matrix (MAX7219) | 1 | Game viewport display |
| 16x2 LCD Display | 1 | Menu, score, and level info |
| Joystick Module (X, Y, SW) | 1 | Player movement and menu selection |
| Buzzer (Passive) | 1 | Sound effects and music |
| Resistors | As needed | Pull-up/down resistors |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | Multiple | Connections |

---

### Circuit Design

**Pin Configuration:**

*LED Matrix (MAX7219):*
- DIN → Pin 12
- CLK → Pin 11
- LOAD (CS) → Pin 10
- VCC → 5V
- GND → GND

*LCD Display (4-bit mode):*
- RS → Pin 9
- EN → Pin 8
- D4 → Pin 7
- D5 → Pin 6
- D6 → Pin 5
- D7 → Pin 4
- VCC → 5V
- GND → GND
- V0 → Potentiometer (contrast)

*Joystick:*
- VRx (X-Axis) → Pin A0
- VRy (Y-Axis) → Pin A1
- SW (Button) → Pin A2
- VCC → 5V
- GND → GND

*Buzzer:*
- Signal → Pin 3
- GND → GND

#### Physical Implementation

**Hardware Setup:**

![Hardware Setup Photo - To be added]()

*Figure: Physical circuit with Arduino Uno, MAX7219 LED matrix, LCD display, joystick, and buzzer.*

---

### Project Structure

The codebase follows **clean architecture** with modular design:

```
Matrix-Checkpoint2/
├── src/
│   ├── proiect1.ino              # Main Arduino sketch
│   ├── Constants.h               # All constants (pins, timing, game settings)
│   ├── GameEngine.h/.cpp         # Game state machine and main logic
│   ├── Map.h/.cpp                # 16x16 world map with 3 level layouts
│   ├── Player.h/.cpp             # Player movement and gold collection
│   ├── CameraController.h/.cpp   # Viewport management (8x8 window)
│   ├── MatrixDisplay.h/.cpp      # LED matrix rendering
│   ├── LCDDisplay.h/.cpp         # LCD display wrapper
│   ├── Joystick.h/.cpp           # Joystick input handling
│   ├── PushButton.h/.cpp         # Button debouncing
│   └── Buzzer.h/.cpp             # Sound pattern system
└── README.md                     # This file
```

---

### Key Classes

**GameEngine:** Main game controller
- Manages game states (MENU, PLAYING)
- Handles input and updates all systems
- Coordinates level loading and progression
- Checks win conditions

**Map:** World data storage
- Stores 16x16 tile grids for 3 levels
- Provides collision detection
- Manages gold placement
- Loads levels from PROGMEM (Flash memory)

**Player:** Character controller
- Tracks position on 16x16 map
- Handles movement with collision detection
- Automatic gold collection when stepping on gold tiles
- Exit detection

**CameraController:** Viewport management
- Tracks which 8x8 room to display
- Converts global coordinates (0-15) to local (0-7)
- Automatically switches rooms when player moves

**MatrixDisplay:** Visual rendering
- Draws 8x8 viewport to LED matrix
- Different rendering for each tile type
- Gold blinking animation
- Player always visible

**Buzzer:** Audio system
- Non-blocking sound patterns
- Musical note support (C4-C6)
- Pattern-based melodies
- Multiple simultaneous sound effects

---

### Game Features

✅ **Complete Menu System:** Main menu with joystick button to start
✅ **3 Progressive Levels:** Increasing complexity and room count
✅ **16x16 World Map:** 4 rooms with camera viewport
✅ **Gold Collection:** Scattered collectibles with sound feedback
✅ **Multi-Room Navigation:** Seamless room transitions
✅ **Sound Effects:** Menu, collection, transition, victory sounds
✅ **LCD Information:** Current level and gold count display
✅ **Clean Code:** No magic numbers, all constants defined
✅ **Modular Architecture:** Each system in separate class
✅ **Non-Blocking Code:** No delay() calls in main loop

---

### Code Quality

**Clean Code Practices:**
- All magic numbers replaced with named constants
- Modular class-based architecture
- Clear separation of concerns
- Hardware abstraction layers
- Comprehensive constant namespaces
- No blocking delays

**Constants Organization:**
```cpp
namespace MatrixPins { DIN, CLK, LOAD }
namespace LCDPins { RS, EN, D4-D7 }
namespace JoystickPins { X_PIN, Y_PIN, SW_PIN }
namespace BuzzerPins { BUZZER_PIN }
namespace SoundDurations { MENU_SELECT_MS, COLLECT_GOLD_MS, etc. }
namespace MessageDurations { LEVEL_COMPLETE_MS, GAME_WON_MS, etc. }
namespace ToneFrequencies { LEVEL_LOAD_HZ, STARTUP_HZ }
namespace DisplayConstants { LCD_BUFFER_SIZE, DEFAULT_MATRIX_BRIGHTNESS }
namespace SpawnConstants { DEFAULT_SPAWN_X, DEFAULT_SPAWN_Y }
namespace MapConstants { WORLD_SIZE, ROOM_SIZE, LEVEL_1/2/3 }
```

---

### Future Enhancements (Checkpoint 3)

Planned features for the final checkpoint:

**Bombs and Light Sensor:**
- Fast-blinking bomb tiles in certain rooms
- Light sensor to reveal bomb locations
- Player loses life when hitting bombs
- 3 lives system displayed on LCD

**Explosive Inventory:**
- Player can carry and place explosives
- Explosives destroy walls to access hidden gold
- Timed explosion mechanic (5 seconds)
- Safe distance requirement

**Advanced Features:**
- Settings menu (brightness, sound volume)
- High score system with EEPROM persistence
- Player name entry
- "How to Play" instructions

---

### Media

**Demo Video:**  
[Watch on YouTube]()

**Source Code:**  
[View on GitHub](https://github.com/ale0204/MatrixProject/tree/main/Matrix-Checkpoint2/src)

---

### Key Learnings

This checkpoint demonstrates advanced embedded systems concepts:

**State Machine Architecture:** Menu and gameplay states with clean transitions  
**Camera Viewport System:** Rendering 8x8 windows of larger 16x16 world  
**Coordinate Transformations:** Global to local coordinate mapping  
**Non-Blocking Audio:** Pattern-based sound system without delays  
**Game Loop Design:** Update-render cycle with fixed timesteps  
**Modular Architecture:** Clean separation between game logic and hardware  
**Memory Management:** Using PROGMEM for level data to save RAM  
**Input Handling:** Debounced buttons and analog joystick with deadzone  

---

**Author:** Alexandra  
**Course:** Introduction to Robotics, University of Bucharest  
**Date:** December 2025  
**Checkpoint:** 2 of 3
