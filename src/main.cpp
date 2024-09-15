#include <Arduino.h>
#include <Potentiometer.h>
#include <LED.h>
#include <WiFiManager.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>     // Inclua a biblioteca ArduinoJson
#include "DateTimeManager.h" // Inclua o DateTimeManager
#include "UltrasonicSensor.h"

// Configurações da rede Wi-Fi
//
//const char *ssid = "Luana"; // Substitua pelo SSID da sua rede
//
//const char *password = "LURN17@092001"; // Substitua pela senha da sua rede
// const char *ssid = "LUAN"; // Substitua pelo SSID da sua rede
// const char *password = "12345678"; // Substitua pela senha da sua rede
const char *ssid = "LUAN_NOT"; // Substitua pelo SSID da sua rede
//
const char *password = "12345678"; // Substitua pela senha da sua rede
String macSuffix;

// Configurações MQTT
const char *mqttServer = "192.168.137.1";
const int mqttPort = 1883;
const char *mqttTopic = "test_topic";
unsigned long lastPublishTime = 0;          // Variável para armazenar o último tempo de publicação
const unsigned long publishInterval = 1000; // Intervalo de publicação em milissegundos (1 segundo)

// Configurações PIN
const int potPin = A0;               // A0
const int ledPin = D4;               // D0 ou D4
UltrasonicSensor ultrasonic(D1, D2); // Pinos de exemplo

Potentiometer pot(potPin);
LED led(ledPin);
WiFiManager wifiManager(ssid, password);
WiFiClient wifiClient;
MQTTClient mqttClient(wifiClient, mqttServer, mqttPort, mqttTopic);
DateTimeManager dateTimeManager; // Cria uma instância do DateTimeManager

void callback(char *topic, uint8_t *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()
{
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("\n");

  wifiManager.connect();

  pot.begin();
  led.begin();

  mqttClient.begin();
  mqttClient.setCallback(callback);
  mqttClient.connect();
  ultrasonic.begin();

  // Obtém o MAC address da placa e extrai os 6 últimos caracteres
  String mac = WiFi.macAddress();
  macSuffix = mac.substring(9); // Extrai os últimos 6 caracteres
  macSuffix.replace(":", "");   // Remove os dois-pontos
  macSuffix.toUpperCase();      // Converte para maiúsculas
}
void loop()
{
  unsigned long currentTime = millis();
  // Lê o valor analógico do potenciômetro
  // int potValue = pot.readValue();
  // Envia o valor para o monitor serial
  // Serial.print("Potentiometer Value: ");
  // Serial.println(potValue);
  int32 distance = ultrasonic.getDistanceCm();
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  // Ajusta o intervalo de piscar do LED com base no valor do potenciômetro
  // unsigned long interval = map(potValue, 0, 1023, 100, 5000);
  led.blink(1000);
  if (currentTime - lastPublishTime >= publishInterval)
  { /**/
    String message;
    // Tempo para publicar uma nova mensagem
    lastPublishTime = currentTime;

    // Obtém a data e hora formatada
    String dateTime = dateTimeManager.getFormattedDateTime();

    if (distance > 100)
    {
      distance = 100;
    }
    // Cria a mensagem JSON usando ArduinoJson
    StaticJsonDocument<200> doc;
    doc["mac"] = macSuffix;
    doc["sensor"] = distance;
    doc["dataHora"] = dateTime;
    serializeJson(doc, message);
    // Serial.println(message.c_str());
    // Publica a mensagem JSON no tópico MQTT
    mqttClient.publish(message.c_str());
    // mqttClient.publish("ola");
  }
  // Serial.println(message.c_str());
  //  mqttClient.publish(message.c_str());
  //   Verifica a conexão Wi-Fi e MQTT
  wifiManager.checkConnection();
  mqttClient.loop();

  // Aguarda 50 ms
  delay(50);
}
