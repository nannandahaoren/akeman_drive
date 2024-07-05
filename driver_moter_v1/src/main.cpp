


#include <Arduino.h>
#include "low/TB6612.h"
#include "low/HallEncoder.h"
#include <Ticker.h>
#include <PID_v1.h>
#include <sstream>

#include "low/Network.h"
#include "low/WebSocket.h"
#include "low/ServoMotor.h"
#include "low/Wheel.h"


#define STBY 9

// motorA
#define PWMA 4
#define AIN2 5
#define AIN1 6
#define E1A 7
#define E1B 8

// motorB
#define PWMB 10
#define BIN2 11
#define BIN1 12
#define E2A 13
#define E2B 14

#define SERVO1_PWM 3
#define SERVO2_PWM 15

double T = 0.29; // WheelTrack,轮距
double L = 0.485; // wheelBase，轴距

double l1=8.656;
double l2=8.1;
double l3=4.445;
double l4=7.912;

/*
计算小车最大转向角sigma，对应的最大转向角为Max_sigma；
左车轮最大转向弧度Maxa：0.6，对应角度34度；
MaxR1 = L/tan(Maxa)
MaxR0 = L/tan(Max_sigma)
MaxR0 = MaxR1 + 0.5*T       T为轮距
Max_sigma = atan(L/(MaxR1 + 0.5*T ))

则    - Max_sigma <= sigma  <= Max_sigma
*/

#define interruptTime 10


// put function declarations here:
// int myFunction(int, int);
// Motor motor = Motor(BIN1, BIN2, PWMB, STBY, 2);
// HallEncoder hallEncoder = HallEncoder(E2A, E2B, 1);

Wheel wheelLeft(0, E1A, E1B, AIN1, AIN2, PWMA, STBY);
Wheel wheelRight(1, E2A, E2B, BIN1, BIN2, PWMB, STBY);


Ticker timerReadEncoder;
Network network;
extern WebSocket globalSocket;
std::stringstream resultStr;

int32_t lastSpeed = 0;
float targetSpeed;
float targetAngle;

ServoMotor servo1(SERVO1_PWM);
ServoMotor servo2(SERVO2_PWM);


// 中断服务函数
void ISR()
{
  wheelLeft.handleISR(interruptTime);
  wheelRight.handleISR(interruptTime);
  globalSocket.loop();
}

void receiveMessage(uint8_t *msg)
{
  char *charData = reinterpret_cast<char *>(msg);
  std::string str(charData);

  // 查找逗号的位置
  size_t commaPos = str.find(",");
  targetSpeed = std::stof(str.substr(0, commaPos));
  targetAngle = std::stof(str.substr(commaPos + 1));
  Serial.print("targetSpeed :");
  Serial.println(targetSpeed);
  wheelLeft.isForward = targetSpeed > 0 ? true : false;
  wheelRight.isForward = targetSpeed > 0 ? true : false;
  Serial.print("targetangle :");
  Serial.println(targetAngle);
  double angle1;
  double angle2;
  double leftangle = 0;
  double rightangle = 0;
  double velocity1 = 0;
  double velocity2 = 0;

  if (targetAngle == 0)
  {
    velocity1 = targetSpeed;
    velocity2 = targetSpeed;
  }
  else
  {
    double rad = (targetAngle*PI) /180; 
    double tanangle =  tan(abs(rad));
    double R0 = L/tanangle; // tan（0）=0？？
    double R1 = R0 - 0.5*T;
    double R2 = R0 + 0.5*T;
    angle1 = atan(L/R1);
    angle2 = atan(L/R2);
    angle1 = (angle1*180)/PI;
    angle2 = (angle2*180)/PI;
    velocity1 = abs((targetSpeed/R0)*R1);
    velocity2 = abs((targetSpeed/R0)*R2);
  }
  Serial.print("angle1 :");
  Serial.println(angle1);
  Serial.print("angle2 :");
  Serial.println(angle2);

  if  (targetAngle > 0 )
  {
      leftangle = 39.3418 - angle2;
      rightangle = 180-(39.3418 + angle2);
      wheelLeft.targetSpeed = velocity2;
      wheelRight.targetSpeed = velocity1;
  }
  else if (targetAngle < 0)
  {
      leftangle = 39.3418 + angle2;
      rightangle = 180-(39.3418 - angle2);
      wheelLeft.targetSpeed = velocity1;
      wheelRight.targetSpeed = velocity2;      
  }
  else
  {
      leftangle = 39.3418;
      rightangle = 180 - 39.3418;
      wheelLeft.targetSpeed = targetSpeed;
      wheelRight.targetSpeed = targetSpeed;
  }

  servo1.setAngle(leftangle);
  servo2.setAngle(rightangle);

  Serial.print("leftangle :");
  Serial.println(leftangle);
  Serial.print("rightangle :");
  Serial.println(rightangle);

  Serial.println(wheelLeft.targetSpeed);
  Serial.println(wheelLeft.targetSpeed);
  Serial.print("wheelRight.targetSpeed: ");
  Serial.println(wheelRight.targetSpeed);

  Serial.println("\r\n");
}



void setup()
{
  Serial.begin(115200);
  Serial.println("Hello world from setup function");

  // 伺服电机
  servo1.setup();
  servo1.setAngle(39);
  servo2.setup();
  servo2.setAngle(141);

  // 轮子
  wheelLeft.setup();
  wheelRight.setup();

  //设置中断
  timerReadEncoder.attach_ms(interruptTime, ISR);
  
  // wifi网络
  network.setup();
  Serial.println(network.localIP);
  globalSocket.setup();
  globalSocket.onMessage(receiveMessage);
}



unsigned long previousMillis = 0;
const unsigned long interval = 100;
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    resultStr.str("");
    resultStr << wheelLeft.readSpeed << "," << wheelLeft.targetSpeed;

    std::string result = resultStr.str();
    const char * cstr = result.c_str();
    // Serial.print(cstr);
    globalSocket.sendMessage(cstr);
    previousMillis = currentMillis;
  }

}
