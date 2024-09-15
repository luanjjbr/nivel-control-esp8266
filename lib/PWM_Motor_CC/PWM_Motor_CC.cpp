#include "PWM_Motor_CC.h"

PWM_Motor_CC::PWM_Motor_CC():_pin(){}

void PWM_Motor_CC::begin(){
    pinMode(_pin, INPUT);
}