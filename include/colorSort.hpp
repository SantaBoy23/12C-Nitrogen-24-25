#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline pros::Optical intakeColor(5);

inline bool ColorSortAuto = false;
inline bool ColorSortDriver = false;

void ToggleColorMode();
void ColorSort();
void ColorSensorLight(int LightLevel);