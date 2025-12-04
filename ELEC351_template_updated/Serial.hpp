/*
Serial.hpp: This file contains a header for the serial thread function as well as bringing in the SensorData object and the Ledbar object.
Author: David Bintley
Student Number: 10855323
*/
#ifndef Serial_HPP
#define Serial_HPP

#include "mbed.h"
#include "SensorData.hpp"
#include "LEDBar.hpp"
#include "Sampling.hpp"

//Bring in the data object and LED bar object
extern SensorData sensorData;
extern LedBarDisplay ledBar;

//Function that handles serial communication
void serial_thread();

#endif