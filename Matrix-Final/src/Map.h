#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "Constants.h"

class Map
{
private:
    // Map data storage (16x16 = 256 bytes)
    uint8_t mapData[MapConstants::WORLD_SIZE][MapConstants::WORLD_SIZE];
    
    // Level state
    uint8_t currentLevel;   
    uint8_t totalGoldCount; 
    
    void clearMap();
    void loadLayoutFromArray(const uint8_t layout[16][16]); 
    void createLevel0();  
    void createLevel1(uint8_t minBombs, uint8_t maxBombs);  
    void createLevel2(uint8_t minBombs, uint8_t maxBombs);
    void createLevel3(uint8_t minBombs, uint8_t maxBombs);
    void placeRandomBombs(uint8_t minBombs, uint8_t maxBombs);  

public:
    Map();
    
    void loadLevel(uint8_t level, class GameSettings* settings = nullptr); 
    
    // Tile queries (read-only)
    TileType getTile(uint8_t x, uint8_t y) const;
    bool isSolid(uint8_t x, uint8_t y) const;
    bool isWalkable(uint8_t x, uint8_t y) const;
    
    // Tile modification
    void setTile(uint8_t x, uint8_t y, TileType type);
    void collectGold(uint8_t x, uint8_t y);
    
    uint8_t getTotalGold() const { return totalGoldCount; }
    uint8_t getCurrentLevel() const { return currentLevel; }
    
    // Bounds checking
    bool isInBounds(uint8_t x, uint8_t y) const;
};

#endif // MAP_H
