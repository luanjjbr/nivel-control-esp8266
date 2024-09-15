#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED
{
public:
    LED(int pin);
    void begin();
    void blink(unsigned long interval);

private:
    int _pin;
    unsigned long _previousMillis;
    bool _ledState;
};

#endif
