#include "main.h"

void IntakeMove(int IntakeSpeed) {
  intake.move(IntakeSpeed);
}

void IntakeControl() {
    if (IntakeControlActive == true) {
    if (master.get_digital(DIGITAL_L1)) {
        IntakeMove(127);
    } 
    else if (master.get_digital(DIGITAL_L2)) {
        IntakeMove(-127);
    } 
    else {
        IntakeMove(0);
    }
    }
}