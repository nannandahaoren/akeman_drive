#include "Wheel.h"

Wheel::Wheel(int name, int pinA, int pinB, int pinIn1, int pinIn2, int pinPWM, int pinStby) : encoder(pinA, pinB, name), name(name)
{

  uint8_t pwmChannel;
  if (name == 0)
  {
    pwmChannel = 2;
  }
  else if (name == 1)
  {
    pwmChannel = 3;
  }
  motor = new Motor(pinIn1, pinIn2, pinPWM, pinStby, pwmChannel);
  pid = new PID(&readSpeed, &output, &targetSpeed, Kp, Ki, Kd, DIRECT);
  // Serial.println("motor init success");
}

Wheel::~Wheel()
{
  delete pid;
  delete motor;
}

float Wheel::getSpeed(void)
{
  return readSpeed;
}

void Wheel::handleISR(int interruptTime)
{
  readSpeed = (int32_t)encoder.getSpeed(interruptTime);
  bool ret = pid->Compute();
  if (ret)
  {
    double finalOutput;
    if (isForward == false)
    {
      finalOutput = output * -1;
    }
    else
    {
      finalOutput = output;
    }

    // 如果目标速度是0, 那么方向保持和上次一致
    if (targetSpeed == 0.)
    {
      finalOutput = abs(output) * lastOutput > 0 ? 1 : -1;
    }

    if (name == 0)
    {
      lastOutput = -1*finalOutput;
    }
    else
    {
      lastOutput = -1*finalOutput;
    }
    motor->drive(lastOutput);
  }
}

void Wheel::setup()
{
  encoder.init();
  pid->SetMode(AUTOMATIC);
  motor->drive(0);
}
