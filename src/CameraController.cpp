#include "CameraController.h"

CameraController::CameraController(Player* gamePlayer)
    : cameraX{0},
      cameraY{0},
      player{gamePlayer}
{

}


void CameraController::update()
{
    uint8_t playerX = player->getX();
    uint8_t playerY = player->getY();
   
    if (playerX < MapConstants::ROOM_SIZE) {
        cameraX = 0;  
    } else {
        cameraX = MapConstants::ROOM_SIZE;  
    }
    
    if (playerY < MapConstants::ROOM_SIZE) {
        cameraY = 0;  
    } else {
        cameraY = MapConstants::ROOM_SIZE;  
    }

}


bool CameraController::globalToLocal(uint8_t globalX, uint8_t globalY,
                                      uint8_t& localX, uint8_t& localY) const
{
    
    // (similar logic to Player::move())
    int16_t calcLocalX = globalX - cameraX;
    int16_t calcLocalY = globalY - cameraY;
     
    if (calcLocalX < 0 || calcLocalX >= MapConstants::ROOM_SIZE) {
        return false;  
    }
    if (calcLocalY < 0 || calcLocalY >= MapConstants::ROOM_SIZE) {
        return false;  
    }

    localX = static_cast<uint8_t>(calcLocalX);
    localY = static_cast<uint8_t>(calcLocalY);
    
    return true;
}

bool CameraController::isInViewport(uint8_t globalX, uint8_t globalY) const
{
    bool inRangeX = (globalX >= cameraX) && (globalX < cameraX + MapConstants::ROOM_SIZE);
    bool inRangeY = (globalY >= cameraY) && (globalY < cameraY + MapConstants::ROOM_SIZE);
    
    return inRangeX && inRangeY;
}
