#include "PhotoResistor.h"

PhotoResistor::PhotoResistor(byte pin)
    : sensorPin(pin)
    , rawValue(0)
    , smoothedValue(0)
    , readIndex(0)
    , total(0)
    , darkThreshold(DEFAULT_DARK_THRESHOLD)
    , brightThreshold(DEFAULT_BRIGHT_THRESHOLD)
{
        for (uint8_t i = 0; i < SMOOTHING_SAMPLES; i++) {
        readings[i] = 0;
    }
}

void PhotoResistor::begin()
{
    pinMode(sensorPin, INPUT);
    
        for (uint8_t i = 0; i < SMOOTHING_SAMPLES; i++) {
        readings[i] = analogRead(sensorPin);
        total += readings[i];
    }
    
    smoothedValue = total / SMOOTHING_SAMPLES;
    rawValue = smoothedValue;
}

void PhotoResistor::update()
{
        rawValue = analogRead(sensorPin);
    
    total -= readings[readIndex];
    
        readings[readIndex] = rawValue;
    total += rawValue;
    
        readIndex++;
    if (readIndex >= SMOOTHING_SAMPLES) {
        readIndex = 0;
    }
    
        smoothedValue = total / SMOOTHING_SAMPLES;
}

uint8_t PhotoResistor::getBrightness() const
{
        return map(smoothedValue, 0, 1023, 0, 100);
}

void PhotoResistor::setDarkThreshold(int threshold)
{
    if (threshold < 0) threshold = 0;
    if (threshold > 1023) threshold = 1023;
    
    darkThreshold = threshold;
}

void PhotoResistor::setBrightThreshold(int threshold)
{
    if (threshold < 0) threshold = 0;
    if (threshold > 1023) threshold = 1023;
    
    brightThreshold = threshold;
}

void PhotoResistor::calibrateDarkness()
{
        update();      
            darkThreshold = smoothedValue + 50;
    
    if (darkThreshold > 1023) darkThreshold = 1023;
}

void PhotoResistor::calibrateBrightness()
{
        update();      
        brightThreshold = smoothedValue - 50;
    
    if (brightThreshold < 0) brightThreshold = 0;
}

void PhotoResistor::printDebug() const
{
    Serial.print("PhotoResistor - Raw: ");
    Serial.print(rawValue);
    Serial.print(" | Smoothed: ");
    Serial.print(smoothedValue);
    Serial.print(" | Brightness: ");
    Serial.print(getBrightness());
    Serial.print("% | Thresholds: [D<");
    Serial.print(darkThreshold);
    Serial.print(", B>");
    Serial.print(brightThreshold);
    Serial.print("] | Status: ");
    
    if (isDark()) {
        Serial.println("DARK");
    } else if (isBright()) {
        Serial.println("BRIGHT");
    } else {
        Serial.println("NORMAL");
    }
}
