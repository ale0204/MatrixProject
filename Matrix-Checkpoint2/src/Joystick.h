#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "Constants.h"
#include "PushButton.h"

/**
 * JoystickDirection - Represents the current direction of the joystick.
 */
enum class JoystickDirection : byte
{
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/**
 * Joystick - Handles analog joystick input with built-in button.
 * Includes deadzone handling and movement cooldown for smooth menu navigation.
 */
class Joystick
{
public:
    Joystick(Pin xPin, Pin yPin, Pin buttonPin);

    void init();
    void update();

    // Raw readings (0-255)
    byte readX() const;
    byte readY() const;

    // Direction detection with deadzone
    JoystickDirection getDirection() const;
    bool isMovedUp() const;
    bool isMovedDown() const;
    bool isMovedLeft() const;
    bool isMovedRight() const;

    // Movement with cooldown (for menu navigation)
    bool hasMovement() const;
    bool isMovementReady();

    // Button handling (delegates to PushButton)
    bool isButtonPressed() const;
    bool wasButtonPressed();

private:
    Pin xPin;
    Pin yPin;
    PushButton button;
    unsigned long lastMovementTime;
};

#endif // JOYSTICK_H
