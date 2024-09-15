#include "WiFiManager.h"

WiFiManager::WiFiManager(const char *ssid, const char *password) : _ssid(ssid), _password(password) {}

void WiFiManager::connect()
{
    Serial.print("Connecting to ");
    Serial.print(_ssid);
    Serial.print("...");
    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiManager::checkConnection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connection lost. Attempting to reconnect...");
        WiFi.disconnect();
        connect();
    }
    else
    {
        // Serial.println("Connection stable.");
    }
}

IPAddress WiFiManager::getLocalIP()
{
    return WiFi.localIP();
}
