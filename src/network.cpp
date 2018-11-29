#include <network.h>

using namespace std;

const char *ssid;
const char *pass;

Ticker wifiReconnectTimer;
Ticker mqttReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  if (WiFi.status() != WL_CONNECTED)
    WiFi.begin(ssid, pass);
}

void onWiFiEvent(WiFiEvent_t event)
{
  switch (event)
  {
  case SYSTEM_EVENT_STA_START:
    Serial.println("WIFI: Connecting...");
    break;
  case SYSTEM_EVENT_STA_CONNECTED:
    Serial.println("WIFI: Connected! Waiting for IP...");
    break;
  case SYSTEM_EVENT_STA_LOST_IP:
    Serial.println("WIFI: Lost IP address...");
    break;
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("WIFI: Got IP!");
    Serial.print("WIFI: IP Address: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("WIFI: Disconnected.");
    mqttReconnectTimer.detach();
    wifiReconnectTimer.once(2, connectToWifi);
    break;
  default:
    break;
  }
}

// void onWifiConnect(const WiFiEventStationModeGotIP &event)
// {
//   Serial.println("Connected to Wi-Fi.");
//   connectToMqtt();
// }

// void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
// {
//   Serial.println("Disconnected from Wi-Fi.");
//   mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
//   wifiReconnectTimer.once(2, connectToWifi);
// }

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
    mqttReconnectTimer.once(2, connectToMqtt);
}

void setupNetworking(const char *WIFI_SSID, const char *WIFI_PASSWORD,
                     const char *HOSTNAME)
{
  ssid = WIFI_SSID;
  pass = WIFI_PASSWORD;

  // Register event handling
  WiFi.onEvent(onWiFiEvent);

  WiFi.setHostname(HOSTNAME);
  connectToWifi();
}
