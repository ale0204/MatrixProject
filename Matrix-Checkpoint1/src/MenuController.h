#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <Arduino.h>
#include "Constants.h"
#include "LCDDisplay.h"
#include "Joystick.h"

/**
 * MenuItem - Represents available menu options.
 * For Checkpoint 1, only Start Game is implemented.
 * More items will be added later (Highscore, Settings, About, How to Play).
 */
enum class MenuItem : byte
{
    StartGame = 0,
    // Future items:
    // Highscore,
    // Settings,
    // About,
    // HowToPlay,
    COUNT  // Keep this last - represents total number of items
};

/**
 * MenuAction - Actions that can be triggered from the menu.
 */
enum class MenuAction : byte
{
    None,
    StartGame
    // Future actions:
    // ShowHighscore,
    // OpenSettings,
    // ShowAbout,
    // ShowHowToPlay
};

/**
 * MenuController - Handles menu display and navigation.
 * Uses joystick UP/DOWN to navigate and button to select.
 */
class MenuController
{
public:
    MenuController(LCDDisplay& lcdDisplay, Joystick& joystick);

    void init();
    void update();
    void render();

    // Check for and consume pending action
    MenuAction consumeAction();

    // Get current selection
    MenuItem getCurrentItem() const;

private:
    LCDDisplay* lcd;
    Joystick* joy;

    MenuItem currentItem;
    MenuAction pendingAction;

    bool needsRedraw;

    // Helper to get menu item text
    const __FlashStringHelper* getItemText(MenuItem item) const;

    void navigateUp();
    void navigateDown();
    void selectItem();
};

#endif // MENU_CONTROLLER_H
