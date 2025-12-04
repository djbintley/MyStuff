/*
Main.cpp: This File initialises all of the threads as well as the data and LED Bar objects.
Author: David Bintley
Student Number: 10855323
*/
#include "mbed.h"
#include "uop_msb.h"
#include "Sampling.hpp"
#include "SDCardLog.hpp"
#include "SensorData.hpp"
#include "Serial.hpp"
#include "LEDBar.hpp"

//Initialise Sensor Data object
SensorData sensorData;
//Initialise LED bar
LedBarDisplay ledBar(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN, LED_RED_LE_PIN,      LED_GRN_LE_PIN,  LED_BLUE_LE_PIN,   LED_BAR_OE_PIN      );

//Threads
Thread SensorThread;
Thread SDThread(osPriorityNormal,12288); //12kB to handle the large strings
Thread SerialThread;

int main()
{   
    //Start Threads
    SensorThread.start(callback(sampling_thread));
    SDThread.start(callback(SDCard_thread));
    SerialThread.start(callback(serial_thread));

    //Set Thread Priorities, sensors highest and serial lowest
    SensorThread.set_priority(osPriorityHigh);
    //SDThread.set_priority(osPriorityNormal);
    SerialThread.set_priority(osPriorityLow);
    
    printf("\n\nStarting...\n");
    while (true) {
        ThisThread::sleep_for(1s);
    }
}
