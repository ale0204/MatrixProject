#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

// Type definitions
typedef unsigned char Pin;

// LED Matrix (MAX7219)
namespace MatrixPins
{
    constexpr Pin DIN  = 12;  // MAX7219 pin 1
    constexpr Pin CLK  = 11;  // MAX7219 pin 13
    constexpr Pin LOAD = 10;  // MAX7219 pin 12 (CS)
}

// LCD 16x2
namespace LCDPins
{
    constexpr Pin RS = 9;
    constexpr Pin EN = 8;
    constexpr Pin D4 = 7;
    constexpr Pin D5 = 6;
    constexpr Pin D6 = 5;
    constexpr Pin D7 = 4;
}

// Joystick
namespace JoystickPins
{
    constexpr Pin X_PIN  = A0;
    constexpr Pin Y_PIN  = A1;
    constexpr Pin SW_PIN = A2;
}

// =============================================================================
// DISPLAY CONSTANTS
// =============================================================================

namespace MatrixConstants
{
    constexpr byte SIZE = 8;           // 8x8 matrix
    constexpr byte BRIGHTNESS = 2;     // Default brightness (0-15)
    constexpr byte MAX_BRIGHTNESS = 15; // Maximum brightness value
    constexpr byte DEVICE_COUNT = 1;   // Number of MAX7219 devices
}

namespace LCDConstants
{
    constexpr byte COLS = 16;
    constexpr byte ROWS = 2;
}

// =============================================================================
// TIMING CONSTANTS
// =============================================================================

namespace TimingConstants
{
    constexpr uint16_t INTRO_DURATION_MS = 2500;       // Intro screen duration
    constexpr uint16_t UPDATE_INTERVAL_MS = 50;        // Main loop update interval
    constexpr uint16_t MENU_SCROLL_DELAY_MS = 200;     // Delay between menu scrolls
    constexpr uint16_t DEBOUNCE_MS = 50;               // Button debounce time
    constexpr uint16_t BLINK_INTERVAL_MS = 300;        // LED blink interval
}

// =============================================================================
// SERIAL CONSTANTS
// =============================================================================

namespace SerialConstants
{
    constexpr unsigned long BAUD_RATE = 115200;
}

// =============================================================================
// JOYSTICK CONSTANTS
// =============================================================================

namespace JoystickConstants
{
    constexpr byte DEADZONE = 30;           // Ignore small movements around center
    constexpr byte CENTER_POSITION = 128;   // Center value (1023/2 mapped to 0-255)
    constexpr uint16_t MOVEMENT_COOLDOWN_MS = 200;  // Prevent too-fast navigation
    
    // Analog read range
    constexpr uint16_t ANALOG_MIN = 0;
    constexpr uint16_t ANALOG_MAX = 1023;
    constexpr byte MAPPED_MIN = 0;
    constexpr byte MAPPED_MAX = 255;
}

// =============================================================================
// MENU CONSTANTS
// =============================================================================

namespace MenuConstants
{
    constexpr byte ITEM_COUNT = 1;  // For now, only "Start Game"
    // Will expand later: Start, Highscore, Settings, About, How to Play
}

// =============================================================================
// GAME DEMO CONSTANTS
// =============================================================================

namespace GameDemoConstants
{
    constexpr uint16_t CURSOR_BLINK_MS = 150;   // Cursor blink rate
    constexpr uint16_t SLOW_BLINK_MS = 500;     // Slow blink rate
    constexpr uint16_t FAST_BLINK_MS = 150;     // Fast blink rate
    constexpr uint16_t MOVE_DELAY_MS = 150;     // Movement delay
    constexpr uint16_t EXIT_HOLD_MS = 1500;     // Hold button to exit
    
    // LCD layout positions
    constexpr byte POSITION_COL = 11;           // Column for (x,y) display
    constexpr byte STATE_VALUE_COL = 7;         // Column for state value
}

// =============================================================================
// BUZZER CONFIGURATION
// =============================================================================

namespace BuzzerPins
{
    constexpr Pin BUZZER_PIN = 3;  // PWM-capable pin for tone generation
}

// =============================================================================
// MAP CONSTANTS (The Miner Game)
// =============================================================================

namespace MapConstants
{
    constexpr byte WORLD_SIZE = 16;      // Total map size (16x16)
    constexpr byte ROOM_SIZE = 8;        // Each room is 8x8
    constexpr byte ROOM_COUNT = 4;       // 2x2 grid of rooms (NW, NE, SW, SE)
    
    // Camera positions (possible offsets)
    constexpr byte CAMERA_OFFSET_0 = 0;  // Top-left or left
    constexpr byte CAMERA_OFFSET_1 = 8;  // Bottom-right or right
    
    // Level identifiers (0-indexed!)
    constexpr byte LEVEL_1 = 0;  // 2 rooms accessible (NW, NE)
    constexpr byte LEVEL_2 = 1;  // 3 rooms accessible (NW, NE, SW)
    constexpr byte LEVEL_3 = 2;  // 4 rooms accessible (all)
    constexpr byte MIN_LEVEL = 0;
    constexpr byte MAX_LEVEL = 2;
}

// =============================================================================
// SOUND DURATION CONSTANTS
// =============================================================================

namespace SoundDurations
{
    constexpr uint16_t MENU_SELECT_MS = 500;
    constexpr uint16_t COLLECT_GOLD_MS = 200;
    constexpr uint16_t ROOM_TRANSITION_MS = 150;
    constexpr uint16_t LEVEL_COMPLETE_MS = 650;
    constexpr uint16_t GAME_WON_MS = 1200;
    constexpr uint16_t LEVEL_LOAD_TONE_MS = 100;
    constexpr uint16_t STARTUP_TONE_MS = 100;
}

namespace MessageDurations
{
    constexpr uint16_t LEVEL_COMPLETE_MS = 2000;
    constexpr uint16_t GAME_WON_MS = 3000;
    constexpr uint16_t STARTUP_MS = 1000;
}

namespace ToneFrequencies
{
    constexpr uint16_t LEVEL_LOAD_HZ = 1000;
    constexpr uint16_t STARTUP_HZ = 1000;
}

// =============================================================================
// DISPLAY CONSTANTS (Extended)
// =============================================================================

namespace DisplayConstants
{
    constexpr uint8_t LCD_BUFFER_SIZE = 17;          // 16 chars + null terminator
    constexpr uint8_t DEFAULT_MATRIX_BRIGHTNESS = 8; // Medium brightness
    constexpr uint8_t GOLD_BLINK_CYCLE = 10;         // Total frames for blink cycle
    constexpr uint8_t GOLD_BLINK_ON_FRAMES = 5;      // Frames LED is on
}

// =============================================================================
// SPAWN CONSTANTS
// =============================================================================

namespace SpawnConstants
{
    constexpr uint8_t DEFAULT_SPAWN_X = 1;
    constexpr uint8_t DEFAULT_SPAWN_Y = 1;
}

// =============================================================================
// TILE TYPES (Map Elements)
// =============================================================================

enum class TileType : uint8_t
{
    EMPTY = 0,  // Walkable, nothing there
    WALL  = 1,  // Solid, blocks movement
    GOLD  = 2,  // Collectible (will blink slow)
    DOOR  = 3,  // Passage between rooms
    EXIT  = 4   // Level finish line
    // BOMB = 5  // Future: explosive (requires light sensor)
};

#endif // CONSTANTS_H
