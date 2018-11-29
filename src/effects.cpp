#include <effects.h>

using namespace std;

struct CRGB lights[LED_COUNT];
struct CRGB color;

void setupLights()
{
  LEDS.addLeds<LIGHT_TYPE, LIGHT_PIN, LIGHT_ORDER>(lights, LED_COUNT);
  FastLED.setBrightness(100);
  set_max_power_in_volts_and_milliamps(5, 500);
}

void showLights() { FastLED.show(); }

void solid() { fill_solid(lights, LED_COUNT, color); }

void rainbowBeat()
{
  uint8_t beatA = beatsin8(17, 0, 255); // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(lights, LED_COUNT, (beatA + beatB) / 2, 8); // Use FastLED's fill_rainbow routine.
}
