#include <Arduino.h>
#include "globals.h"
#include "stairs.h"
#include "ir_Remote.h"

/*
 * Управляет всеми ступеньками лестницы
 * from Down - снизу-вверх или сверху-вниз
 * turnOn - включение или выключение
 */
void lightStairs(bool fromDown, bool turnOn)
{
  int startIndex = fromDown ? 0 : nSteps - 1;
  int endIndex = fromDown ? nSteps : -1 ;

  // если включаем по ступенькам
  if (modeByStep)
  {
    while (startIndex != endIndex) // по ступеням
    {
      int firstLed = startIndex * stepLed;
      int lastLed = startIndex * stepLed + stepLed;
      
      e_run(firstLed, lastLed, turnOn);
      delay(STEP_TIME);

      startIndex += fromDown ? 1 : -1;
    }
  }
  else // вся лестницы сразу
  {
    startIndex = 0;
    endIndex = nLed;
    e_run(startIndex, endIndex, turnOn);
  }
}

/*
 * Управляет яркостью всей лестницы
 */
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

/*
 * Управляет датчиками движения
 */
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
      delay(WAIT_TIME);
    }
    else if (digitalRead(motionStart) && state == states::toDown) // .. спустился
    {
      Serial.println("конец - Спустились");
      lightStairs(false, false); // выкл ступеньки N - 0 
      state = states::wait;
      delay(WAIT_TIME);
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


void showApplyStrip()
{
  for (int i=0; i < 2; ++i)
  {
    e_run(0, stepLed, true);
    delay(STEP_TIME / 2);
    e_run(0, stepLed, false);
    delay(STEP_TIME / 2);
  }
}
/*
 * Управляет текущими настройками,
 * которые получает с ИК-пульта
 */
void workRemoteControl()
{
  if (millis() - irTimer < 1000)
  {
    return;
  }

  irTimer = millis();
  Codes code = IR::readCode();

  if (code == Codes::cNone)
    return;
  
  if (code == cPrevEffect)
    setPrevEffect();
  else if (code == cNextEffect)
    setNextEffect();  
  else if (code == cSetModeByStep)
    modeByStep = !modeByStep;
  else if (code == cAnimateAllStair)
  {
    e_greenSnake();
    return;
  }
  else
    curEffect = (effects)code;

  showApplyStrip();
}

void setup() {
  randomSeed(analogRead(1));
  Serial.begin(9600);
  strip.begin();
  recv.enableIRIn();
  e_offAll();
}

void loop() {
  configureBright();
  workSensors();
  workRemoteControl();
}