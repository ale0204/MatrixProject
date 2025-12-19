#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <Arduino.h>
#include "Player.h"
#include "Constants.h"

class CameraController
{
private:
    uint8_t cameraX;
    uint8_t cameraY;
    Player* player;

public:
    CameraController(Player* gamePlayer);
    
    void update();
    
    uint8_t getCameraX() const { return cameraX; }
    uint8_t getCameraY() const { return cameraY; }
    
    bool globalToLocal(uint8_t globalX, uint8_t globalY, 
                       uint8_t& localX, uint8_t& localY) const;
    
    bool isInViewport(uint8_t globalX, uint8_t globalY) const;
};

#endif // CAMERA_CONTROLLER_H
