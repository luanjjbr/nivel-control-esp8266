#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTTClient
{
public:
    MQTTClient(WiFiClient &client, const char *server, int port, const char *topic);
    void begin();
    void connect();
    void loop();
    void publish(const char *message);
    void setCallback(std::function<void(char *, uint8_t *, unsigned int)> callback);

private:
    const char *_server;
    int _port;
    const char *_topic;
    PubSubClient _client;
};

#endif
