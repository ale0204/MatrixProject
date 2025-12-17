#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <Arduino.h>
#include "Constants.h"

class PushButton
{
public:
    PushButton(Pin pin, bool usePullup = true);

    void init();
    void update();

    bool isPressed() const;
    bool wasPressed();  
    bool isLongPress();  
private:
    Pin buttonPin;
    bool usePullup;

    bool currentState;
    bool previousState;
    bool pressReady;
    unsigned long lastDebounceTime;
    
    unsigned long pressStartTime;     
    bool longPressDetected;        
};

#endif // PUSH_BUTTON_H
