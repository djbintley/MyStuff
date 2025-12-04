/*
Sampling.cpp: This file contains code for that runs in the sensor thread. It reads the SPL06-001 and LDR and updates the sensorData object using it's threadsafe API
It also checks to see if the value are outside of the thresholds and if so sounds the alarm.
Author: David Bintley
Student Number: 10855323
*/
#include "Sampling.hpp"

//Alarm Threshhold values
static const float TEMP_HIGH = 22.0f; 
static const float TEMP_LOW = 18.0f; 
static const float PRESS_HIGH = 1000.0f;
static const float PRESS_LOW = 985.0f;
static const float LIGHT_LOW = 50000.0f;
static const float LIGHT_High = 4000.0f;


//Function to get called repeatedly in the Sampling Thread
void sampling_thread()
{
    while (true) {
        //Get Data from SPL06-001
        float temp = env.getTemperature();
        float press = env.getPressure();
        
        //Get light level from LDR
        float light = ldr.read_u16();

        //Set the new sensor data using the API
        sensorData.set(temp, press, light);

        //Push to SD Card buffer
        sd_push_sample(temp, press, light);

        //Check for alarms
        bool alarm = false;
        if (temp > TEMP_HIGH) {
            alarm = true;
            printf("ALARM! High Temperature (%.2fC)\n", temp);
        }else if (temp < TEMP_LOW) {
            alarm = true;
            printf("ALARM! Low Temperature (%.2fC)\n", temp);
        }else if (press > PRESS_HIGH) {
            alarm = true;
            printf("ALARM! High Pressure (%.2f mbar)\r\n", press);
        }else if (press < PRESS_LOW) {
            alarm = true;
            printf("ALARM! Low Pressure (%.2f mbar)\r\n", press);
        }else if (light > LIGHT_LOW) {
            alarm = true;
            printf("ALARM! Low Light Level (%.0f)\r\n", light);
        }else if (light < LIGHT_High) {
            alarm = true;
            printf("ALARM! High Light Level (%.0f)\r\n", light);
        }


        //Sound the buzzer if there is an alarm
        if (alarm) {
            buzz.playTone("C");
            ThisThread::sleep_for(200ms); //Sleep while buzz is playing   
            buzz.rest();
        }
        
        // 1 Hz sampling to match the sensor thread
        ThisThread::sleep_for(1s); 
    }
}