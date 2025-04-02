#include "main.h"

void lift_task() {
    pros::delay(2000);
    while (true) {
      set_lift(LiftPID.compute(liftLeft.get_position()));
  
      pros::delay(ez::util::DELAY_TIME);
    }
}

void LiftMoveTo(int LiftPosition) {
    LiftPID.target_set(LiftPosition);
}

void LiftManualControl() {
    int CurrentLiftPosition = liftLeft.get_position();
    LiftPID.target_set(LiftPID.target + 30);
}

void ResetLiftPosition() {
    liftRight.tare_position();
    liftLeft.tare_position();
}

void LiftHome() {
    LiftPID.target_set(0);
}

void LiftLoad() {
    LiftPID.target_set(175);
}

void LiftScore() {
    LiftPID.target_set(1100);
}

void LiftControl() {
    if (master.get_digital(DIGITAL_A)) {
        LiftHome();
    }
    else if (master.get_digital(DIGITAL_Y)){
        LiftLoad();
    }
    else if (master.get_digital(DIGITAL_X)) {
        LiftScore();
    }
    else if (master.get_digital(DIGITAL_B)) {
        LiftManualControl();
    }
}