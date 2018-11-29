#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <Ticker.h>
#include <mqtt.h>

void setupNetworking(const char *WIFI_SSID, const char *WIFI_PASSWORD,
                     const char *HOSTNAME);

#endif
