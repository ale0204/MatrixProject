#include "PushButton.h"

PushButton::PushButton(Pin pin, bool usePullup)
    : buttonPin(pin),
      usePullup(usePullup),
      currentState(false),
      previousState(false),
      pressReady(false),
      lastDebounceTime(0)
{
}

void PushButton::init()
{
    pinMode(buttonPin, usePullup ? INPUT_PULLUP : INPUT);
}

void PushButton::update()
{
    unsigned long currentTime = millis();

    // Read button (LOW = pressed when using pullup)
    bool reading = usePullup ? (digitalRead(buttonPin) == LOW) : (digitalRead(buttonPin) == HIGH);

    // Debouncing
    if (reading != currentState)
    {
        if (currentTime - lastDebounceTime > TimingConstants::DEBOUNCE_MS)
        {
            previousState = currentState;
            currentState = reading;
            lastDebounceTime = currentTime;

            // Button just released - mark press as ready
            if (!currentState && previousState)
            {
                pressReady = true;
            }
        }
    }
}

bool PushButton::isPressed() const
{
    return currentState;
}

bool PushButton::wasPressed()
{
    if (pressReady)
    {
        pressReady = false;
        return true;
    }
    return false;
}
