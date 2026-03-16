#include "Robot.h"

void Robot::begin()
{
    pwm.begin();
    pwm.setPWMFreq(50);

    // wheels
    wheelFL.begin(&pwm,0,1);
    wheelFR.begin(&pwm,2,3);
    wheelRL.begin(&pwm,4,5);
    wheelRR.begin(&pwm,6,7);

    // legs
    frontLeft.begin(&pwm,8,9,&geometry);
    frontRight.begin(&pwm,10,11,&geometry);
    rearLeft.begin(&pwm,12,13,&geometry);
    rearRight.begin(&pwm,14,15,&geometry);
}

void Robot::stand()
{
    frontLeft.moveFoot(30,-200);
    frontRight.moveFoot(30,-200);

    rearLeft.moveFoot(-30,-200);
    rearRight.moveFoot(-30,-200);
}

void Robot::drive(int leftSpeed, int rightSpeed)
{
    wheelFL.setSpeed(leftSpeed);
    wheelRL.setSpeed(leftSpeed);

    wheelFR.setSpeed(rightSpeed);
    wheelRR.setSpeed(rightSpeed);
}