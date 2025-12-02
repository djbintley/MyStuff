#ifndef SAMPLING_HPP
#define SAMPLING_HPP

#include "mbed.h"
#include "uop_msb.h"
#include "SensorData.hpp"

//Include the sensor data
extern SensorData sensorData;

//Functiuon to call in the sampling thread
//Reads SPL06 temp/pressure and LDR light level,
//Then updates the SensorData object using it's API.
void sampling_thread();

#endif