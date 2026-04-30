#include "Wheel.h"

void Wheel::begin(Adafruit_PWMServoDriver* pwm, int chA, int chB)
{
    _pwm = pwm;
    channelA = chA;
    channelB = chB;
}

void Wheel::setSpeed(int speed)
{
    speed = constrain(speed, -255, 255);

    int pwm = map(abs(speed),0,255,0,4095);

    if(speed > 0)
    {
        _pwm->setPWM(channelA,0,pwm);
        _pwm->setPWM(channelB,0,0);
    }
    else if(speed < 0)
    {
        _pwm->setPWM(channelA,0,0);
        _pwm->setPWM(channelB,0,pwm);
    }
    else
    {
        _pwm->setPWM(channelA,0,0);
        _pwm->setPWM(channelB,0,0);
    }
}