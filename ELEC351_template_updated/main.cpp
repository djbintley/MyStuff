#include "mbed.h"
#include "uop_msb.h"
#include "Sampling.hpp"
#include "SDCardLog.hpp"
#include "SensorData.hpp"
#include "Serial.hpp"
#include "LEDBar.hpp"

SensorData sensorData;
EnvSensor SENSE;
LedBarDisplay ledBar(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN, // Data pins D0–D7
    LED_RED_LE_PIN,      // RED latch
    LED_GRN_LE_PIN,      // GREEN latch
    LED_BLUE_LE_PIN,      // BLUE latch
    LED_BAR_OE_PIN       // Enable (active low)
);

//Threads
Thread SensorThread;
Thread SDThread(osPriorityNormal,12288); //12kB to handle the large strings
Thread SerialThread;

int main()
{   
    ThisThread::sleep_for(500ms);
    printf("\nMSB4 SENSOR SELF TEST\n");
    printf("TEMP = %.3f\n", SENSE.getTemperature());
    printf("PRESS = %.3f\n", SENSE.getPressure());
    while(1);
    //Start Threads
    SensorThread.start(callback(sampling_thread));
    SDThread.start(callback(SDCard_thread));
    SerialThread.start(callback(serial_thread));

    //Set Thread Priorities, sensors highest and serial lowest
    SensorThread.set_priority(osPriorityHigh);
    //SDThread.set_priority(osPriorityNormal);
    SerialThread.set_priority(osPriorityLow);
    
    printf("\n\nStarting...\n");
    while (true) {
        ThisThread::sleep_for(1s);
    }
}
