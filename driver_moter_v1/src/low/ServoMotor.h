#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H
#include <ESP32Servo.h>

// 伺服舵机
class ServoMotor
{
public:
  ServoMotor(int pinPWM);
  void setup(void);
  void setAngle(int targetAngle);
  int angle;

private:
  Servo servo;
  int pinPWM;
};

#endif
