#pragma once

#include "IRremote.h"
#include "globals.h"

IRrecv recv(IR_PIN);
decode_results res;

namespace IR
{
    Codes readCode()
    {
        if (state != states::wait)
            return cNone;

        if (!recv.decode())
            return cNone;
        
        uint16_t value = recv.decodedIRData.command;
        recv.resume();
        
        switch (value)
        {
        case 25: // 0
        {
            return cWhite;
        }
        case 69: // 1
        {
            return cRed;
        }
        case 70: // 2
        {
            return cOrange;
        }
        case 71: // 3
        {
            return cYellow;
        }
        case 68: // 4
        {
            return cGreen;
        }
        case 64: // 5
        {
            return cCyan;
        }
        case 67: // 6
        {
            return cBlue;
        }
        case 7: // 7
        {
            return cPurple;
        }
        case 21: // 8
        {
            return cRainbow;
        }
        case 9: // 9
        {
            return cRandom;
        }
        case 22: // *
        {
            return cNone;
        }
        case 13: // #
        {
            return cNone;
        }
        case 24: // вверх
        {
            return cBrightnessUp;
        }
        case 8: // влево
        {
            return cPrevEffect;
        }
        case 82: // вниз
        {
            return cBrightnessDown;
        }
        case 90: // вправо
        {
            return cNextEffect;
        }
        case 28: // ок
        {
            return cNone;
        }
        
        default:
            return cNone;
        }
    }
}