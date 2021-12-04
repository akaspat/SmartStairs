#pragma once
#include "globals.h"

// эффект включения цвета
// from, to - номера диода на ленте
void e_colorize(int from, int to, uint32_t color)
{
  for (int i = from; i < to; ++i)
    strip.setPixelColor(i, color);
  
  strip.show();
}

// плавное угасание
void e_fadeAll()
{
    int prevValue = strip.getBrightness();

    while (strip.getBrightness() > 0)
    {
        int _br = strip.getBrightness() - 10;
        _br = _br < 0 ? 0 : _br;
        strip.setBrightness(_br);
        delay(100);
        strip.show();
    }
    strip.setBrightness(prevValue);
}

// выключить все
void e_offAll()
{
    uint32_t c = Adafruit_NeoPixel::Color(0,0,0);
    for (int i = 0; i < nLed; ++i)
    {
        strip.setPixelColor(i, c);
    }
    strip.show();
}

// включить все
void e_onAll(uint32_t color)
{
    for (int i = 0; i < nLed; ++i)
    {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

void setNextEffect() 
{
    curEffect = effects(curEffect + 1);
    if (curEffect == effects_count)
        curEffect = white;
}

void setPrevEffect() 
{
    curEffect = effects(curEffect - 1);
    if (curEffect == white - 1)
        curEffect = (effects)(effects_count - 1);
}

// запускает установленный эффект
void e_run(int from, int to, bool turnOn)
{
    // выключаем по ступенькам
    if (!turnOn)
    {
        e_colorize(from, to, Adafruit_NeoPixel::Color(0, 0, 0));
        return;
    }

    // включаем по ступенькам
    switch (curEffect)
    {
    case effects::white:
        e_colorize(from, to, uint32_t(Colors::White));
        break;
    case effects::red:
        e_colorize(from, to, uint32_t(Colors::Red));
        break;
    case effects::orange:
        e_colorize(from, to, uint32_t(Colors::Orange));
        break;
    case effects::yellow:
        e_colorize(from, to, uint32_t(Colors::Yellow));
        break;
    case effects::green:
        e_colorize(from, to, uint32_t(Colors::Green));
        break;
    case effects::cyan:
        e_colorize(from, to, uint32_t(Colors::Cyan));
        break;
    case effects::blue:
        e_colorize(from, to, uint32_t(Colors::Blue));
        break;
    case effects::puprle:
        e_colorize(from, to, uint32_t(Colors::Purple));
        break;
    case effects::rainbow:
    {
        e_colorize(from, to, colorCodes[from / nSteps]);
        break;
    }
    case effects::randomize:
    {
        int index = random(7);
        //int r = random(255); int g = random(255); int b = random(255);
        e_colorize(from, to, colorCodes[index]);
        break;
    }
    default:
        curEffect = effects::white;
    }
}