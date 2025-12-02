#ifndef SDCardLog_HPP
#define SDCardLog_HPP

#include "mbed.h"
#include "SensorData.hpp"

extern SensorData sensorData;
//Function to repeatedly call in the SD Card thread
void SDCard_thread();

#endif