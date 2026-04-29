#include "Gait.h"
#include <Arduino.h>

float Gait::getPhase(unsigned long time, float offset)
{
    float t = fmod(time, cycleTime) / cycleTime;
    t += offset;

    if(t > 1.0) t -= 1.0;

    return t;
}

void Gait::getFootPosition(float phase, float& x, float& y)
{
    if(phase < 0.75)
    {
        // stance phase
        x = stepLength * (0.5 - phase);
        y = -200;
    }
    else
    {
        // swing phase
        float t = (phase - 0.75) / 0.25;

        x = -stepLength/2 + t * stepLength;
        y = -200 + stepHeight * sin(t * PI);
    }
}