#include "SensorData.hpp"

SensorData::SensorData():
    temperature(0.0f),
    pressure(0.0f),
    light(0.0f)
{}


//API to set values
void SensorData::set(float newTemp, float newPress, float newLight){
    mutex.lock();
    temperature = newTemp;
    pressure = newPress;
    light = newLight;
    mutex.unlock();
}

//API to read values
void SensorData::get(float &reqTemp, float &reqPress, float &reqLight){
    mutex.lock();
    reqTemp = temperature;
    reqPress = pressure;
    reqLight = light;
    mutex.unlock();
}