#include "Player.h"

Player::Player(Map* gameMap)
    : x{0},
      y{0},
      goldCollected{0},
      map{gameMap}
{

}

void Player::move(int8_t dx, int8_t dy)
{
    int16_t newX = x + dx;
    int16_t newY = y + dy;
   
    if (newX < 0 || newX >= MapConstants::WORLD_SIZE) {
        return;  
    }
    if (newY < 0 || newY >= MapConstants::WORLD_SIZE) {
        return; 
    }
    
    // Cast back to uint8_t (now safe because we checked bounds)
    uint8_t targetX = static_cast<uint8_t>(newX);
    uint8_t targetY = static_cast<uint8_t>(newY);

    if (!map->isWalkable(targetX, targetY)) {
        return; 
    }
    
    x = targetX;
    y = targetY;
    
    // After moving, check if we stepped on gold
    checkAndCollectGold();
}

void Player::setPosition(uint8_t newX, uint8_t newY)
{
    x = newX;
    y = newY;
    
    // Check for gold at spawn position
    // (Unlikely, but better safe than sorry)
    checkAndCollectGold();
}

void Player::checkAndCollectGold()
{
    TileType currentTile = map->getTile(x, y);
    
    if (currentTile == TileType::GOLD) {
        goldCollected++;
        map->collectGold(x, y);
    }
}

bool Player::isOnExit() const
{
    TileType currentTile = map->getTile(x, y);
    
    return (currentTile == TileType::EXIT);
}
