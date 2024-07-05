#include "HallEncoder.h"

HallEncoder::HallEncoder(int pointA, int pointB, int name) : pointA(pointA), pointB(pointB), name(name) {}

HallEncoder *hallLeft = NULL;
HallEncoder *hallRight = NULL;

void encoderIsrLeft()
{
  if (hallLeft == NULL)
  {
    return;
  }

  if (digitalRead(hallLeft->pointA) == HIGH)
  {
    if (digitalRead(hallLeft->pointB) == LOW)
    {
      hallLeft->plueCounter += 1;
    }
    else
    {
      hallLeft->plueCounter -= -1;
    }
  }
  else
  {
    if (digitalRead(hallLeft->pointB) == HIGH)
    {
      hallLeft->plueCounter += +1;
    }
    else
    {
      hallLeft->plueCounter -= -1;
    }
  }
}

void encoderIsrRight()
{
  if (hallRight == NULL)
  {
    return;
  }

  if (digitalRead(hallRight->pointA) == HIGH)
  {
    if (digitalRead(hallRight->pointB) == LOW)
    {
      hallRight->plueCounter += 1;
    }
    else
    {
      hallRight->plueCounter -= -1;
    }
  }
  else
  {
    if (digitalRead(hallRight->pointB) == HIGH)
    {
      hallRight->plueCounter += +1;
    }
    else
    {
      hallRight->plueCounter -= -1;
    }
  }
}

void HallEncoder::init()
{
  pinMode(pointA, INPUT);
  pinMode(pointB, INPUT);

  if (name == 0)
  {
    hallLeft = this;
    attachInterrupt(digitalPinToInterrupt(pointA), encoderIsrLeft, CHANGE);
  }
  else if (name == 1)
  {
    hallRight = this;
    attachInterrupt(digitalPinToInterrupt(pointA), encoderIsrRight, CHANGE);
  }
}

// 13线, 减速比30, AB两相
// 设计转速: 290 +-20
float HallEncoder::getSpeed(int interruptTimeMs)
{
  if (plueCounter == 0)
  {
    return 0.0;
  }

  // 每毫秒的脉冲数
  float a = (float)interruptTimeMs / (float)plueCounter;
  plueCounter = 0;

  // 1s 的脉冲数
  float b = 1000.0 / a;
  // 1分钟的圈数
  return b / (13.0 * 30 * 2) * 60.0;
}
