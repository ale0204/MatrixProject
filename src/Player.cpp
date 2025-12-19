#include "Player.h"

Player::Player(Map* gameMap)
    : x{0},
      y{0},
      goldCollected{0},
      lives{3},
      explosives{0},
      map{gameMap}
{

}

bool Player::move(int8_t dx, int8_t dy)
{
    int16_t newX = x + dx;
    int16_t newY = y + dy;
   
    if (newX < 0 || newX >= MapConstants::WORLD_SIZE) {
        return false;  // Out of bounds
    }
    if (newY < 0 || newY >= MapConstants::WORLD_SIZE) {
        return false;  // Out of bounds
    }
    
    // Cast back to uint8_t (now safe because we checked bounds)
    uint8_t targetX = static_cast<uint8_t>(newX);
    uint8_t targetY = static_cast<uint8_t>(newY);

    if (!map->isWalkable(targetX, targetY)) {
        return false;  // Wall blocking
    }
    
    x = targetX;
    y = targetY;
    
    // After moving, check what we stepped on
    checkAndCollectGold();  // Check for gold
    checkBomb();            // Check for bomb
    
    return true;
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

bool Player::checkBomb()
{
    TileType currentTile = map->getTile(x, y);
    
    if (currentTile == TileType::BOMB)
    {
        if (lives > 0) {
            lives--;
        }
        
        map->setTile(x, y, TileType::EMPTY);
        
        return true;
    }
    
    return false;
}

bool Player::isOnExit() const
{
    TileType currentTile = map->getTile(x, y);
    
    return (currentTile == TileType::EXIT);
}

bool Player::isNearHiddenTreasure() const
{
    for (int8_t dy = -GameplayConstants::TREASURE_DETECTION_RADIUS; dy <= GameplayConstants::TREASURE_DETECTION_RADIUS; dy++)
    {
        for (int8_t dx = -GameplayConstants::TREASURE_DETECTION_RADIUS; dx <= GameplayConstants::TREASURE_DETECTION_RADIUS; dx++)
        {
            if (dx == 0 && dy == 0) continue;
            
            int8_t checkX = x + dx;
            int8_t checkY = y + dy;
            
            if (checkX >= 0 && checkX < MapConstants::WORLD_SIZE &&
                checkY >= 0 && checkY < MapConstants::WORLD_SIZE)
            {
                if (map->getTile(checkX, checkY) == TileType::HIDDEN_GOLD)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}
