#include "Map.h"

constexpr uint8_t E = static_cast<uint8_t>(TileType::EMPTY);  // Empty space (walkable)
constexpr uint8_t W = static_cast<uint8_t>(TileType::WALL);   // Wall (solid)
constexpr uint8_t G = static_cast<uint8_t>(TileType::GOLD);   // Gold piece (collectible)
constexpr uint8_t D = static_cast<uint8_t>(TileType::DOOR);   // Door (walkable passage)
constexpr uint8_t X = static_cast<uint8_t>(TileType::EXIT);   // Exit (level complete)


const uint8_t LEVEL_1_LAYOUT[16][16] PROGMEM = {
    // X:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*1*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W}, 
    /*2*/ {W, E, G, E, E, E, E, W, W, G, E, E, E, E, E, X}, 
    /*3*/ {W, E, E, W, W, E, E, D, D, E, E, G, E, E, E, W}, 
    /*4*/ {W, E, E, E, E, E, E, D, D, E, E, E, E, G, E, W}, 
    /*5*/ {W, E, G, E, E, E, E, W, W, E, G, E, W, W, E, W}, 
    /*6*/ {W, E, E, E, G, E, E, W, W, E, E, E, E, E, E, W},  
    /*7*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*8*/ {W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W}, 
    /*9*/ {W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*10*/{W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W}, 
    /*11*/{W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*12*/{W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*13*/{W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*14*/{W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*15*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}   
};

// LEVEL 2: 3 rooms accessible (NW, NE, SW), Exit in SW room
const uint8_t LEVEL_2_LAYOUT[16][16] PROGMEM = {
    // X:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*1*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},  
    /*2*/ {W, E, G, E, W, E, E, D, D, G, E, E, W, E, E, W},  
    /*3*/ {W, E, E, E, E, E, E, D, D, E, E, E, E, E, E, W},  
    /*4*/ {W, E, E, G, E, E, E, W, W, E, G, E, E, E, E, W},  
    /*5*/ {W, E, E, E, E, G, E, W, W, E, E, E, E, G, E, W},  
    /*6*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},  
    /*7*/ {W, W, W, D, D, W, W, W, W, W, W, W, W, W, W, W},  
    /*8*/ {W, W, W, D, D, W, W, W, W, W, W, W, W, W, W, W}, 
    /*9*/ {W, E, E, E, E, E, E, W, W, W, W, W, W, W, W, W},  
    /*10*/{W, E, E, G, E, E, E, W, W, W, W, W, W, W, W, W}, 
    /*11*/{W, E, E, E, E, G, E, W, W, W, W, W, W, W, W, W},  
    /*12*/{W, E, G, E, W, E, E, W, W, W, W, W, W, W, W, W}, 
    /*13*/{W, E, E, E, E, E, E, W, W, W, W, W, W, W, W, W}, 
    /*14*/{W, E, E, E, E, E, G, W, W, W, W, W, W, W, W, W}, 
    /*15*/{W, W, W, X, W, W, W, W, W, W, W, W, W, W, W, W}  
};

// LEVEL 3: 4 rooms accessible (all), Exit in SE room
const uint8_t LEVEL_3_LAYOUT[16][16] PROGMEM = {
    // X:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}, 
    /*1*/ {W, E, E, E, E, E, E, W, E, E, E, E, E, E, E, W},  
    /*2*/ {W, E, G, E, E, E, E, D, E, E, G, E, E, E, E, W},  
    /*3*/ {W, E, E, W, E, G, E, D, E, E, E, E, W, E, E, W},  
    /*4*/ {W, E, E, E, E, E, E, W, E, G, E, E, E, E, E, W},  
    /*5*/ {W, E, G, E, E, E, E, W, E, E, E, E, E, G, E, W},  
    /*6*/ {W, E, E, E, G, E, E, W, E, E, E, E, E, E, E, W},  
    /*7*/ {W, W, W, D, D, W, W, W, W, W, W, W, W, W, W, W},  
    /*8*/ {W, W, W, D, D, W, W, W, W, W, W, W, W, W, W, W}, 
    /*9*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},  
    /*10*/{W, E, G, E, E, E, E, W, W, E, E, G, E, E, E, W},  
    /*11*/{W, E, E, E, G, E, E, D, D, E, E, E, E, E, E, W},  
    /*12*/{W, E, E, W, E, E, E, D, D, G, E, E, W, E, E, W},  
    /*13*/{W, E, E, E, E, G, E, W, W, E, E, E, E, E, E, X},  
    /*14*/{W, E, E, E, E, E, E, W, W, E, E, G, E, E, E, W},  
    /*15*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}  
};

Map::Map()
    : currentLevel{0},     
      totalGoldCount{0}     
{
    clearMap();
}

void Map::clearMap()
{
    memset(mapData, static_cast<uint8_t>(TileType::EMPTY), sizeof(mapData));
}


TileType Map::getTile(uint8_t x, uint8_t y) const
{
    // Bounds checking: out of bounds = treat as wall
    if (x >= MapConstants::WORLD_SIZE || y >= MapConstants::WORLD_SIZE) {
        return TileType::WALL;  // Out of bounds acts as solid barrier
    }
    
    // Cast the stored byte back to TileType enum
    return static_cast<TileType>(mapData[y][x]);
}

bool Map::isSolid(uint8_t x, uint8_t y) const
{
    TileType tile = getTile(x, y);
    
    // Only WALL blocks movement (for now)
    return (tile == TileType::WALL);
}

bool Map::isWalkable(uint8_t x, uint8_t y) const
{
    return !isSolid(x, y);
}

bool Map::isInBounds(uint8_t x, uint8_t y) const
{
    return (x < MapConstants::WORLD_SIZE && y < MapConstants::WORLD_SIZE);
}

void Map::setTile(uint8_t x, uint8_t y, TileType type)
{
    if (!isInBounds(x, y)) {
        return;  // Silent fail - prevent memory corruption
    }
    
    mapData[y][x] = static_cast<uint8_t>(type);
}

void Map::collectGold(uint8_t x, uint8_t y)
{
    if (getTile(x, y) == TileType::GOLD) {
        setTile(x, y, TileType::EMPTY);
    }
}

void Map::loadLayoutFromArray(const uint8_t layout[16][16])
{
    for (uint8_t y = 0; y < MapConstants::WORLD_SIZE; y++) {
        for (uint8_t x = 0; x < MapConstants::WORLD_SIZE; x++) {
            // Read byte from FLASH and write to RAM
            mapData[y][x] = pgm_read_byte(&layout[y][x]);
        }
    }
}


void Map::loadLevel(uint8_t level)
{
    // Store current level
    currentLevel = level;
    
    clearMap();

    switch (level)
    {
        case MapConstants::LEVEL_1:
            createLevel1();
            break;
        case MapConstants::LEVEL_2:
            createLevel2();
            break;
        case MapConstants::LEVEL_3:
            createLevel3();
            break;
        default:
            // Invalid level - default to Level 1
            createLevel1();
            break;
    }
    
    totalGoldCount = 0;
    for (uint8_t y = 0; y < MapConstants::WORLD_SIZE; y++) {
        for (uint8_t x = 0; x < MapConstants::WORLD_SIZE; x++) {
            if (getTile(x, y) == TileType::GOLD) {
                totalGoldCount++;
            }
        }
    }
}

void Map::createLevel1()
{
    loadLayoutFromArray(LEVEL_1_LAYOUT);
}

void Map::createLevel2()
{
    loadLayoutFromArray(LEVEL_2_LAYOUT);
}

void Map::createLevel3()
{
    loadLayoutFromArray(LEVEL_3_LAYOUT);
}
