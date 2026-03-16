#ifndef WHEEL_H
#define WHEEL_H

#include <Adafruit_PWMServoDriver.h>

class Wheel
{
public:

    Wheel(){}

    void begin(Adafruit_PWMServoDriver* pwm, int chA, int chB);

    void setSpeed(int speed);

private:

    Adafruit_PWMServoDriver* _pwm;

    int channelA;
    int channelB;
};

#endif