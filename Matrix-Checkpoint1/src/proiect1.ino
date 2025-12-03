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

enum class AppState : byte
{
    Intro,      // Showing intro message
    Menu,       // Main menu
    GameDemo    // Interactive demo
};

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

MenuController menuController(lcdDisplay, joystick);
GameDemo gameDemo(matrixDisplay, lcdDisplay, joystick);

AppState currentState = AppState::Intro;
unsigned long introStartTime = 0;

void showIntro()
{
    lcdDisplay.showMessage(F("Matrix Game"), F("by Alexandra"));

    matrixDisplay.clear();

    for (byte i = 0; i < MatrixConstants::SIZE; i++)
    {
        matrixDisplay.setLed(i, i, true);                              
        matrixDisplay.setLed(i, MatrixConstants::SIZE - 1 - i, true);  
    }
}

void enterMenu()
{
    currentState = AppState::Menu;
    menuController.init();
    menuController.render();

    matrixDisplay.clear();
}

void enterGameDemo()
{
    currentState = AppState::GameDemo;
    gameDemo.init();
}


void updateIntro(unsigned long currentTime)
{
    if (currentTime - introStartTime >= TimingConstants::INTRO_DURATION_MS)
    {
        enterMenu();
    }
}


void updateMenu(unsigned long currentTime)
{
    menuController.update();
    menuController.render();

    MenuAction action = menuController.consumeAction();
    if (action == MenuAction::StartGame)
    {
        enterGameDemo();
    }
}


void updateGameDemo(unsigned long currentTime)
{
    gameDemo.update(currentTime);
    gameDemo.render(currentTime);

    if (gameDemo.shouldExit())
    {
        gameDemo.resetExit();
        enterMenu();
    }
}

void setup()
{
    Serial.begin(SerialConstants::BAUD_RATE);
    Serial.println(F("Matrix Project - Checkpoint 1"));

    lcdDisplay.init();
    matrixDisplay.init();
    joystick.init();

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
