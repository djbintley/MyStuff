#ifndef CALIBRATION_H
#define CALIBRATION_H

struct ServoCal
{
    float offset;     // degrees
    bool invert;      // true if reversed
};

struct Calibration
{
    ServoCal shoulder[4];
    ServoCal knee[4];
};

#endif