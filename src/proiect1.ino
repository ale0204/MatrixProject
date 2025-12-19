#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LedControl.h>

#include "Constants.h"
#include "Joystick.h"
#include "MatrixDisplay.h"
#include "LCDDisplay.h"
#include "Buzzer.h"
#include "PhotoResistor.h"
#include "GameEngine.h"

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
PhotoResistor photoResistor(PhotoResistorPins::SENSOR_PIN);

GameEngine* gameEngine = nullptr;

unsigned long startupMessageTime = 0;
bool waitingForStartup = false;

void setup()
{
    Serial.begin(SerialConstants::BAUD_RATE);
    Serial.println(F("The Miner - Starting..."));

    lcdDisplay.init();
    matrixDisplay.begin();
    joystick.init();
    photoResistor.begin();
    
    matrixDisplay.setPhotoResistor(&photoResistor);

    lcdDisplay.clear();
    lcdDisplay.printCentered(0, "The Miner!");
    lcdDisplay.printCentered(1, "Let's dig :)");
    
    buzzer.playTone(ToneFrequencies::STARTUP_HZ, SoundDurations::STARTUP_TONE_MS);
    startupMessageTime = millis();
    waitingForStartup = true;

    Serial.println(F("Setup complete - Waiting for startup..."));
}

void loop()
{
    photoResistor.update();
    
    if (waitingForStartup) {
        if (millis() - startupMessageTime >= MessageDurations::STARTUP_MS) {
            waitingForStartup = false;
            gameEngine = new GameEngine(matrixDisplay, lcdDisplay, joystick, buzzer);
            gameEngine->begin();
            Serial.println(F("Game started!"));
        }
        return;
    }
    
    if (gameEngine != nullptr)
    {
        gameEngine->update();
    }
}

