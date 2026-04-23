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


    Serial.print("Final Shoulder: ");
    Serial.println(shoulder);
    Serial.println();
}

void Leg::moveFoot(float x, float y)
{
    float d = sqrt(x*x + y*y);

    if(d > L1 + L2)
    {
        // too far
        d = L1 + L2;
    }
    // Prevent invalid domain for acos
    d = constrain(d, 1, L1 + L2 - 1);

    float cosKnee = (L1*L1 + L2*L2 - d*d) / (2*L1*L2);
    cosKnee = constrain(cosKnee, -1, 1);

    float knee = acos(cosKnee);

    float cosShoulder = (d*d + L1*L1 - L2*L2) / (2*L1*d);
    cosShoulder = constrain(cosShoulder, -1, 1);

    float shoulder =
        atan2(y, x) +
        acos(cosShoulder);

    // Convert to degrees
    knee = degrees(knee);
    shoulder = degrees(shoulder);

    shoulder += 90;

    Serial.print("X: "); Serial.print(x);
    Serial.print(" Y: "); Serial.println(y);

    Serial.print("Shoulder: "); Serial.println(shoulder);
    Serial.print("Knee: "); Serial.println(knee);

    setAngles(shoulder, knee);
}

void Leg::setCalibration(ServoCal* sCal, ServoCal* kCal)
{
    shoulderCal = sCal;
    kneeCal = kCal;
}