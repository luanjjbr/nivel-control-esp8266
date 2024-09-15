#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echPin)
{
    triggerPin = trigPin;
    echoPin = echPin;
}

void UltrasonicSensor::begin()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float UltrasonicSensor::getDistanceCm()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distanceCm = (duration * 0.0343) / 2.0;

    return distanceCm;
}
