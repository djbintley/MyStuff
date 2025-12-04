/*
SensorData.cpp: This file contains code for the SensorData class. It provides variables to store Temperature, Pressure and Light as well as APIs to set and read them in a threadsafe manner.
Author: David Bintley
Student Number: 10855323
*/
#include "SensorData.hpp"

SensorData::SensorData():
    temperature(0.0f),
    pressure(0.0f),
    light(0.0f)
{}


//API to set values
void SensorData::set(float newTemp, float newPress, float newLight){
    //Lock so that nothing interrupts while values are being set
    mutex.lock();
    temperature = newTemp;
    pressure = newPress;
    light = newLight;
    mutex.unlock();
}

//API to read values
void SensorData::get(float &reqTemp, float &reqPress, float &reqLight){
    //Lock so that nothing interrupts while values are being read
    mutex.lock();
    reqTemp = temperature;
    reqPress = pressure;
    reqLight = light;
    mutex.unlock();
}