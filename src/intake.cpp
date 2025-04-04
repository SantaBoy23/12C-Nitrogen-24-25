#include "main.h"

//Parallel Function to control intake speed
void IntakeMove(int IntakeSpeed) {
  intake.move(IntakeSpeed);
}

//Function for intake driver control
void IntakeControl() {

    //If intake control is permitted, run this function
    if (IntakeControlActive == true) {

        //If L1 is pressed, spin intake forward
        if (master.get_digital(DIGITAL_L1)) {
            IntakeMove(127);
        } 

        //If L2 is pressed, spin intake backward
        else if (master.get_digital(DIGITAL_L2)) {
            IntakeMove(-127);
        } 

        //If no button is pressed, stop intake
        else {
            IntakeMove(0);
        }
    }
}