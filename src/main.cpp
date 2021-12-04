#include <Arduino.h>
#include "globals.h"
#include "stairs.h"

void lightStairs(bool fromDown, bool turnOn)
{
  int startIndex = fromDown ? 0 : nSteps - 1;
  int endIndex = fromDown ? nSteps : -1 ;

  while (startIndex != endIndex) // по ступеням
  {
    int firstLed = startIndex * stepLed;
    int lastLed = startIndex * stepLed + stepLed;
    
    e_run(firstLed, lastLed, turnOn);
    delay(300);

    startIndex += fromDown ? 1 : -1;
  }

  if (turnOn)
  {
    //setNextEffect(); // смена эффекта
  }
}

void configureBright()
{
  if (!bIsAutoBright)
    return;

  if (state == states::wait)
    return;

  int _bright = analogRead(brightPin);
  int _mappedBright = 210 - map(_bright, 30, 800, 10, 200);
  strip.setBrightness(_mappedBright);
  strip.show();
}

void workSensors()
{
  // на лестнице кто то есть
  if (state != states::wait)
  {
    if (digitalRead(motionEnd) && state == states::toUp)  // .. поднялся
    {
      Serial.println("конец - Поднялись");
      lightStairs(true, false); // выкл ступеньки 0 - N
      state = states::wait;
      delay(1000);
    }
    else if (digitalRead(motionStart) && state == states::toDown) // .. спустился
    {
      Serial.println("конец - Спустились");
      lightStairs(false, false); // выкл ступеньки N - 0 
      state = states::wait;
      delay(1000);
    }
  }

  // на лестницу зашли..
  if (digitalRead(motionStart)) // .. и поднимаются
  {
    Serial.println("начало - Поднимаются");
    lightStairs(true, true); // вкл ступеньки 0 - N
    state = states::toUp;
    stairTimer = millis();
  }
  else if (digitalRead(motionEnd)) // .. и спускаются
  {
    Serial.println("начало - Спускаются");
    lightStairs(false,true);// вкл ступеньки N - 0
    state = states::toDown;
    stairTimer = millis();
  }

  if (state != states::wait && abs(millis() - stairTimer) > waitTimeout)
  {
    stairTimer = millis();
    state = states::wait;
    Serial.println("Потерял человека. Иду спать.");
    e_fadeAll();
  }
}

void setup() {
  randomSeed(analogRead(1));
  Serial.begin(9600);
  strip.begin();
  e_offAll();
}

void loop() {
  configureBright();
  workSensors();
  delay(100);
}