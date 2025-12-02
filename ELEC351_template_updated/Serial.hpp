#ifndef Serial_HPP
#define Serial_HPP

#include "mbed.h"
#include "SensorData.hpp"
//#include "led_bar_display.hpp"
#include "Sampling.hpp"

extern SensorData sensorData;
//extern LedBarDisplay ledBar;
//Function that handles two - way serial communication
//To be run in the serial thread
void serial_thread();

#endif