#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline pros::Motor liftRight(-2);
inline pros::Motor liftLeft(3);

inline pros::Rotation liftRotation(1);
inline pros::ADIDigitalIn liftLimit('h');

inline void set_lift(int input) {
    liftRight.move(input);
    liftLeft.move(input);
}
  
inline ez::PID LiftPID{0.6, 0, .1, 0, "Lift"};

inline void lift_wait() {
    while (LiftPID.exit_condition({liftLeft, liftRight}, true) == ez::RUNNING) {
        pros::delay(ez::util::DELAY_TIME);
    }
}

inline bool LiftControlAuto = false;
inline bool LiftControlDriver = false;
inline bool DownTog = false;

void LiftMoveTo(int LiftPosition);
void LiftManualControl();
void ResetLiftPosition();
void LiftSetBrakeHold();
void LiftSetBrakeCoast();
void LiftLimitControl();
void LiftHome();
void LiftLoad();
void LiftScore();
void LiftControl();