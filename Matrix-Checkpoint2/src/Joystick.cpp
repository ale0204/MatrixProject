#include "Joystick.h"

Joystick::Joystick(Pin xPin, Pin yPin, Pin buttonPin)
    : xPin(xPin),
      yPin(yPin),
      button(buttonPin),
      lastMovementTime(0)
{
}

void Joystick::init()
{
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    button.init();
}

void Joystick::update()
{
    button.update();
}

byte Joystick::readX() const
{
    return map(analogRead(xPin), 
               JoystickConstants::ANALOG_MIN, JoystickConstants::ANALOG_MAX, 
               JoystickConstants::MAPPED_MIN, JoystickConstants::MAPPED_MAX);
}

byte Joystick::readY() const
{
    return map(analogRead(yPin), 
               JoystickConstants::ANALOG_MIN, JoystickConstants::ANALOG_MAX, 
               JoystickConstants::MAPPED_MIN, JoystickConstants::MAPPED_MAX);
}

JoystickDirection Joystick::getDirection() const
{
    byte x = readX();
    byte y = readY();

    // Check horizontal movement (left/right)
    // Note: might need to swap depending on physical orientation
    if (x < JoystickConstants::CENTER_POSITION - JoystickConstants::DEADZONE)
    {
        return JoystickDirection::RIGHT;
    }
    if (x > JoystickConstants::CENTER_POSITION + JoystickConstants::DEADZONE)
    {
        return JoystickDirection::LEFT;
    }

    // Check vertical movement (up/down)
    if (y < JoystickConstants::CENTER_POSITION - JoystickConstants::DEADZONE)
    {
        return JoystickDirection::DOWN;
    }
    if (y > JoystickConstants::CENTER_POSITION + JoystickConstants::DEADZONE)
    {
        return JoystickDirection::UP;
    }

    return JoystickDirection::NONE;
}

bool Joystick::isMovedUp() const
{
    return readY() > JoystickConstants::CENTER_POSITION + JoystickConstants::DEADZONE;
}

bool Joystick::isMovedDown() const
{
    return readY() < JoystickConstants::CENTER_POSITION - JoystickConstants::DEADZONE;
}

bool Joystick::isMovedLeft() const
{
    return readX() > JoystickConstants::CENTER_POSITION + JoystickConstants::DEADZONE;
}

bool Joystick::isMovedRight() const
{
    return readX() < JoystickConstants::CENTER_POSITION - JoystickConstants::DEADZONE;
}

bool Joystick::hasMovement() const
{
    return getDirection() != JoystickDirection::NONE;
}

bool Joystick::isMovementReady()
{
    unsigned long currentTime = millis();
    if (hasMovement() && (currentTime - lastMovementTime >= JoystickConstants::MOVEMENT_COOLDOWN_MS))
    {
        lastMovementTime = currentTime;
        return true;
    }
    return false;
}

bool Joystick::isButtonPressed() const
{
    return button.isPressed();
}

bool Joystick::wasButtonPressed()
{
    return button.wasPressed();
}
