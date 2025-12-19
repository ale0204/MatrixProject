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
    constexpr Pin RS = 2;  // Register Select (moved from 9 to free PWM pin)
    constexpr Pin EN = 8;
    constexpr Pin D4 = 7;
    constexpr Pin D5 = 6;
    constexpr Pin D6 = 5;
    constexpr Pin D7 = 4;
    constexpr Pin LED = 9; // LCD backlight LED (PWM for brightness control)
}

// Joystick
namespace JoystickPins
{
    constexpr Pin X_PIN  = A0;
    constexpr Pin Y_PIN  = A1;
    constexpr Pin SW_PIN = A2;
}

// Exit Button (Settings Menu)
namespace ExitButtonPins
{
    constexpr Pin EXIT_BUTTON_PIN = 13;  }

// PhotoResistor (Light Sensor)
namespace PhotoResistorPins
{
    constexpr Pin SENSOR_PIN = A3;  // Analog pin for photoresistor (switched back to A3)
}

namespace PhotoResistorConstants
{
    constexpr int DEFAULT_DARK_THRESHOLD = 300;    // Normal: values < 300 = dark
    constexpr int DEFAULT_BRIGHT_THRESHOLD = 700;  // Normal: values > 700 = bright
    constexpr int MIN_THRESHOLD = 0;
    constexpr int MAX_THRESHOLD = 1023;
    constexpr int ANALOG_MAX_VALUE = 1023;         // 10-bit ADC max value
    constexpr int BRIGHTNESS_PERCENTAGE_MAX = 100;  // 0-100% range
    constexpr int CALIBRATION_MARGIN = 50;          // Margin for calibration adjustment
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
    constexpr byte SMALL_BUFFER_SIZE = 16;  // Small buffer for short messages (without null terminator space)
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
    constexpr uint16_t MENU_NAVIGATION_COOLDOWN_MS = 300;  // Menu navigation cooldown
    constexpr uint16_t SETTINGS_NAVIGATION_COOLDOWN_MS = 200; // Settings navigation cooldown
    constexpr uint16_t HIGHSCORE_SCROLL_COOLDOWN_MS = 200;    // Highscore scroll cooldown
    constexpr uint16_t MESSAGE_DISPLAY_MS = 1000;      // Default message display duration
    constexpr uint16_t RESET_FEEDBACK_MS = 1500;       // Reset confirmation message duration
    constexpr uint16_t CONFIRM_TIMEOUT_MS = 3000;      // Confirmation timeout duration
    constexpr uint16_t LONG_PRESS_MS = 1000;           // Long press threshold
    constexpr uint16_t TEXT_SCROLL_INTERVAL_MS = 500;  // Text scrolling interval (About/HowToPlay)
    constexpr uint16_t PROXIMITY_BEEP_INTERVAL_MS = 500; // Treasure proximity beep interval
    constexpr uint16_t TREASURE_COLLECT_SOUND_MS = 500;  // Treasure collection sound duration
    constexpr uint16_t TEXT_SCROLL_START_DELAY_MS = 2000; // Initial delay before text starts scrolling
    constexpr uint16_t GAME_OVER_SOUND_MS = 2000;      // Game over sound duration
    constexpr uint16_t NAME_EDIT_TIMEOUT_MS = 1000;    // Timeout for name editor if no changes made
    constexpr uint16_t NAME_EDIT_INITIAL_DELAY_MS = 300; // Initial delay after entering name editor (prevent accidental input)
    constexpr uint16_t NAME_CHAR_CHANGE_COOLDOWN_MS = 150; // Cooldown between character changes (UP/DOWN)
    constexpr uint16_t NAME_CHAR_NAVIGATE_COOLDOWN_MS = 200; // Cooldown between character position navigation (LEFT/RIGHT)
    constexpr uint16_t BOMB_FEEDBACK_MS = 1000;        // Duration to display bomb hit feedback
    constexpr uint16_t GAME_OVER_FEEDBACK_MS = 3000;   // Duration to display game over message
    constexpr uint16_t GAME_WON_NAME_ENTRY_DELAY_MS = 2500; // Delay before entering name editor after winning
    constexpr uint16_t BOMB_PLACED_LCD_DISPLAY_MS = 3000; // Duration to display bomb placement message on LCD
}

namespace SoundFrequencies
{
    constexpr uint16_t NAVIGATION_BEEP_HZ = 200;       // Menu navigation beep
    constexpr uint16_t SETTINGS_CHANGE_HZ = 400;       // Settings value change beep
    constexpr uint16_t SETTINGS_SAVE_HZ = 1200;        // Settings saved sound
    constexpr uint16_t RESET_DONE_HZ = 1000;           // Reset confirmation sound
    constexpr uint16_t RESET_PROMPT_HZ = 800;          // Reset prompt sound
    constexpr uint16_t HIGHSCORE_SCROLL_HZ = 200;      // Highscore scroll beep
    constexpr uint16_t TREASURE_PROXIMITY_HZ = 1000;   // Treasure proximity beep frequency
    constexpr uint16_t EXPLOSIVE_PLACED_HZ = 800;      // Explosive placed confirmation beep
    constexpr uint16_t HIGHSCORE_SAVED_HZ = 1500;      // Highscore saved confirmation sound
    constexpr uint16_t NAME_CHAR_EDIT_HZ = 300;        // Name character edit beep
    constexpr uint16_t ERROR_BEEP_HZ = 200;            // Error/invalid action beep
}

namespace SoundDurationConstants
{
    constexpr uint16_t NAVIGATION_BEEP_MS = 50;        // Navigation beep duration
    constexpr uint16_t SETTINGS_CHANGE_MS = 50;        // Settings change beep duration
    constexpr uint16_t SETTINGS_SAVE_MS = 150;         // Settings save sound duration
    constexpr uint16_t RESET_DONE_MS = 200;            // Reset done sound duration
    constexpr uint16_t RESET_PROMPT_MS = 100;          // Reset prompt sound duration
    constexpr uint16_t HIGHSCORE_SCROLL_MS = 30;       // Highscore scroll sound duration
    constexpr uint16_t SHORT_BEEP_MS = 100;            // Short beep duration (general purpose)
    constexpr uint16_t HIGHSCORE_SAVED_MS = 200;       // Highscore saved sound duration
    constexpr uint16_t NAME_CHAR_EDIT_MS = 30;         // Name character edit beep duration
    constexpr uint16_t ERROR_BEEP_MS = 300;            // Error/invalid action beep duration
}

namespace SystemDefaultConstants
{
    constexpr uint8_t DEFAULT_LCD_BRIGHTNESS = 200;    // Default LCD brightness (0-255)
    constexpr uint8_t MAX_ATTEMPTS_BOMB_PLACEMENT = 100; // Max attempts to place bombs
    constexpr uint8_t DEFAULT_MATRIX_BRIGHTNESS = 8;   // Default matrix brightness (0-15)
    constexpr uint8_t MAX_LCD_BRIGHTNESS = 255;         // Maximum LCD brightness
    constexpr uint8_t PLAYER_NAME_LENGTH = 3;           // Player name max length
    constexpr uint8_t LCD_BUFFER_SIZE = 17;             // LCD buffer size (16 chars + null terminator)
}

namespace MenuIndexConstants
{
    constexpr uint8_t MENU_START_GAME = 0;
    constexpr uint8_t MENU_SETTINGS = 1;
    constexpr uint8_t MENU_HIGHSCORES = 2;
    constexpr uint8_t MENU_ABOUT = 3;
    constexpr uint8_t MENU_HOW_TO_PLAY = 4;
    constexpr uint8_t MENU_MAX_OPTION = 4;
    
    constexpr uint8_t SETTINGS_STARTING_LEVEL = 0;
    constexpr uint8_t SETTINGS_DIFFICULTY = 1;
    constexpr uint8_t SETTINGS_LCD_BRIGHTNESS = 2;
    constexpr uint8_t SETTINGS_MATRIX_BRIGHTNESS = 3;
    constexpr uint8_t SETTINGS_SOUND = 4;
    constexpr uint8_t SETTINGS_RESET = 5;
    constexpr uint8_t SETTINGS_MAX_OPTION = 5;
}

namespace HighscoreConstants
{
    constexpr uint8_t MAX_HIGHSCORE_ENTRIES = 3;        // Top 3 scores
    constexpr uint8_t HIGHSCORE_NAME_LENGTH = 3;        // 3 characters for name
    constexpr uint8_t HIGHSCORE_FIRST_PLACE = 0;
    constexpr uint8_t HIGHSCORE_SECOND_PLACE = 1;
    constexpr uint8_t HIGHSCORE_THIRD_PLACE = 2;
    constexpr uint8_t HIGHSCORE_NOT_QUALIFIED = 255;    // Returned when score doesn't qualify
    constexpr char DEFAULT_NAME_CHAR = 'A';              // Default character for names
    constexpr uint8_t EEPROM_MAGIC_OFFSET = 1;          // Offset after magic byte
    constexpr uint8_t SCORE_LOW_BYTE_SHIFT = 0;
    constexpr uint8_t SCORE_HIGH_BYTE_SHIFT = 8;
    constexpr uint8_t BYTE_MASK = 0xFF;
}

namespace ExplosiveConstants
{
    constexpr unsigned long EXPLOSION_DELAY_MS = 5000;   // 5 seconds until explosion
}

namespace GameplayConstants
{
    constexpr uint8_t TREASURE_DETECTION_RADIUS = 2;     // 5x5 grid (±2 in all directions)
    constexpr uint16_t LEVEL_COMPLETE_BONUS = 50;        // Bonus score for completing level
    constexpr uint8_t EXPLOSIVE_BLINK_CYCLE = 12;        // Total frames for explosive blink
    constexpr uint8_t EXPLOSIVE_BLINK_ON_FRAMES = 6;     // Frames LED is on
    constexpr uint8_t EXPLOSION_PATTERN_SIZE = 5;        // Cross pattern: center + 4 directions
    constexpr uint16_t EXPLOSION_SOUND_DURATION_MS = 500; // Explosion sound duration
    constexpr uint8_t GOLD_COLLECT_SCORE = 10;           // Score awarded for collecting gold
    constexpr uint8_t LIFE_BONUS_MULTIPLIER = 15;        // Score bonus per remaining life
    constexpr uint8_t EXPLOSIVES_BONUS_THREE = 30;       // Bonus for finishing with 3 explosives
    constexpr uint8_t EXPLOSIVES_BONUS_TWO = 20;         // Bonus for finishing with 2 explosives
    constexpr uint8_t EXPLOSIVES_BONUS_ONE = 10;         // Bonus for finishing with 1 explosive
}

namespace MapBoundaryConstants
{
    constexpr uint8_t MAP_BOUNDARY_MIN = 0;
    constexpr uint8_t MAP_BOUNDARY_MAX = 15;
    constexpr uint8_t ROOM_SEPARATOR_LOWER = 7;
    constexpr uint8_t ROOM_SEPARATOR_UPPER = 8;
}

namespace DifficultyConstants
{
    constexpr uint8_t EASY_LIVES = 4;
    constexpr uint8_t NORMAL_LIVES = 3;
    constexpr uint8_t HARD_LIVES = 2;
    constexpr uint8_t LEVEL_0_BASE_BOMBS = 0;
    constexpr uint8_t LEVEL_1_BASE_BOMBS = 4;
    constexpr uint8_t LEVEL_2_BASE_BOMBS = 6;
    constexpr uint8_t LEVEL_3_BASE_BOMBS = 8;
    constexpr uint8_t EASY_BOMB_REDUCTION = 1;
    constexpr uint8_t HARD_BOMB_INCREASE = 2;
    constexpr uint8_t MIN_BOMBS_REDUCTION = 2;
    constexpr float SCORE_MULT_LEVEL_0 = 1.0f;
    constexpr float SCORE_MULT_LEVEL_1 = 1.5f;
    constexpr float SCORE_MULT_LEVEL_2 = 2.0f;
    constexpr float SCORE_MULT_LEVEL_3 = 3.0f;
    constexpr float SCORE_MULT_EASY = 0.8f;
    constexpr float SCORE_MULT_NORMAL = 1.0f;
    constexpr float SCORE_MULT_HARD = 1.5f;
}

namespace EEPROMOffsets
{
    constexpr uint8_t SYSTEM_SETTINGS_LCD_BRIGHTNESS_OFFSET = 4;
    constexpr uint8_t SYSTEM_SETTINGS_MATRIX_BRIGHTNESS_OFFSET = 5;
    constexpr uint8_t SYSTEM_SETTINGS_SOUND_ENABLED_OFFSET = 6;
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
    
    constexpr byte LEVEL_0 = 0;  
    constexpr byte LEVEL_1 = 1;  
    constexpr byte LEVEL_2 = 2;  
    constexpr byte LEVEL_3 = 3;  
    constexpr byte MIN_LEVEL = 0;
    constexpr byte MAX_LEVEL = 3;  
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
    constexpr uint8_t GOLD_BLINK_CYCLE = 22;         // Total frames for blink cycle (slower)
    constexpr uint8_t GOLD_BLINK_ON_FRAMES = 11;      // Frames LED is on
    constexpr uint8_t BOMB_BLINK_CYCLE = 8;          // Total frames for bomb blink cycle
    constexpr uint8_t BOMB_BLINK_ON_FRAMES = 4;      // Frames LED is on (4 ON, 4 OFF)
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
    EMPTY = 0, 
    WALL  = 1,  
    GOLD  = 2,  
    DOOR  = 3, 
    EXIT  = 4, 
    BOMB  = 5, 
    HIDDEN_GOLD = 6  
};

#endif // CONSTANTS_H
