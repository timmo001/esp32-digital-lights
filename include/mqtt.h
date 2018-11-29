#ifndef MQTT_H
#define MQTT_H

#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

void setupMqtt(const char *MQTT_HOST, const uint16_t MQTT_PORT,
               const char *MQTT_USERNAME, const char *MQTT_PASSWORD,
               const char *MQTT_TOPIC, const char *MQTT_LWT_TOPIC,
               const char *CLIENT_ID);

void connectToMqtt();

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

void publishState(uint8_t qos, bool retain, const char *payload);

void publish(char*topic, uint8_t qos, bool retain, const char *payload);

#endif
