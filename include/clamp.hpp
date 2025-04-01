#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline ez::Piston clampBack('-A');

void ClampDown(bool ClampState);
void ClampControl();