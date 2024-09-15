#ifndef DATETIMEMANAGER_H
#define DATETIMEMANAGER_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

class DateTimeManager
{
public:
    DateTimeManager();
    void begin();
    String getFormattedDateTime();

private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
};

#endif
