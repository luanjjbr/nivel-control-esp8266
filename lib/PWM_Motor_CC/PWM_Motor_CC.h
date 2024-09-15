#ifndef PWMMOTORCC_H
#define PWMMOTORCC_H

#include <Arduino.h>

class PWM_Motor_CC
{
private:
    int _pin;
public:
    void begin();
    void setMotor();
};
#endif
