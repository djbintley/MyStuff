#ifndef LEDBar_HPP
#define LEDBar_HPP

#include "mbed.h"

class LedBarDisplay {
public:
    //Constructor
    //includes the pins, the output enable pin and individual colour latch enables
    LedBarDisplay(
        PinName d0, PinName d1, PinName d2, PinName d3,
        PinName d4, PinName d5, PinName d6, PinName d7,
        PinName redLE, PinName greenLE, PinName blueLE,
        PinName barOE
    );

    //Set the colours individually
    void setRed(uint8_t pattern);
    void setGreen(uint8_t pattern);
    void setBlue(uint8_t pattern);

    //Set the entire bar
    void setLevel(int level);

private:
    //Private variables
    BusOut data;
    DigitalOut redLatch;
    DigitalOut greenLatch;
    DigitalOut blueLatch;
    DigitalOut enable;

    //Function to strobe latch
    void latch(DigitalOut &latchPin, uint8_t pattern);
};

#endif