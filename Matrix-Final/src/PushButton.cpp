#include "PushButton.h"
#include "Constants.h"

PushButton::PushButton(Pin pin, bool usePullup)
    : buttonPin(pin),
      usePullup(usePullup),
      currentState(false),
      previousState(false),
      pressReady(false),
      lastDebounceTime(0),
      pressStartTime(0),
      longPressDetected(false)
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

            if (currentState && !previousState)
            {
                pressStartTime = currentTime;
                longPressDetected = false;
            }

            if (!currentState && previousState)
            {
                pressReady = true;
                longPressDetected = false;  // Reset long press flag
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

bool PushButton::isLongPress()
{
    if (currentState && !longPressDetected)
    {
        unsigned long pressDuration = millis() - pressStartTime;
        
        if (pressDuration >= TimingConstants::LONG_PRESS_MS)
        {
            longPressDetected = true;
            return true;  
        }
    }
    
    return false;
}
