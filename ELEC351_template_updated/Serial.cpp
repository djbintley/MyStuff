#include "Serial.hpp"

//Set Default LED Bar display mode to temperature
static char selectedMode = 'T';   // T = temperature, P = pressure, L = light
//Serial interface
static BufferedSerial pc(USBTX, USBRX, 115200);

//reads a character if available
static bool read_char(char &c) {
    if (pc.readable()) {
        pc.read(&c, 1);
        return true;
    }
    return false;
}

//Thread function
void serial_thread() {
    //Initialise temporary variables
    float t = 0.0f;
    float p = 0.0f;
    float l = 0.0f;
    char rx = 0;

    while (true) {
        //Read sensor data
        sensorData.get(t, p, l);

        //Print values
        printf("T = %.2f C,  P = %.2f mbar,  L = %.0f\r\n", t, p, l);

        //Check for incoming data
        if (read_char(rx)) {
            if (rx == 'T' || rx == 'P' || rx == 'L') {
                selectedMode = rx;
                printf("LED Bar now displaying: '%c'\r\n", selectedMode);
            }
        }else{
            printf("Invalid Character Input");
        }

        //Update LED Bar
        switch (selectedMode) {
            case 'T':
                //ledBar.setLevel((int)t);
                printf("T = %.2f C", t);     
                break;
            case 'P':
                //ledBar.setLevel((int)(p / 40)); 
                printf("P = %.2f mbar", p);   
                break;
            case 'L':
                //ledBar.setLevel((int)(l / 2000));
                printf("L = %.0f", l);  
                break;
        }
        //Need to sleep while data values are not being read
        ThisThread::sleep_for(1s);
    }
}