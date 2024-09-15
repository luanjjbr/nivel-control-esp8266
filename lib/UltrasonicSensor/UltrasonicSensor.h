#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <Arduino.h>

class UltrasonicSensor
{
private:
    int triggerPin;
    int echoPin;

public:
    UltrasonicSensor(int trigPin, int echPin);
    void begin();
    float getDistanceCm();
};

#endif
