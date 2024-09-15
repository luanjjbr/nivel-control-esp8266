#include "LED.h"

LED::LED(int pin) : _pin(pin), _previousMillis(0), _ledState(false) {}

void LED::begin()
{
    pinMode(_pin, OUTPUT);
}

void LED::blink(unsigned long interval)
{
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMillis >= interval)
    {
        _previousMillis = currentMillis;
        _ledState = !_ledState;
        digitalWrite(_pin, _ledState ? LOW : HIGH); // Inversão para LED embutido
    }
}
