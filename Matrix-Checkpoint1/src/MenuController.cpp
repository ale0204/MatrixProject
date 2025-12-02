#include "MenuController.h"

MenuController::MenuController(LCDDisplay& lcdDisplay, Joystick& joystick)
    : lcd(&lcdDisplay),
      joy(&joystick),
      currentItem(MenuItem::StartGame),
      pendingAction(MenuAction::None),
      needsRedraw(true)
{
}

void MenuController::init()
{
    currentItem = MenuItem::StartGame;
    pendingAction = MenuAction::None;
    needsRedraw = true;
}

void MenuController::update()
{
    // Check for joystick navigation (with movement cooldown)
    if (joy->isMovementReady())
    {
        JoystickDirection dir = joy->getDirection();

        if (dir == JoystickDirection::UP)
        {
            navigateUp();
        }
        else if (dir == JoystickDirection::DOWN)
        {
            navigateDown();
        }
    }

    // Check for button press to select
    if (joy->wasButtonPressed())
    {
        selectItem();
    }
}

void MenuController::render()
{
    if (!needsRedraw)
    {
        return;
    }

    lcd->clear();

    // Line 0: Menu title with arrows
    // Show up arrow if not at first item, down arrow if not at last
    byte itemIndex = static_cast<byte>(currentItem);
    byte maxIndex = static_cast<byte>(MenuItem::COUNT) - 1;

    // For now with only 1 item, no arrows needed
    // But structure is ready for multiple items
    lcd->printAt(0, 0, F("=== MENU ==="));

    // Line 1: Current selection with indicator
    lcd->printAt(0, 1, F("> "));
    lcd->printAt(2, 1, getItemText(currentItem));

    // Show navigation hints if multiple items exist
    if (maxIndex > 0)
    {
        if (itemIndex > 0)
        {
            lcd->printAt(LCDConstants::COLS - 1, 0, F("^"));  // Can go up
        }
        if (itemIndex < maxIndex)
        {
            lcd->printAt(LCDConstants::COLS - 1, 1, F("v"));  // Can go down
        }
    }

    needsRedraw = false;
}

MenuAction MenuController::consumeAction()
{
    MenuAction action = pendingAction;
    pendingAction = MenuAction::None;
    return action;
}

MenuItem MenuController::getCurrentItem() const
{
    return currentItem;
}

const __FlashStringHelper* MenuController::getItemText(MenuItem item) const
{
    switch (item)
    {
        case MenuItem::StartGame:
            return F("Start Game");
        // Future items:
        // case MenuItem::Highscore:
        //     return F("Highscore");
        // case MenuItem::Settings:
        //     return F("Settings");
        // case MenuItem::About:
        //     return F("About");
        // case MenuItem::HowToPlay:
        //     return F("How to Play");
        default:
            return F("???");
    }
}

void MenuController::navigateUp()
{
    byte current = static_cast<byte>(currentItem);
    if (current > 0)
    {
        current--;
        currentItem = static_cast<MenuItem>(current);
        needsRedraw = true;
    }
}

void MenuController::navigateDown()
{
    byte current = static_cast<byte>(currentItem);
    byte maxIndex = static_cast<byte>(MenuItem::COUNT) - 1;

    if (current < maxIndex)
    {
        current++;
        currentItem = static_cast<MenuItem>(current);
        needsRedraw = true;
    }
}

void MenuController::selectItem()
{
    switch (currentItem)
    {
        case MenuItem::StartGame:
            pendingAction = MenuAction::StartGame;
            break;
        // Future items will set corresponding actions
        default:
            break;
    }
}
