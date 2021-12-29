#pragma once
#include "Adafruit_NeoPixel.h"

#define brightPin A0
#define WAIT_TIME 1500 // время которое ждем после срабатывания выключения
#define STEP_TIME 1000 // скорость анимации следующей ступеньки
#define SNAKE_SPEED 100 // передвижений змеи на 1 светодиод
#define IR_PIN 9

constexpr bool bIsAutoBright = true;

constexpr int motionStart = 2;
constexpr int motionEnd = 3;
static unsigned long stairTimer = 0;
static unsigned long irTimer = 0;
constexpr int waitTimeout = 15 * 1000;

constexpr int nLed = 30;
constexpr int8_t pinLed = 12;
constexpr int nSteps = 5;
constexpr int stepLed = 6;

Adafruit_NeoPixel strip(1800, pinLed, NEO_GRB + NEO_KHZ800);

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
    orange,
    yellow,
    green,
    cyan,
    blue,
    puprle,
    rainbow,
    randomize,
    // ...
    effects_count
};

enum Codes
{
    cWhite,
    cRed,
    cOrange,
    cYellow,
    cGreen,
    cCyan,
    cBlue,
    cPurple,
    cRainbow,
    cRandom,
    cPrevEffect,
    cNextEffect,
    cSetModeByStep,
    cAnimateAllStair,
    cNone
};

static effects curEffect = effects::randomize;
enum Colors : uint32_t
{
    Red = 0xff0000,
    Orange = 0xff9900, 
    Yellow = 0xffff00, 
    Green = 0x00ff00, 
    Cyan = 0x00ffff, 
    Blue = 0x0000ff, 
    Purple = 0xff00ff,
    White = 0xffffff
};

uint32_t colorCodes[7] =
{
    Colors::Red, Colors::Orange, Colors::Yellow,  Colors::Green, 
    Colors::Cyan, Colors::Blue, Colors::Purple
};

bool modeByStep = true;