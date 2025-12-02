#ifndef GAME_DEMO_H
#define GAME_DEMO_H

#include <Arduino.h>
#include "Constants.h"
#include "MatrixDisplay.h"
#include "LCDDisplay.h"
#include "Joystick.h"

/**
 * LedState - Represents the state of an LED position.
 * Used for the drawing demo where button cycles through states.
 * Order: ON -> BLINK_SLOW -> BLINK_FAST -> OFF (Off is last)
 */
enum class LedState : byte
{
    On = 0,
    BlinkSlow,
    BlinkFast,
    Off,
    COUNT  // Number of states
};

/**
 * GameDemo - Simple interactive demo for Checkpoint 1.
 * 
 * Features:
 * - A cursor LED that moves with the joystick
 * - Press button to cycle through LED states at current position:
 *   Off -> On -> BlinkSlow -> BlinkFast -> Off
 * - Cursor blinks to distinguish from placed LEDs
 * 
 * This implements the "Just joystick" option from Checkpoint 1 requirements:
 * "Draw with an LED on the 8x8 matrix. Move the LED around and when you 
 * press the button it toggles the current position on (fixed), on (blinking 
 * slow), on (blinking fast) or off."
 */
class GameDemo
{
public:
    GameDemo(MatrixDisplay& matrix, LCDDisplay& lcd, Joystick& joystick);

    void init();
    void update(unsigned long currentTime);
    void render(unsigned long currentTime);

    // Check if user wants to exit (e.g., long press or specific action)
    bool shouldExit() const;
    void resetExit();

private:
    MatrixDisplay* matrix;
    LCDDisplay* lcd;
    Joystick* joy;

    // Cursor position
    byte cursorX;
    byte cursorY;

    // LED states for all positions (8x8 = 64 positions)
    LedState ledStates[MatrixConstants::SIZE][MatrixConstants::SIZE];

    // Timing for blink effects
    unsigned long lastBlinkTime;
    bool blinkPhase;  // Toggle for blink animation

    // Exit flag (for returning to menu)
    bool wantsExit;
    unsigned long buttonHoldStart;

    // Movement timing
    unsigned long lastMoveTime;

    void moveCursor(int8_t dx, int8_t dy);
    void cycleCurrentLed();
    void updateBlink(unsigned long currentTime);
    void renderMatrix(unsigned long currentTime);
    void renderLCD();
};

#endif // GAME_DEMO_H
