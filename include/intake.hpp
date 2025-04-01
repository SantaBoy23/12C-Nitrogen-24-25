#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline pros::Motor intake(-4);

void IntakeMove(int IntakeSpeed);
void IntakeControl();