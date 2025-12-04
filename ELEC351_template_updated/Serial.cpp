/*
Serial.cpp: This file contains code that runs the serial thread. It uses the SensorData API to read the sensor values and then transmits them via the serial link.
It also sets the led bar to represent the value selected by the user via the serial input
Author: David Bintley
Student Number: 10855323
*/
#include "Serial.hpp"

//Set default display mode
static char selectedMode = 'L';   // T = temperature, P = pressure, L = light

//From Task 245
static BufferedSerial pc(USBTX, USBRX, 115200); 

//reads a character if available
static bool read_char(char &c) {
    if (pc.readable()) {
        pc.read(&c, 1);
        return true;
    }
    return false;
}

//Thread function
void serial_thread() {
    //Initialise temporary variables
    float t = 0.0f;
    float p = 0.0f;
    float l = 0.0f;
    char rx = 0;

    while (true) {
        //Read sensor data
        sensorData.get(t, p, l);

        //Print values
        printf("T = %.2f C,  P = %.2f mbar,  L = %.0f\n", t, p, l);

        //Check for incoming data
        if (read_char(rx)) {
            if (rx == 'T' || rx == 'P' || rx == 'L') {
                selectedMode = rx;
                printf("LED Bar now displaying: '%c'\n", selectedMode);
            }else{
            printf("Invalid Character Input\n");
            }
        }

        //Update LED Bar
        switch (selectedMode) {
            case 'T':
                ledBar.setLevel((int)t); 
                break;
            case 'P':
                //Scaled to the scale of the led bar
                ledBar.setLevel((int)((p -1000)+12));   
                break;
                //Scaled and flipped so the bar rises with light
            case 'L':
                ledBar.setLevel((int)(24-(l/2730))); 
                break;
        }
        //Need to sleep while data values are not being read
        ThisThread::sleep_for(1s);
    }
}