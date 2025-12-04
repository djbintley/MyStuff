/*
SDCardLog.hpp: This file contains headers for the SDCard_thread and sd_push_sample functions as well as bringing in the sensorData object
Author: David Bintley
Student Number: 10855323
*/
#ifndef SDCardLog_HPP
#define SDCardLog_HPP

#include "mbed.h"
#include "SensorData.hpp"
#include <cstring>      
#include <cstdio>

extern SensorData sensorData;

//Function to repeatedly call in the SD Card thread
void SDCard_thread();

//Function called by the sampling thread to push a sample into the SD buffer
void sd_push_sample(float temperature, float pressure, float light);
#endif