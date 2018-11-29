#include <mqtt.h>

using namespace std;

char *topic;
char *lwtTopic;

AsyncMqttClient mqttClient;

void connectToMqtt()
{
  Serial.println("MQTT: Connecting..");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("MQTT: Connected.");

  mqttClient.publish(lwtTopic, 0, true, "online");
  Serial.println("MQTT: Published LWT.");
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  Serial.println("MQTT: Subscribed.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId)
{
  Serial.println("MQTT: Unsubscribed.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println("MQTT: Message received.");
  Serial.print("MQTT:  topic: ");
  Serial.println(topic);
  Serial.print("MQTT: qos: ");
  Serial.println(properties.qos);
  Serial.print("MQTT: dup: ");
  Serial.println(properties.dup);
  Serial.print("MQTT: retain: ");
  Serial.println(properties.retain);
  Serial.print("MQTT: len: ");
  Serial.println(len);
  Serial.print("MQTT: index: ");
  Serial.println(index);
  Serial.print("MQTT: total: ");
  Serial.println(total);
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("MQTT: Published.");
  Serial.print("MQTT: packetId: ");
  Serial.println(packetId);
}

void setupMqtt(const char *MQTT_HOST, const uint16_t MQTT_PORT,
               const char *MQTT_USERNAME, const char *MQTT_PASSWORD,
               const char *MQTT_TOPIC, const char *MQTT_LWT_TOPIC,
               const char *CLIENT_ID)
{
  topic = (char *)MQTT_TOPIC;
  lwtTopic = (char *)MQTT_LWT_TOPIC;

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setClientId(CLIENT_ID);
  mqttClient.setCredentials(MQTT_USERNAME, MQTT_PASSWORD);
  mqttClient.setWill(lwtTopic, 0, true, "offline");
}

void publishState(uint8_t qos, bool retain, const char *payload)
{
  if (mqttClient.connected())
  {
    Serial.print("MQTT: Publish to ");
    Serial.print(topic);
    Serial.print(", QOS: ");
    Serial.print(qos);
    Serial.print(", retain: ");
    Serial.print(retain);
    Serial.print(", payload: ");
    Serial.println(payload);
    mqttClient.publish(topic, qos, retain, payload);
  }
}

void publish(char *topic, uint8_t qos, bool retain, char *payload)
{
  mqttClient.publish(topic, qos, retain, payload);
}
