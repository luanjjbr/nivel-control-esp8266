#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

class Potentiometer
{
public:
    Potentiometer(int pin);
    void begin();
    int readValue();

private:
    int _pin;
};

#endif
