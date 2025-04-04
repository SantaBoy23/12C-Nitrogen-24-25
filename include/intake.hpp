#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline pros::Motor intake(-4);

inline bool IntakeControlActive = true;

void IntakeMove(int IntakeSpeed);
void IntakeControl();