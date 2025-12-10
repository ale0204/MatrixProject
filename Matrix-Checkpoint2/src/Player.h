#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "Map.h"
#include "Constants.h"

class Player
{
private:
    uint8_t x;
    uint8_t y;
    uint8_t goldCollected;
    Map* map;

public:
    Player(Map* gameMap);
    
    void move(int8_t dx, int8_t dy);
    void setPosition(uint8_t newX, uint8_t newY);
    
    uint8_t getX() const { return x; }
    uint8_t getY() const { return y; }
    
    uint8_t getGoldCollected() const { return goldCollected; }
    void resetGold() { goldCollected = 0; }
    
    bool isOnExit() const;

private:
    void checkAndCollectGold();
};

#endif // PLAYER_H
