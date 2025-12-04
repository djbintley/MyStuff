/*
LEDBar.cpp: This file contains code for constructiong the LEDBar  as well as code for strobing segments of the bar and setting the bar altogether and by individual segments.
Author: David Bintley
Student Number: 10855323
*/
#include "LEDBar.hpp"

//Constructor
LedBarDisplay::LedBarDisplay(
    PinName d0, PinName d1, PinName d2, PinName d3,
    PinName d4, PinName d5, PinName d6, PinName d7,
    PinName redLE, PinName greenLE, PinName blueLE,
    PinName barOE
) :
    data(d0, d1, d2, d3, d4, d5, d6, d7),
    redLatch(redLE),
    greenLatch(greenLE),
    blueLatch(blueLE),
    enable(barOE)
{
    enable = 0; //Enable bar
}

//Function to Stroba a specific latch with a specific pattern
void LedBarDisplay::latch(DigitalOut &latchPin, uint8_t pattern){
    data = pattern;
    latchPin = 1;
    wait_us(1);
    latchPin = 0;
    wait_us(1);
}

//Function to set a value to the red section of the bar
void LedBarDisplay::setRed(uint8_t pattern){
    latch(redLatch, pattern);
}

//Function to set a value to the Green section of the bar
void LedBarDisplay::setGreen(uint8_t pattern){
    latch(greenLatch, pattern);
}

//Function to set a value to the Blue section of the bar
void LedBarDisplay::setBlue(uint8_t pattern){
    latch(blueLatch, pattern);
}

//Function to set a value to all of the sections of the bar
void LedBarDisplay::setLevel(int level){
    if (level < 0)  level = 0;
    if (level > 24) level = 24;

    //0–7 is Red
    //8–15 is Green
    //16–23 is Blue
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    //Set the level for each section
    if (level <= 8) {
        red = (1 << level) - 1; //fill up to level
    } else {
        red = 0xFF;
        int temp = level - 8;
        if (temp <= 8) {
            green = (1 << temp) - 1;
        } else {
            green = 0xFF;
            temp = temp - 8;
            if (temp <= 8) {
                blue = (1 << temp) - 1;
            } else {
                blue = 0xFF;
            }
        }
    }
    //Strobe the latches to actually change the LEDs
    setRed(red);
    setGreen(green);
    setBlue(blue);
}