#ifndef LEG_H
#define LEG_H

#include <Adafruit_PWMServoDriver.h>
#include "Geometry.h"

class Leg
{
public:

    Leg(){}

    void begin(Adafruit_PWMServoDriver* pwm,
               int shoulderChannel,
               int kneeChannel,
               RobotGeometry* geo);

    void setAngles(float shoulder, float knee);

    void moveFoot(float x, float y);

private:

    Adafruit_PWMServoDriver* _pwm;

    int shoulderServo;
    int kneeServo;

    RobotGeometry* geometry;

    float L1;
    float L2;

    int angleToPWM(float angle);
};

#endif