/*
Sampling.hpp: This file contains a declaration for the sampling_thread function as well as brings in the sensorData and buzz objects.
Author: David Bintley
Student Number: 10855323
*/
#ifndef SAMPLING_HPP
#define SAMPLING_HPP

#include "mbed.h"
#include "uop_msb.h"
#include "SensorData.hpp"
#include "SDCardLog.hpp"

//Include the sensor data
extern SensorData sensorData;
//Include the buzzer
extern Buzzer buzz;

//Functiuon to call in the sampling thread
//Reads SPL06 temp/pressure and LDR light level,
//Then updates the SensorData object using it's API.
void sampling_thread();

#endif