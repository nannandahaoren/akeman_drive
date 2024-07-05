#ifndef HALL_ENCODER_H
#define HALL_ENCODER_H

#include <Arduino.h>

// 霍尔磁编码器
class HallEncoder
{
public:
    int pointA;
    int pointB;

    HallEncoder(int pointA, int pointB, int name);

    void init();
    float getSpeed(int);

    // 0: left, 1: right;
    int name;
    // 脉冲计数
    int32_t plueCounter = 0;
};

#endif
