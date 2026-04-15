#include "Robot.h"

void Robot::begin(){
    pwm.begin();
    pwm.setPWMFreq(50);

    //Calibration
    cal.shoulder[0] = {0,false};
    cal.knee[0]     = {0,false};
    cal.shoulder[1] = {0,true};
    cal.knee[1]     = {0,true};
    cal.shoulder[2] = {0,false};
    cal.knee[2]     = {0,false};
    cal.shoulder[3] = {0,true};
    cal.knee[3]     = {0,true};


    //Wheels
    wheelFL.begin(&pwm,0,1);
    wheelFR.begin(&pwm,2,3);
    wheelRL.begin(&pwm,4,5);
    wheelRR.begin(&pwm,6,7);

    //Legs
    frontLeft.begin(&pwm,8,9,&geometry);
    frontRight.begin(&pwm,10,11,&geometry);
    rearLeft.begin(&pwm,12,13,&geometry);
    rearRight.begin(&pwm,14,15,&geometry);

    frontLeft.setCalibration(&cal.shoulder[0], &cal.knee[0]);
    frontRight.setCalibration(&cal.shoulder[1], &cal.knee[1]);
    rearLeft.setCalibration(&cal.shoulder[2], &cal.knee[2]);
    rearRight.setCalibration(&cal.shoulder[3], &cal.knee[3]);
}

void Robot::stand(){
    frontLeft.moveFoot(30,-200);
    frontRight.moveFoot(30,-200);

    rearLeft.moveFoot(-30,-200);
    rearRight.moveFoot(-30,-200);
}

void Robot::drive(int leftSpeed, int rightSpeed){
    wheelFL.setSpeed(leftSpeed);
    wheelRL.setSpeed(leftSpeed);

    wheelFR.setSpeed(rightSpeed);
    wheelRR.setSpeed(rightSpeed);
}

void Robot::debugSetServo(int channel, float angle){
    int pwmVal = map(angle,0,180,102,512);
    pwm.setPWM(channel,0,pwmVal);
}