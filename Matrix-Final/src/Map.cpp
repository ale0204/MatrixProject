#include "Map.h"
#include "GameSettings.h"

constexpr uint8_t E = static_cast<uint8_t>(TileType::EMPTY);
constexpr uint8_t W = static_cast<uint8_t>(TileType::WALL);
constexpr uint8_t G = static_cast<uint8_t>(TileType::GOLD);
constexpr uint8_t D = static_cast<uint8_t>(TileType::DOOR);
constexpr uint8_t B = static_cast<uint8_t>(TileType::BOMB);
constexpr uint8_t X = static_cast<uint8_t>(TileType::EXIT);
constexpr uint8_t H = static_cast<uint8_t>(TileType::HIDDEN_GOLD);

const uint8_t LEVEL_0_LAYOUT[16][16] PROGMEM = {
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    /*1*/ {W, E, E, E, E, E, E, W, W, E, W, W, E, E, G, W},
    /*2*/ {W, E, G, E, E, E, E, W, W, E, E, G, E, G, G, W},
    /*3*/ {W, E, E, E, G, E, E, D, D, E, W, E, W, E, E, W},
    /*4*/ {W, E, E, G, E, E, E, D, D, E, W, E, E, W, G, W},
    /*5*/ {W, E, E, E, E, G, E, W, W, E, W, W, W, W, W, W},
    /*6*/ {W, E, G, E, E, E, E, W, W, E, E, E, E, E, E, X},
    /*7*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*8*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}, 
    /*9*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*10*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}, 
    /*11*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*12*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*13*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*14*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},  
    /*15*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}   
};

const uint8_t LEVEL_1_LAYOUT[16][16] PROGMEM = {
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    /*1*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*2*/ {W, E, G, E, E, E, E, W, W, G, E, E, E, E, E, X},
    /*3*/ {W, E, E, W, W, E, E, D, D, E, E, G, E, E, E, W},
    /*4*/ {W, E, E, E, E, E, E, D, D, E, E, E, E, G, E, W},
    /*5*/ {W, E, G, E, E, E, E, W, W, E, G, E, W, W, E, W},
    /*6*/ {W, E, E, E, G, E, E, W, W, E, E, E, E, E, E, W},
    /*7*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    /*8*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*9*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*10*/{W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*11*/{W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*12*/{W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*13*/{W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*14*/{W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*15*/{W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}
};

const uint8_t LEVEL_2_LAYOUT[16][16] PROGMEM = {
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

const uint8_t LEVEL_3_LAYOUT[16][16] PROGMEM = {
    /*0*/ {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    /*1*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*2*/ {W, E, G, E, E, E, E, D, D, E, G, E, W, W, W, W},
    /*3*/ {W, E, E, G, E, G, E, D, D, E, E, E, W, H, W, W},
    /*4*/ {W, E, E, E, E, E, E, W, W, G, E, E, W, W, W, W},
    /*5*/ {W, E, G, E, E, E, E, W, W, E, E, E, E, G, E, W},
    /*6*/ {W, E, E, E, G, E, E, W, W, E, E, E, E, E, E, W},
    /*7*/ {W, W, W, D, D, W, W, W, W, W, W, D, D, W, W, W},
    /*8*/ {W, W, W, D, D, W, W, W, W, W, W, D, D, W, W, W},
    /*9*/ {W, E, E, E, E, E, E, W, W, E, E, E, E, E, E, W},
    /*10*/{W, E, G, E, E, E, E, W, W, E, E, G, E, W, W, W},
    /*11*/{W, W, W, W, G, E, E, D, D, E, E, E, E, W, H, W},
    /*12*/{W, W, E, W, W, W, E, D, D, G, E, E, W, W, W, W},
    /*13*/{W, W, W, W, H, W, E, W, W, E, W, W, W, W, E, X},
    /*14*/{W, E, E, W, E, W, E, W, W, E, W, H, W, E, E, W},
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
    if (x >= MapConstants::WORLD_SIZE || y >= MapConstants::WORLD_SIZE) {
        return TileType::WALL;
    }
    
    return static_cast<TileType>(mapData[y][x]);
}

bool Map::isSolid(uint8_t x, uint8_t y) const
{
    TileType tile = getTile(x, y);
    return (tile == TileType::WALL || tile == TileType::HIDDEN_GOLD);
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
        return;
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
            mapData[y][x] = pgm_read_byte(&layout[y][x]);
        }
    }
}


void Map::loadLevel(uint8_t level, GameSettings* settings)
{
    currentLevel = level;
    
    clearMap();

    switch (level)
    {
        case MapConstants::LEVEL_0:
            createLevel0();
            break;
        case MapConstants::LEVEL_1:
            if (settings) {
                createLevel1(settings->getMinBombsForLevel(level), 
                           settings->getMaxBombsForLevel(level));
            } else {
                createLevel1(2, 4);
            }
            break;
        case MapConstants::LEVEL_2:
            if (settings) {
                createLevel2(settings->getMinBombsForLevel(level), 
                           settings->getMaxBombsForLevel(level));
            } else {
                createLevel2(4, 6);
            }
            break;
        case MapConstants::LEVEL_3:
            if (settings) {
                createLevel3(settings->getMinBombsForLevel(level), 
                           settings->getMaxBombsForLevel(level));
            } else {
                createLevel3(6, 8);
            }
            break;
        default:
            createLevel0();
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

void Map::createLevel0()
{
    loadLayoutFromArray(LEVEL_0_LAYOUT);
}

void Map::createLevel1(uint8_t minBombs, uint8_t maxBombs)
{
    loadLayoutFromArray(LEVEL_1_LAYOUT);
    placeRandomBombs(minBombs, maxBombs);
}

void Map::createLevel2(uint8_t minBombs, uint8_t maxBombs)
{
    loadLayoutFromArray(LEVEL_2_LAYOUT);
    placeRandomBombs(minBombs, maxBombs);
}

void Map::createLevel3(uint8_t minBombs, uint8_t maxBombs)
{
    loadLayoutFromArray(LEVEL_3_LAYOUT);
    placeRandomBombs(minBombs, maxBombs);
}

void Map::placeRandomBombs(uint8_t minBombs, uint8_t maxBombs)
{
    randomSeed(millis());
    
    uint8_t bombCount = random(minBombs, maxBombs + 1);
    uint8_t bombsPlaced = 0;
    
    uint8_t attempts = 0;
    while (bombsPlaced < bombCount && attempts < SystemDefaultConstants::MAX_ATTEMPTS_BOMB_PLACEMENT)
    {
        attempts++;
        
        uint8_t x = random(1, MapConstants::WORLD_SIZE - 1);
        uint8_t y = random(1, MapConstants::WORLD_SIZE - 1);
        
        if (x == MapBoundaryConstants::ROOM_SEPARATOR_LOWER || x == MapBoundaryConstants::ROOM_SEPARATOR_UPPER || y == MapBoundaryConstants::ROOM_SEPARATOR_LOWER || y == MapBoundaryConstants::ROOM_SEPARATOR_UPPER) {
            continue;
        }
        
        if (x == SpawnConstants::DEFAULT_SPAWN_X && y == SpawnConstants::DEFAULT_SPAWN_Y) {
            continue;
        }
        
        TileType tile = getTile(x, y);
        if (tile == TileType::EMPTY)
        {
            setTile(x, y, TileType::BOMB);
            bombsPlaced++;
        }
    }
}
