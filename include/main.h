#ifndef MAIN_H
#define MAIN_H

using namespace std;

#include <map>
#include <string>
#include <ArduinoJson.h>
#include <network.h>
#include <mqtt.h>
#include <ota.h>
#include <effects.h>
#include <setup.h>

std::map<string, void *> effects = {
  {"solid", (void *)solid},
  {"rainbow beat", (void *)rainbowBeat}
};

struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct State
{
  Color color = {255, 255, 255};
  uint8_t brightness = 100;
  string effect = "static";
  uint16_t speed = 1000;
  bool on = true;
};

State currentState;

#endif
