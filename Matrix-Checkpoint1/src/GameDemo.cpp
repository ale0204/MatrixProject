#include "GameDemo.h"

GameDemo::GameDemo(MatrixDisplay& matrixRef, LCDDisplay& lcdRef, Joystick& joystickRef)
    : matrix(&matrixRef),
      lcd(&lcdRef),
      joy(&joystickRef),
      cursorX(0),
      cursorY(0),
      lastBlinkTime(0),
      blinkPhase(false),
      wantsExit(false),
      buttonHoldStart(0),
      lastMoveTime(0)
{
    // Initialize all LED states to Off
    for (byte y = 0; y < MatrixConstants::SIZE; y++)
    {
        for (byte x = 0; x < MatrixConstants::SIZE; x++)
        {
            ledStates[y][x] = LedState::Off;
        }
    }
}

void GameDemo::init()
{
    // Clear all LED states first
    for (byte y = 0; y < MatrixConstants::SIZE; y++)
    {
        for (byte x = 0; x < MatrixConstants::SIZE; x++)
        {
            ledStates[y][x] = LedState::Off;
        }
    }

    // Spawn initial LED at center (4,4) with state ON
    cursorX = MatrixConstants::SIZE / 2;
    cursorY = MatrixConstants::SIZE / 2;
    ledStates[cursorY][cursorX] = LedState::On;

    // Reset timing
    lastBlinkTime = millis();
    blinkPhase = false;
    wantsExit = false;
    buttonHoldStart = 0;
    lastMoveTime = millis();

    // Clear displays
    matrix->clear();
    renderLCD();
}

void GameDemo::update(unsigned long currentTime)
{
    // Handle joystick movement with delay
    if (currentTime - lastMoveTime >= GameDemoConstants::MOVE_DELAY_MS)
    {
        JoystickDirection direction = joy->getDirection();

        int8_t dx = 0;
        int8_t dy = 0;

        switch (direction)
        {
            case JoystickDirection::LEFT:
                dx = -1;
                break;
            case JoystickDirection::RIGHT:
                dx = 1;
                break;
            case JoystickDirection::UP:
                dy = -1;  // Up decreases Y (row 0 is top)
                break;
            case JoystickDirection::DOWN:
                dy = 1;
                break;
            default:
                break;
        }

        if (dx != 0 || dy != 0)
        {
            moveCursor(dx, dy);
            lastMoveTime = currentTime;
        }
    }

    // Handle button press to cycle LED state
    if (joy->wasButtonPressed())
    {
        cycleCurrentLed();
    }

    // Handle long button hold to exit (check if button is being held)
    if (joy->isButtonPressed())
    {
        if (buttonHoldStart == 0)
        {
            buttonHoldStart = currentTime;
        }
        else if (currentTime - buttonHoldStart >= GameDemoConstants::EXIT_HOLD_MS)
        {
            wantsExit = true;
        }
    }
    else
    {
        buttonHoldStart = 0;
    }

    // Update blink timing
    updateBlink(currentTime);
}

void GameDemo::render(unsigned long currentTime)
{
    renderMatrix(currentTime);
}

bool GameDemo::shouldExit() const
{
    return wantsExit;
}

void GameDemo::resetExit()
{
    wantsExit = false;
}

void GameDemo::moveCursor(int8_t dx, int8_t dy)
{
    // Turn off LED at current position, before moving
    ledStates[cursorY][cursorX] = LedState::Off;

    // Move cursor (wrap around edges)
    cursorX = (cursorX + dx + MatrixConstants::SIZE) % MatrixConstants::SIZE;
    cursorY = (cursorY + dy + MatrixConstants::SIZE) % MatrixConstants::SIZE;

    // Turn on LED at new position
    ledStates[cursorY][cursorX] = LedState::On;

    // Update LCD to show new position and state
    renderLCD();
}

void GameDemo::cycleCurrentLed()
{
    LedState current = ledStates[cursorY][cursorX];
    byte nextState = (static_cast<byte>(current) + 1) % static_cast<byte>(LedState::COUNT);
    ledStates[cursorY][cursorX] = static_cast<LedState>(nextState);

    // Update LCD to show current state
    renderLCD();
}

void GameDemo::updateBlink(unsigned long currentTime)
{
    // Update global blink phase for cursor
    if (currentTime - lastBlinkTime >= GameDemoConstants::CURSOR_BLINK_MS)
    {
        lastBlinkTime = currentTime;
        blinkPhase = !blinkPhase;
    }
}

void GameDemo::renderMatrix(unsigned long currentTime)
{
    // Calculate blink states for slow and fast
    bool slowBlinkOn = ((currentTime / GameDemoConstants::SLOW_BLINK_MS) % 2) == 0;
    bool fastBlinkOn = ((currentTime / GameDemoConstants::FAST_BLINK_MS) % 2) == 0;

    // Render all LEDs based on their state
    for (byte y = 0; y < MatrixConstants::SIZE; y++)
    {
        for (byte x = 0; x < MatrixConstants::SIZE; x++)
        {
            bool ledOn = false;
            LedState state = ledStates[y][x];

            switch (state)
            {
                case LedState::On:
                    // ON state is always solid (no blinking)
                    ledOn = true;
                    break;
                case LedState::BlinkSlow:
                    ledOn = slowBlinkOn;
                    break;
                case LedState::BlinkFast:
                    ledOn = fastBlinkOn;
                    break;
                case LedState::Off:
                default:
                    ledOn = false;
                    break;
            }

            matrix->setLed(y, x, ledOn);
        }
    }
}

void GameDemo::renderLCD()
{
    lcd->clear();

    // Line 0: Game title and position
    lcd->printAt(0, 0, F("Draw Mode"));

    // Show position
    lcd->printAt(GameDemoConstants::POSITION_COL, 0, F("("));
    lcd->getLcd()->print(cursorX);
    lcd->getLcd()->print(F(","));
    lcd->getLcd()->print(cursorY);
    lcd->getLcd()->print(F(")"));

    // Line 1: Current LED state at cursor
    lcd->printAt(0, 1, F("State: "));

    LedState state = ledStates[cursorY][cursorX];
    switch (state)
    {
        case LedState::Off:
            lcd->printAt(GameDemoConstants::STATE_VALUE_COL, 1, F("OFF"));
            break;
        case LedState::On:
            lcd->printAt(GameDemoConstants::STATE_VALUE_COL, 1, F("ON"));
            break;
        case LedState::BlinkSlow:
            lcd->printAt(GameDemoConstants::STATE_VALUE_COL, 1, F("SLOW"));
            break;
        case LedState::BlinkFast:
            lcd->printAt(GameDemoConstants::STATE_VALUE_COL, 1, F("FAST"));
            break;
        default:
            break;
    }
}
