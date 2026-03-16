#ifndef ROBOT_H
#define ROBOT_H

#include <Adafruit_PWMServoDriver.h>
#include "Leg.h"
#include "Wheel.h"
#include "Geometry.h"

class Robot
{
public:

    void begin();

    void stand();

    void drive(int leftSpeed, int rightSpeed);

private:

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

    RobotGeometry geometry;

    Leg frontLeft;
    Leg frontRight;
    Leg rearLeft;
    Leg rearRight;

    Wheel wheelFL;
    Wheel wheelFR;
    Wheel wheelRL;
    Wheel wheelRR;
};

#endif