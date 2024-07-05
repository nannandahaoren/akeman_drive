// #include <Arduino.h>
// #include "low/TB6612.h"
// #include "low/HallEncoder.h"
// #include <Ticker.h>
// #include <PID_v1.h>
// #include <sstream>

// #include "low/Network.h"
// #include "low/WebSocket.h"
// #include "low/ServoMotor.h"
// #include "low/Wheel.h"
// double l1;
// double l2;
// double l3;
// double l4;


// double caculateServoangle(double angle)
// {
//   double rad = (angle*PI) /180; 
//   double lbd = sqrt(l1*l1 + l4*l4 -2*l1*l4*cos(rad));
//   double ph1 = asin(sin(rad)*l1/lbd);
//   double tem = (lbd*lbd + l3*l3 - l2*l2)/(2*lbd*l3);
//   double ph2 = acos(tem);
//   ph1 = (ph1*180) /PI; 
//   ph2 = (ph2*180) /PI; 
//   double out_th3 = 180 - (ph1 + ph2);
//   return out_th3;

// }