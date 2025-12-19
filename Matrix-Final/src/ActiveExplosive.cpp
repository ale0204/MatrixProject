#include "ActiveExplosive.h"
#include "Constants.h"

ActiveExplosive::ActiveExplosive()
    : x(0),
      y(0),
      placedTime(0),
      active(false)  {
}

void ActiveExplosive::place(uint8_t posX, uint8_t posY)
{
    x = posX;                         
    y = posY;                         
    placedTime = millis();            
    active = true;                
}

bool ActiveExplosive::shouldExplode(unsigned long currentTime) const
{
    if (!active) 
    {
        return false;      
    }
    
    unsigned long timeSincePlaced = currentTime - placedTime;
    
    return (timeSincePlaced >= ExplosiveConstants::EXPLOSION_DELAY_MS);  
}
