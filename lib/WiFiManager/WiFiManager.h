#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiManager
{
public:
    WiFiManager(const char *ssid, const char *password);
    void connect();
    void checkConnection();
    IPAddress getLocalIP();

private:
    const char *_ssid;
    const char *_password;
};

#endif
