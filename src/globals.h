#pragma once
#include "Adafruit_NeoPixel.h"

#define brightPin A0

constexpr bool bIsAutoBright = true;

constexpr int motionStart = 2;
constexpr int motionEnd = 3;
static unsigned long stairTimer = 0;
constexpr int waitTimeout = 15 * 1000;

constexpr int nLed = 30;
constexpr int8_t pinLed = 12;
constexpr int nSteps = 5;
constexpr int stepLed = 6;

Adafruit_NeoPixel strip(nLed, pinLed, NEO_GRB + NEO_KHZ800);

enum states
{
    toUp = 0,
    toDown = 1,
    wait = 2
};
static states state = states::wait;

enum effects
{
    white = 0,
    red,
    green,
    blue,
    yellow,
    puprle,
    rainbow,
    randomize,
    // ...
    effects_count
};

static effects curEffect = effects::randomize;

uint32_t colorCodes[7] =
{
    0xff0000, 0xff9900, 0xffff00,  0x00ff00, 
    0x00ffff, 0x0000ff, 0xff00ff
};

enum Colors : uint32_t
{
    Red = 0xff0000,
    Orange = 0xff7700, 
    Yellow = 0xffff00, 
    Green = 0x00ff00, 
    Cyan = 0x00ffff, 
    Blue = 0x0000ff, 
    Purple = 0xff00ff,
    White = 0xffffff
};