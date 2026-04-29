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
d
8  - Front Left Shoulder - Second from bottom left - invert + 10 degrees
9  - Front Left Knee - Third from bottom right +3

10 - Front Right Shoulder - Second from bottom right    
11 - Front Right Knee   - Bottom right - invert (5)

12 - Rear Left Shoulder    -  (+5)
13 - Rear Left Knee

14 - Rear Right Shoulder - Invert (-5)
15 - Rear Right Knee - Invert 
*/

Robot robot;

void setup(){
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.begin(115200);
    robot.begin();
    delay(2000);
    Serial.println();
    Serial.println();
    Serial.println("Good Morning");
    robot.drive(0,0);
    robot.stand();
    //robot.crouch();
}

void loop(){
    robot.drive(255,255);
    delay(5000);
    robot.drive(0,0);
    delay(5000);
    //robot.walk();
    //robot.drive(0,0);
    //calibrationMode();
    //PositionMode();
}

int x = 30;
int y = -200;

void PositionMode(){
    if(Serial.available()){
        char c = Serial.read();
        
        if(c == 'w') {
            for(int i = 0; i <5; i++){
            y+=1;
            robot.SetPos(x, y);
            delay(50);
            }
        }

        if(c == 's') {
            for(int i = 0; i <5; i++){
            y-=1;
            robot.SetPos(x, y);
            delay(50);
            }
        }

        if(c == 'd') {
            for(int i = 0; i <5; i++){
            x-=1;
            robot.SetPos(x, y);
            delay(50);
            }
        }
        if(c == 'a') {
            for(int i = 0; i <5; i++){
            x+=1;
            robot.SetPos(x, y);
            delay(50);
            }
        }

        Serial.print("X: ");
        Serial.print(x);
        Serial.print(", Y: ");
        Serial.println(y);
    }
}

int currentServo = 8;  //Start at first servo
int angle = 90;

void calibrationMode(){
    if(Serial.available()){
            char c = Serial.read();
            if (c == ' '){
            }else{
            if(c == 'n') currentServo++;
            if(c == 'p') currentServo--;

            if(c == 'u') angle += 5;
            if(c == 'd') angle -= 5;

            angle = constrain(angle,0,180);
            currentServo = constrain(currentServo,8,15);

            Serial.print("Servo: ");
            Serial.print(currentServo);
            Serial.print(" Angle: ");
            Serial.println(angle);

            robot.debugSetServo(currentServo, angle);
        }
    }
}
