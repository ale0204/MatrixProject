/**
 * The Miner - Arduino Game
 * Introduction to Robotics, Unibuc 2025-2026
 * 
 * Hardware:
 * - 8x8 LED Matrix with MAX7219 driver
 * - 16x2 LCD display
 * - Analog joystick
 * - Buzzer
 * 
 * Game:
 * - Navigate 16x16 map (4 rooms)
 * - Collect all gold
 * - Reach EXIT to complete level
 * 
 * Author: Alexandra
 * Date: December 2025
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LedControl.h>

#include "Constants.h"
#include "Joystick.h"
#include "MatrixDisplay.h"
#include "LCDDisplay.h"
#include "Buzzer.h"
#include "GameEngine.h"

// Hardware instances
LiquidCrystal lcd(
    LCDPins::RS,
    LCDPins::EN,
    LCDPins::D4,
    LCDPins::D5,
    LCDPins::D6,
    LCDPins::D7
);

LCDDisplay lcdDisplay(lcd);
MatrixDisplay matrixDisplay(MatrixPins::DIN, MatrixPins::CLK, MatrixPins::LOAD);
Joystick joystick(JoystickPins::X_PIN, JoystickPins::Y_PIN, JoystickPins::SW_PIN);
Buzzer buzzer(BuzzerPins::BUZZER_PIN);

// Game engine
GameEngine* gameEngine = nullptr;

void setup()
{
    Serial.begin(SerialConstants::BAUD_RATE);
    Serial.println(F("The Miner - Starting..."));

    // Initialize hardware
    lcdDisplay.init();
    matrixDisplay.begin();
    joystick.init();

    // Show startup message
    lcdDisplay.clear();
    lcdDisplay.printCentered(0, "THE MINER");
    lcdDisplay.printCentered(1, "Loading...");
    
    buzzer.playTone(ToneFrequencies::STARTUP_HZ, SoundDurations::STARTUP_TONE_MS);
    delay(MessageDurations::STARTUP_MS);

    gameEngine = new GameEngine(matrixDisplay, lcdDisplay, joystick, buzzer);
    gameEngine->begin();

    Serial.println(F("Setup complete - Game started!"));
}

void loop()
{
    if (gameEngine != nullptr)
    {
        gameEngine->update();
    }
}

