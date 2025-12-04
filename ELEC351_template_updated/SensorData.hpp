/*
SensorData.hpp: This header file declares the SensorData Class, its constructor, api and private variables. 
Author: David Bintley
Student Number: 10855323
*/
#ifndef Sensor_HPP
#define Sensor_HPP

#include "mbed.h"
#include "uop_msb.h"

class SensorData {
    public:
        //Constructor
        SensorData();

        //Updates all sensor readings    
        void set(float temperature, float pressure, float light);

        //Function used to access readings
        void get(float &temperature, float &pressure, float &light);

    private:
        //Values to Store readings in
        float temperature;
        float pressure;
        float light;

        //Mutex initialisation
        Mutex mutex;
};

#endif