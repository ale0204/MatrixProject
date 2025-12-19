#ifndef ACTIVE_EXPLOSIVE_H
#define ACTIVE_EXPLOSIVE_H

#include <Arduino.h>

class ActiveExplosive
{
private:
    uint8_t x, y;                    
    unsigned long placedTime;        
    bool active;                     
public:
    ActiveExplosive();
    
    void place(uint8_t posX, uint8_t posY);
    
    bool shouldExplode(unsigned long currentTime) const;
    
    // Getters
    bool isActive() const { return active; }
    uint8_t getX() const { return x; }
    uint8_t getY() const { return y; }
    
    void deactivate() { active = false; }
};

#endif // ACTIVE_EXPLOSIVE_H
