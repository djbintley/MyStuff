#ifndef LEG_H
#define LEG_H

#include <Adafruit_PWMServoDriver.h>
#include "Geometry.h"
#include "Calibration.h"

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

    void setCalibration(ServoCal* shoulderCal, ServoCal* kneeCal);

private:

    Adafruit_PWMServoDriver* _pwm;

    int shoulderServo;
    int kneeServo;

    RobotGeometry* geometry;

    float L1;
    float L2;

    bool isLeft;

    int angleToPWM(float angle);

    ServoCal* shoulderCal;
    ServoCal* kneeCal;
};

#endif