#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>

class PhotoResistor
{
private:
    byte sensorPin;
    int rawValue;
    int smoothedValue;
    
    static const uint8_t SMOOTHING_SAMPLES = 5;
    int readings[SMOOTHING_SAMPLES];
    uint8_t readIndex;
    int total;
    
    int darkThreshold;
    int brightThreshold;
    
    static const int DEFAULT_DARK_THRESHOLD = 300;
    static const int DEFAULT_BRIGHT_THRESHOLD = 700;
    
public:
    PhotoResistor(byte pin);
    
    void begin();
    void update();
    
    int getRawValue() const { return rawValue; }
    int getSmoothedValue() const { return smoothedValue; }
    uint8_t getBrightness() const;
    
    void setDarkThreshold(int threshold);
    void setBrightThreshold(int threshold);
    int getDarkThreshold() const { return darkThreshold; }
    int getBrightThreshold() const { return brightThreshold; }
    
    void calibrateDarkness();
    void calibrateBrightness();
    
    bool isDark() const { return smoothedValue < darkThreshold; }
    bool isBright() const { return smoothedValue > brightThreshold; }
    bool isNormal() const { return !isDark() && !isBright(); }
    
    void printDebug() const;
};

#endif
