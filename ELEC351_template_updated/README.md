Student Number: 10855323
Name: David Bintley

I Believe that I have fulfilled all requirements.
This Can be checked in the following ways:

Accurate Sensor Sampling: The readings are printed through serial at a 1hz frequency.
The 1hz frequency is achieved by having the sampling on it's own thread with the highest priority and then sleeping the thread for 1 second after each measurement.
As the thread has the highest priority, no other thread disrupts the timing.

Multithreading: The thread setup is visible in Main. All threads use "ThisThread::sleep_for()" To avoid blocking other threads.
Data is accessed through APIs that use MUTEXs (See Sensordata.hpp and SensorData.cpp)

SD card logging: Put a blank SD Card in and after a minute it will have a csv file written to it with the readings for the last minute.
If you leave it for another minute it will have the second minute's readings appended to the "Enviromental_Data.csv" file.
There is a bufffer so that the SD Card is only written to once a minute. This can be found in SDCardLog.cpp

Serial Terminal Output: This should run as soon as the program starts on a baud rate of 115200, you can see that the values are written every second, as well as alarms and SD Card write alerts.
Characters can also be input to change the LED bar between light, temperature and pressure.
This can be found in Serial.hpp and Serial.cpp.

LED display: The display can be switched between displaying light, temperature and pressure by inputting 'L', 'T' or 'P' to the serial.
The bar class is written in LEDBar.hpp and LEDBar.cpp however it is utilised in Serial.cpp where the values are read through a threadsafe api.

Alarm: The alarm is handled in Sampling.cpp and it detects accurately when the light, temperature or pressure get too high or low according to the values at the top of that file.
You can test this by listening for the beep and shining a torch at or covering the LDR or inceasing or decreasing the temperature or pressure.

Code Structure: There are comments throughout as well as file headers.

YouTube Demonstration: https://youtu.be/L10q9zSEE9o?si=Fgne8oT5xqoNIiJQ