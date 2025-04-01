#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline ez::Piston doinkerRight('E');
inline ez::Piston doinkerLeft('D');

void DoinkerRightDrop(bool DoinkerRightState);
void DoinkerLeftDrop(bool DoinkerLeftState);
void DoinkersDrop(bool DoinkersState);
void DoinkerControl();