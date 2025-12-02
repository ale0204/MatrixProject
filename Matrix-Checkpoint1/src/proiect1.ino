/**
 * Matrix Project - Checkpoint 1
 * Introduction to Robotics, Unibuc 2025-2026
 * 
 * Hardware:
 * - 8x8 LED Matrix with MAX7219 driver
 * - 16x2 LCD display
 * - Analog joystick with button
 * 
 * Features (Checkpoint 1):
 * - Intro screen on startup
 * - Simple menu with "Start Game" option
 * - Interactive drawing demo on the matrix
 * 
 * Author: Alexandra
 * Date: December 2025
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LedControl.h>

#include "Constants.h"
#include "PushButton.h"
#include "Joystick.h"
#include "MatrixDisplay.h"
#include "LCDDisplay.h"
#include "MenuController.h"
#include "GameDemo.h"

// =============================================================================
// APPLICATION STATE
// =============================================================================

/**
 * AppState - Represents the current state of the application.
 */
enum class AppState : byte
{
    Intro,      // Showing intro message
    Menu,       // Main menu
    GameDemo    // Interactive demo
};

// =============================================================================
// GLOBAL OBJECTS
// =============================================================================

// LCD object (using tested pin configuration)
LiquidCrystal lcd(
    LCDPins::RS,
    LCDPins::EN,
    LCDPins::D4,
    LCDPins::D5,
    LCDPins::D6,
    LCDPins::D7
);

// Hardware wrappers
LCDDisplay lcdDisplay(lcd);
MatrixDisplay matrixDisplay(MatrixPins::DIN, MatrixPins::CLK, MatrixPins::LOAD);
Joystick joystick(JoystickPins::X_PIN, JoystickPins::Y_PIN, JoystickPins::SW_PIN);

// Controllers
MenuController menuController(lcdDisplay, joystick);
GameDemo gameDemo(matrixDisplay, lcdDisplay, joystick);

// Application state
AppState currentState = AppState::Intro;
unsigned long introStartTime = 0;

// =============================================================================
// STATE TRANSITION FUNCTIONS
// =============================================================================

/**
 * Shows the intro screen with game title and author.
 */
void showIntro()
{
    lcdDisplay.showMessage(F("Matrix Game"), F("by Alexandra"));

    // Show a pattern on the matrix during intro
    matrixDisplay.clear();

    // Display a simple pattern (diagonal line or border)
    for (byte i = 0; i < MatrixConstants::SIZE; i++)
    {
        matrixDisplay.setLed(i, i, true);                              // Main diagonal
        matrixDisplay.setLed(i, MatrixConstants::SIZE - 1 - i, true);  // Anti-diagonal
    }
}

/**
 * Transitions to the menu state.
 */
void enterMenu()
{
    currentState = AppState::Menu;
    menuController.init();
    menuController.render();

    // Show idle pattern on matrix
    matrixDisplay.clear();
    // Could show a small icon or animation here
}

/**
 * Transitions to the game demo state.
 */
void enterGameDemo()
{
    currentState = AppState::GameDemo;
    gameDemo.init();
}

// =============================================================================
// UPDATE FUNCTIONS
// =============================================================================

/**
 * Updates the intro state.
 */
void updateIntro(unsigned long currentTime)
{
    // Wait for intro duration, then transition to menu
    if (currentTime - introStartTime >= TimingConstants::INTRO_DURATION_MS)
    {
        enterMenu();
    }
}

/**
 * Updates the menu state.
 */
void updateMenu(unsigned long currentTime)
{
    menuController.update();
    menuController.render();

    // Check for menu actions
    MenuAction action = menuController.consumeAction();
    if (action == MenuAction::StartGame)
    {
        enterGameDemo();
    }
}

/**
 * Updates the game demo state.
 */
void updateGameDemo(unsigned long currentTime)
{
    gameDemo.update(currentTime);
    gameDemo.render(currentTime);

    // Check if user wants to exit (long button press)
    if (gameDemo.shouldExit())
    {
        gameDemo.resetExit();
        enterMenu();
    }
}

// =============================================================================
// ARDUINO SETUP AND LOOP
// =============================================================================

void setup()
{
    // Initialize serial for debugging
    Serial.begin(SerialConstants::BAUD_RATE);
    Serial.println(F("Matrix Project - Checkpoint 1"));

    // Initialize all hardware
    lcdDisplay.init();
    matrixDisplay.init();
    joystick.init();

    // Show intro
    currentState = AppState::Intro;
    introStartTime = millis();
    showIntro();

    Serial.println(F("Setup complete"));
}

void loop()
{
    unsigned long currentTime = millis();

    // Update joystick (for button debouncing)
    joystick.update();

    // Update based on current state
    switch (currentState)
    {
        case AppState::Intro:
            updateIntro(currentTime);
            break;

        case AppState::Menu:
            updateMenu(currentTime);
            break;

        case AppState::GameDemo:
            updateGameDemo(currentTime);
            break;
    }
}
