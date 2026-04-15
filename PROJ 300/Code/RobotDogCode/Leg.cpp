#include "Leg.h"
#include <math.h>

void Leg::begin(Adafruit_PWMServoDriver* pwm,
                int shoulderChannel,
                int kneeChannel,
                RobotGeometry* geo)
{
    _pwm = pwm;

    shoulderServo = shoulderChannel;
    kneeServo = kneeChannel;

    geometry = geo;

    L1 = geometry->upperLeg;
    L2 = geometry->lowerLeg;
}

int Leg::angleToPWM(float angle)
{
    int pulse = map(angle,0,180,102,512);
    return pulse;
}

void Leg::setAngles(float shoulder, float knee)
{
    // Apply calibration
    if(shoulderCal->invert) shoulder = 180 - shoulder;
    if(kneeCal->invert) knee = 180 - knee;

    shoulder += shoulderCal->offset;
    knee += kneeCal->offset;

    shoulder = constrain(shoulder, 0, 180);
    knee  = constrain(knee, 0, 180);

    _pwm->setPWM(shoulderServo,0,angleToPWM(shoulder));
    _pwm->setPWM(kneeServo,0,angleToPWM(knee));
}

void Leg::moveFoot(float x, float y)
{
    float d = sqrt(x*x + y*y);

    float knee =
        acos((L1*L1 + L2*L2 - d*d) / (2*L1*L2));

    if (y < 0 && x < 0){
        float shoulder =
            atan2(y,x) -
            acos((d*d + L1*L1 - L2*L2)/(2*L1*d));
    } else if (y < 0 && x > 0){ 
        float shoulder =
            180 +
            atan2(y,x) -
            acos((d*d + L1*L1 - L2*L2)/(2*L1*d));
    } else if (y > 0 && x > 0){ 
        float shoulder =
            270 -
            atan2(x,y) -
            acos((d*d + L1*L1 - L2*L2)/(2*L1*d));
    }

    knee = degrees(knee);
    shoulder = degrees(shoulder);

    setAngles(shoulder,knee);
}

void Leg::setCalibration(ServoCal* sCal, ServoCal* kCal)
{
    shoulderCal = sCal;
    kneeCal = kCal;
}