#include <main.h>

using namespace std;

void updateState()
{
  // float ldr = analogRead(LDR_PIN);
  // Serial.print("LDR: ");
  // Serial.println(ldr);
  // if (!ldr || ldr != ldr)
  //   return;

  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject &root = jsonBuffer.createObject();
  // root["ldr"] = ldr;

  char payload[root.measureLength() + 1];
  root.printTo(payload, sizeof(payload));

  publishState(0, true, payload);
}

void processStateJson(char *payload)
{
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(payload);

  if (!root.success())
  {
    Serial.println("ParseObject() failed, skipping...");
    return;
  }

  if (root.containsKey("state") && strcasecmp(root["state"].as<const char *>(), "ON") == 0)
  {
    currentState.on = true;
  }
  else
  {
    currentState.on = false;
  }

  if (root.containsKey("speed"))
  {
    currentState.speed = root["speed"].as<uint16_t>();
  }

  if (root.containsKey("brightness"))
  {
    currentState.brightness = root["brightness"].as<uint8_t>();
  }

  if (root.containsKey("effect"))
  {
    string effect = root["effect"].as<const char *>();
    if (!effect.empty())
    {
      currentState.effect = effect;
    }
  }

  if (root.containsKey("color"))
  {
    currentState.color.r = root["color"]["r"].as<uint8_t>();
    currentState.color.g = root["color"]["g"].as<uint8_t>();
    currentState.color.b = root["color"]["b"].as<uint8_t>();
  }

  updateState();
}

void announceToHomeAssistant()
{
  Serial.println("MQTT: Annoucing to Home Assistant");

  StaticJsonBuffer<2048> jsonObject;
  JsonObject &discovery = jsonObject.createObject();
  discovery.set("name", HASS_NAME);
  discovery.set("unique_id", WiFi.macAddress());
  discovery.set("platform", "mqtt_json");
  discovery.set("state_topic", MQTT_STATE_TOPIC);
  discovery.set("availability_topic", MQTT_LWT_TOPIC);
  discovery.set("command_topic", MQTT_SET_TOPIC);
  discovery.set("brightness", true);
  discovery.set("rgb", true);
  discovery.set("effect", true);

  // Adds effect list
  JsonArray &effectList = discovery.createNestedArray("effect_list");
  for (std::map<string, void*>::iterator e = effects.begin(); e != effects.end(); ++e)
  {
    effectList.add(e->first.c_str());
  }

  char payload[2048];
  discovery.printTo(payload);
  Serial.println(payload);
  publish("homeassistant/light/ledstrip/config", 2, true, payload);
}

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("--------------------------");
  Serial.println("ESP32 Digital Lights");
  Serial.println("--------------------------");
  Serial.println();
  Serial.println();

  setupNetworking(WIFI_SSID, WIFI_PASSWORD, HOSTNAME);
  setupMqtt(MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD,
            MQTT_STATE_TOPIC, MQTT_LWT_TOPIC, HOSTNAME);
  setupOTA(HOSTNAME, OTA_PORT, OTA_PASSWORD);
  setupLights();
}

void loop()
{
  rainbowBeat();
  showLights();

  // updateState();
  // delay(10000);
}
