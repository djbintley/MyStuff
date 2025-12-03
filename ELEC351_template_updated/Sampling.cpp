#include "Sampling.hpp"

//Function to get called repeatedly in the Sampling Thread
void sampling_thread()
{
    while (true) {
        //Get Data from SPL06-001
        float temp = env.getTemperature();
        float press = env.getPressure();
        
        //Get light level from LDR
        float light = ldr.read_u16();

        sensorData.set(temp, press, light);

        //Push to SD Card buffer
        sd_push_sample(temp, press, light);
        // 1 Hz sampling to match the sensor thread
        ThisThread::sleep_for(1s); 
    }
}