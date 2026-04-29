#ifndef GAIT_H
#define GAIT_H

class Gait
{
public:

    float stepLength = 40;
    float stepHeight = 60;
    float cycleTime  = 4000; // ms

    float getPhase(unsigned long time, float offset);

    void getFootPosition(float phase, float& x, float& y);
};

#endif