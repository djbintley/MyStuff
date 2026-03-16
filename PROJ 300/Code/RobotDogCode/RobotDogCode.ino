#include "Robot.h"
/*
PWM Breakout Channels

0  - Front Left Wheel A
1  - Front Left Wheel B

2  - Front Right Wheel A
3  - Front Right Wheel B

4  - Rear Left Wheel A
5  - Rear Left Wheel B

6  - Rear Right Wheel A
7  - Rear Right Wheel B

8  - Front Left Shoulder
9  - Front Left Knee

10 - Front Right Shoulder
11 - Front Right Knee

12 - Rear Left Shoulder
13 - Rear Left Knee

14 - Rear Right Shoulder
15 - Rear Right Knee
*/

Robot robot;

void setup()
{
    Serial.begin(115200);

    robot.begin();

    delay(2000);

    robot.stand();
}

void loop()
{
    robot.drive(120,120);

    delay(3000);

    robot.drive(0,0);

    delay(3000);
}