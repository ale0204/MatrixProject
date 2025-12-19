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
    uint8_t lives;
    uint8_t explosives;
    Map* map;

public:
    Player(Map* gameMap);
    
    bool move(int8_t dx, int8_t dy);
    void setPosition(uint8_t newX, uint8_t newY);
    
    uint8_t getX() const { return x; }
    uint8_t getY() const { return y; }
    
    uint8_t getGoldCollected() const { return goldCollected; }
    void resetGold() { goldCollected = 0; }
    
    uint8_t getLives() const { return lives; }
    void setLives(uint8_t l) { lives = l; }
    void resetLives() { lives = 3; }  // Reset to default
    bool isDead() const { return lives == 0; }
    
    uint8_t getExplosivesCount() const { return explosives; }
    void setExplosivesCount(uint8_t count) { explosives = count; }
    void resetExplosives() { explosives = 8; }  
    bool hasExplosives() const { return explosives > 0; }
    
    bool isOnExit() const;
    bool isNearHiddenTreasure() const;
    
private:
    void checkAndCollectGold();
    bool checkBomb();
};

#endif // PLAYER_H
