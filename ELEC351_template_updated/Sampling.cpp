#include "Sampling.hpp"
#include "mbed.h"

//Global shared data object
SensorData sensorData;

//Function to get called repeatedly in the Sampling Thread
void sampling_thread()
{
    while (true) {
        //Gather Data from SPL06-001
        float temp = env.getTemperature();
        float press = env.getPressure();
        
        //Gather light level from LDR
        float light = ldr.read_u16();

        sensorData.set(temp, press, light);

        ThisThread::sleep_for(1s);  // 1 Hz sampling
    }
}