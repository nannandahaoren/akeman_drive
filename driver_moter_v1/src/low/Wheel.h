#ifndef Wheel_H
#define Wheel_H

#include <Arduino.h>
#include "ESP32Servo.h"
#include "PID_v1.h"

#include "TB6612.h"
#include "HallEncoder.h"

class Wheel
{
public:
  Wheel(int name, int pinA, int pinB, int pinIn1, int pinIn2, int pinPWM, int pinStby);
  ~Wheel();

  void setup();
  float getSpeed(void);
  void handleISR(int interruptTime);

  double targetSpeed = 0.0;
  double readSpeed;
  bool isForward = true;

private:
  double Kp = 0.2, Ki = 0.8, Kd = 0.;
  double output;
  double lastOutput;

  int name;
  PID * pid;
  Motor * motor;
  HallEncoder encoder;
};

#endif
