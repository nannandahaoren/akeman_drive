#include "ServoMotor.h"

ServoMotor::ServoMotor(int _pinPWM):pinPWM(_pinPWM)
{
}

void ServoMotor::setup(void)
{
  servo.attach(pinPWM, 500, 2500);
  angle = servo.read();
}

void ServoMotor::setAngle(int targetAngle)
{
  if (angle != targetAngle)
  {
    angle = targetAngle;
    servo.write(angle);
  };
}
