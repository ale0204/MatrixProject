#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <Arduino.h>
#include "Constants.h"

/**
 * PushButton - Handles button input with debouncing and press detection.
 * Supports short press detection.
 */
class PushButton
{
public:
    PushButton(Pin pin, bool usePullup = true);

    void init();
    void update();

    bool isPressed() const;
    bool wasPressed();  // Returns true once per press (after release)

private:
    Pin buttonPin;
    bool usePullup;

    bool currentState;
    bool previousState;
    bool pressReady;
    unsigned long lastDebounceTime;
};

#endif // PUSH_BUTTON_H
