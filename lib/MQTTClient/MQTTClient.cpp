#include "MQTTClient.h"

MQTTClient::MQTTClient(WiFiClient &client, const char *server, int port, const char *topic)
    : _server(server), _port(port), _topic(topic), _client(client) {}

void MQTTClient::begin()
{
    _client.setServer(_server, _port);
}

void MQTTClient::connect()
{
    while (!_client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (_client.connect("ESP8266Client"))
        {
            Serial.println("connected");
            _client.subscribe(_topic);
            delay(1000);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MQTTClient::loop()
{
    _client.loop();
}

void MQTTClient::publish(const char *message)
{
    _client.publish(_topic, message);
}

void MQTTClient::setCallback(std::function<void(char *, uint8_t *, unsigned int)> callback)
{
    _client.setCallback(callback);
}
