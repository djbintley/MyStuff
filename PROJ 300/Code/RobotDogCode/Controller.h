#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Bluepad32.h>
#include "Robot.h"

Robot robot;

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl);

void onDisconnectedController(ControllerPtr ctl);






#endif