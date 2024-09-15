#include "DateTimeManager.h"

DateTimeManager::DateTimeManager() : timeClient(ntpUDP, "pool.ntp.org", 0, 60000) {}

void DateTimeManager::begin()
{
    timeClient.begin();
    timeClient.update();
}

String DateTimeManager::getFormattedDateTime()
{
    timeClient.update();

    // Obtém a data e hora do NTP e formata no estilo ISO 8601
    time_t rawTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime(&rawTime);

    char formattedDateTime[30];
    snprintf(formattedDateTime, sizeof(formattedDateTime),
             "%04d-%02d-%02dT%02d:%02d:%02d.000+00:00",
             ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
             ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    return String(formattedDateTime);
}
