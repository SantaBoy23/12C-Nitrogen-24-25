#include "main.h"

//Parallel function to change right doinker state
void DoinkerRightDrop(bool DoinkerRightState) {
    doinkerRight.set(DoinkerRightState);
}

//Parallel function to change left doinker state
void DoinkerLeftDrop(bool DoinkerLeftState) {
    doinkerLeft.set(DoinkerLeftState);
}

//Function to change both doinker states
void DoinkersDrop(bool DoinkersState) {
    doinkerRight.set(DoinkersState);
    doinkerLeft.set(DoinkersState);
}

//Function for right doinker driver control
void DoinkerControl() {

    //If > is pressed, toggle right doinker state
    doinkerRight.button_toggle(master.get_digital(DIGITAL_RIGHT));
}