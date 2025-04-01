#include "main.h"

void DoinkerRightDrop(bool DoinkerRightState) {
    doinkerRight.set(DoinkerRightState);
}

void DoinkerLeftDrop(bool DoinkerLeftState) {
    doinkerLeft.set(DoinkerLeftState);
}

void DoinkersDrop(bool DoinkersState) {
    doinkerRight.set(DoinkersState);
    doinkerLeft.set(DoinkersState);
}

void DoinkerControl() {
    doinkerRight.button_toggle(master.get_digital(DIGITAL_B));
}