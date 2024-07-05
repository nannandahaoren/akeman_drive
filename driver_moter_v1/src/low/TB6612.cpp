#include "TB6612.h"
// https://github.com/pablopeza/TB6612FNG_ESP32/blob/master/src/TB6612_ESP32.cpp

Motor::Motor(int In1pin, int In2pin, int PWMpin, int STBYpin,uint8_t _pwmChannel)
{
  In1 = In1pin;
  In2 = In2pin;
  PWM = PWMpin;
  Standby = STBYpin;
  pwmChannel = _pwmChannel;

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(Standby, OUTPUT);

  // 频率:5k, 分辨率 2^8 = 255
  ledcSetup(pwmChannel, 5000, 8);
  ledcAttachPin(PWM, pwmChannel);
}

void Motor::drive(int speed)
{
  digitalWrite(Standby, HIGH);
  if (speed >= 0)
  {
    fwd(speed);
  }
  else
  {
    rev(-speed);
  }
}

void Motor::fwd(int speed)
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  ledcWrite(pwmChannel, speed);
}

void Motor::rev(int speed)
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  ledcWrite(pwmChannel, speed);
}

void Motor::brake()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);
  ledcWrite(pwmChannel, 0);
}

void Motor::standby()
{
  digitalWrite(Standby, LOW);
}

void forward(Motor motor1, Motor motor2, int speed)
{
  motor1.drive(speed);
  motor2.drive(speed);
}

void back(Motor motor1, Motor motor2, int speed)
{
  int temp = abs(speed);
  motor1.drive(-temp);
  motor2.drive(-temp);
}

void left(Motor left, Motor right, int speed)
{
  int temp = abs(speed) / 2;
  left.drive(-temp);
  right.drive(temp);
}

void right(Motor left, Motor right, int speed)
{
  int temp = abs(speed) / 2;
  left.drive(temp);
  right.drive(-temp);
}

void brake(Motor motor1, Motor motor2)
{
  motor1.brake();
  motor2.brake();
}
