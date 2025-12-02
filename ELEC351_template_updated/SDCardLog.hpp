#ifndef SDCardLog_HPP
#define SDCardLog_HPP

#include "mbed.h"
#include "SensorData.hpp"

//Function to repeatedly call in the SD Card thread
void logging_thread();

#endif