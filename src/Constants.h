#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

typedef unsigned char Pin;

namespace MatrixPins
{
    constexpr Pin DIN  = 12;
    constexpr Pin CLK  = 11;
    constexpr Pin LOAD = 10;
}

namespace LCDPins
{
    constexpr Pin RS = 2;
    constexpr Pin EN = 8;
    constexpr Pin D4 = 7;
    constexpr Pin D5 = 6;
    constexpr Pin D6 = 5;
    constexpr Pin D7 = 4;
    constexpr Pin LED = 9;
}

namespace JoystickPins
{
    constexpr Pin X_PIN  = A0;
    constexpr Pin Y_PIN  = A1;
    constexpr Pin SW_PIN = A2;
}

namespace ExitButtonPins
{
    constexpr Pin EXIT_BUTTON_PIN = 13;
}

namespace PhotoResistorPins
{
    constexpr Pin SENSOR_PIN = A3;
}

namespace PhotoResistorConstants
{
    constexpr int DEFAULT_DARK_THRESHOLD = 300;
    constexpr int DEFAULT_BRIGHT_THRESHOLD = 700;
    constexpr int MIN_THRESHOLD = 0;
    constexpr int MAX_THRESHOLD = 1023;
    constexpr int ANALOG_MAX_VALUE = 1023;
    constexpr int BRIGHTNESS_PERCENTAGE_MAX = 100;
    constexpr int CALIBRATION_MARGIN = 50;
}

namespace MatrixConstants
{
    constexpr byte SIZE = 8;
    constexpr byte BRIGHTNESS = 2;
    constexpr byte MAX_BRIGHTNESS = 15;
    constexpr byte DEVICE_COUNT = 1;
}

namespace LCDConstants
{
    constexpr byte COLS = 16;
    constexpr byte ROWS = 2;
    constexpr byte SMALL_BUFFER_SIZE = 16;
}

namespace TimingConstants
{
    constexpr uint16_t INTRO_DURATION_MS = 2500;
    constexpr uint16_t UPDATE_INTERVAL_MS = 50;
    constexpr uint16_t MENU_SCROLL_DELAY_MS = 200;
    constexpr uint16_t DEBOUNCE_MS = 50;
    constexpr uint16_t BLINK_INTERVAL_MS = 300;
    constexpr uint16_t MENU_NAVIGATION_COOLDOWN_MS = 300;
    constexpr uint16_t SETTINGS_NAVIGATION_COOLDOWN_MS = 200;
    constexpr uint16_t HIGHSCORE_SCROLL_COOLDOWN_MS = 200;
    constexpr uint16_t MESSAGE_DISPLAY_MS = 1000;
    constexpr uint16_t RESET_FEEDBACK_MS = 1500;
    constexpr uint16_t CONFIRM_TIMEOUT_MS = 3000;
    constexpr uint16_t LONG_PRESS_MS = 1000;
    constexpr uint16_t TEXT_SCROLL_INTERVAL_MS = 500;
    constexpr uint16_t PROXIMITY_BEEP_INTERVAL_MS = 500;
    constexpr uint16_t TREASURE_COLLECT_SOUND_MS = 500;
    constexpr uint16_t TEXT_SCROLL_START_DELAY_MS = 2000;
    constexpr uint16_t GAME_OVER_SOUND_MS = 2000;
    constexpr uint16_t NAME_EDIT_TIMEOUT_MS = 1000;
    constexpr uint16_t NAME_EDIT_INITIAL_DELAY_MS = 300;
    constexpr uint16_t NAME_CHAR_CHANGE_COOLDOWN_MS = 150;
    constexpr uint16_t NAME_CHAR_NAVIGATE_COOLDOWN_MS = 200;
    constexpr uint16_t BOMB_FEEDBACK_MS = 1000;
    constexpr uint16_t GAME_OVER_FEEDBACK_MS = 3000;
    constexpr uint16_t GAME_WON_NAME_ENTRY_DELAY_MS = 2500;
    constexpr uint16_t BOMB_PLACED_LCD_DISPLAY_MS = 3000;
}

namespace SoundFrequencies
{
    constexpr uint16_t NAVIGATION_BEEP_HZ = 200;
    constexpr uint16_t SETTINGS_CHANGE_HZ = 400;
    constexpr uint16_t SETTINGS_SAVE_HZ = 1200;
    constexpr uint16_t RESET_DONE_HZ = 1000;
    constexpr uint16_t RESET_PROMPT_HZ = 800;
    constexpr uint16_t HIGHSCORE_SCROLL_HZ = 200;
    constexpr uint16_t TREASURE_PROXIMITY_HZ = 1000;
    constexpr uint16_t EXPLOSIVE_PLACED_HZ = 800;
    constexpr uint16_t HIGHSCORE_SAVED_HZ = 1500;
    constexpr uint16_t NAME_CHAR_EDIT_HZ = 300;
    constexpr uint16_t ERROR_BEEP_HZ = 200;
}

namespace SoundDurationConstants
{
    constexpr uint16_t NAVIGATION_BEEP_MS = 50;
    constexpr uint16_t SETTINGS_CHANGE_MS = 50;
    constexpr uint16_t SETTINGS_SAVE_MS = 150;
    constexpr uint16_t RESET_DONE_MS = 200;
    constexpr uint16_t RESET_PROMPT_MS = 100;
    constexpr uint16_t HIGHSCORE_SCROLL_MS = 30;
    constexpr uint16_t SHORT_BEEP_MS = 100;
    constexpr uint16_t HIGHSCORE_SAVED_MS = 200;
    constexpr uint16_t NAME_CHAR_EDIT_MS = 30;
    constexpr uint16_t ERROR_BEEP_MS = 300;
}

namespace SystemDefaultConstants
{
    constexpr uint8_t DEFAULT_LCD_BRIGHTNESS = 200;
    constexpr uint8_t MAX_ATTEMPTS_BOMB_PLACEMENT = 100;
    constexpr uint8_t DEFAULT_MATRIX_BRIGHTNESS = 8;
    constexpr uint8_t MAX_LCD_BRIGHTNESS = 255;
    constexpr uint8_t PLAYER_NAME_LENGTH = 3;
    constexpr uint8_t LCD_BUFFER_SIZE = 17;
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
    constexpr uint8_t MAX_HIGHSCORE_ENTRIES = 3;
    constexpr uint8_t HIGHSCORE_NAME_LENGTH = 3;
    constexpr uint8_t HIGHSCORE_FIRST_PLACE = 0;
    constexpr uint8_t HIGHSCORE_SECOND_PLACE = 1;
    constexpr uint8_t HIGHSCORE_THIRD_PLACE = 2;
    constexpr uint8_t HIGHSCORE_NOT_QUALIFIED = 255;
    constexpr char DEFAULT_NAME_CHAR = 'A';
    constexpr uint8_t EEPROM_MAGIC_OFFSET = 1;
    constexpr uint8_t SCORE_LOW_BYTE_SHIFT = 0;
    constexpr uint8_t SCORE_HIGH_BYTE_SHIFT = 8;
    constexpr uint8_t BYTE_MASK = 0xFF;
}

namespace ExplosiveConstants
{
    constexpr unsigned long EXPLOSION_DELAY_MS = 5000;
}

namespace GameplayConstants
{
    constexpr uint8_t TREASURE_DETECTION_RADIUS = 2;
    constexpr uint16_t LEVEL_COMPLETE_BONUS = 50;
    constexpr uint8_t EXPLOSIVE_BLINK_CYCLE = 12;
    constexpr uint8_t EXPLOSIVE_BLINK_ON_FRAMES = 6;
    constexpr uint8_t EXPLOSION_PATTERN_SIZE = 5;
    constexpr uint16_t EXPLOSION_SOUND_DURATION_MS = 500;
    constexpr uint8_t GOLD_COLLECT_SCORE = 10;
    constexpr uint8_t LIFE_BONUS_MULTIPLIER = 15;
    constexpr uint8_t EXPLOSIVES_BONUS_THREE = 30;
    constexpr uint8_t EXPLOSIVES_BONUS_TWO = 20;
    constexpr uint8_t EXPLOSIVES_BONUS_ONE = 10;
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

namespace SerialConstants
{
    constexpr unsigned long BAUD_RATE = 115200;
}

namespace JoystickConstants
{
    constexpr byte DEADZONE = 30;
    constexpr byte CENTER_POSITION = 128;
    constexpr uint16_t MOVEMENT_COOLDOWN_MS = 200;   
    constexpr uint16_t ANALOG_MIN = 0;
    constexpr uint16_t ANALOG_MAX = 1023;
    constexpr byte MAPPED_MIN = 0;
    constexpr byte MAPPED_MAX = 255;
}

namespace MenuConstants
{
    constexpr byte ITEM_COUNT = 1;
}

namespace GameDemoConstants
{
    constexpr uint16_t CURSOR_BLINK_MS = 150;
    constexpr uint16_t SLOW_BLINK_MS = 500;
    constexpr uint16_t FAST_BLINK_MS = 150;
    constexpr uint16_t MOVE_DELAY_MS = 150;
    constexpr uint16_t EXIT_HOLD_MS = 1500;
    
    constexpr byte POSITION_COL = 11;
    constexpr byte STATE_VALUE_COL = 7;
}

namespace BuzzerPins
{
    constexpr Pin BUZZER_PIN = 3;
}

namespace MapConstants
{
    constexpr byte WORLD_SIZE = 16;
    constexpr byte ROOM_SIZE = 8;
    constexpr byte ROOM_COUNT = 4;
    
    constexpr byte CAMERA_OFFSET_0 = 0;
    constexpr byte CAMERA_OFFSET_1 = 8;
    
    constexpr byte LEVEL_0 = 0;  
    constexpr byte LEVEL_1 = 1;  
    constexpr byte LEVEL_2 = 2;  
    constexpr byte LEVEL_3 = 3;  
    constexpr byte MIN_LEVEL = 0;
    constexpr byte MAX_LEVEL = 3;
}

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

namespace DisplayConstants
{
    constexpr uint8_t LCD_BUFFER_SIZE = 17;
    constexpr uint8_t DEFAULT_MATRIX_BRIGHTNESS = 8;
    constexpr uint8_t GOLD_BLINK_CYCLE = 22;
    constexpr uint8_t GOLD_BLINK_ON_FRAMES = 11;
    constexpr uint8_t BOMB_BLINK_CYCLE = 8;
    constexpr uint8_t BOMB_BLINK_ON_FRAMES = 4;
}

namespace SpawnConstants
{
    constexpr uint8_t DEFAULT_SPAWN_X = 1;
    constexpr uint8_t DEFAULT_SPAWN_Y = 1;
}

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

#endif
