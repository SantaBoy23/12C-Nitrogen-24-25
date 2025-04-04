#include "main.h"

//Function to set lift position using PID
void lift_task() {

    //Wait for 2 seconds to permit initialization of other components
    pros::delay(2000);

    //Always have this function running in the background
    while (true) {
        //Set the lift PID target
        set_lift(LiftPID.compute(liftLeft.get_position()));
        
        //Delay to prevent overloading the CPU
        pros::delay(ez::util::DELAY_TIME);
    }
}

//Parallel function to set lift PID target
void LiftMoveTo(int LiftPosition) {
    LiftPID.target_set(LiftPosition);
}

//Function to manually control the lift
void LiftManualControl() {
    
    //Increase lift PID target by 30
    LiftPID.target_set(LiftPID.target + 30);
}

//Function to reset lift motor positions
void ResetLiftPosition() {
    liftRight.tare_position();
    liftLeft.tare_position();
}

//Function to set lift PID target to start/home position
void LiftHome() {
    LiftPID.target_set(0);
}

//Function to set lift PID target to loading position
void LiftLoad() {
    LiftPID.target_set(175);
}

//Function to set lift PID target to scoring position
void LiftScore() {
    LiftPID.target_set(1100);
}

//Function for lift driver control
void LiftControl() {

    //If A is pressed, set lift PID target to home position
    if (master.get_digital(DIGITAL_A)) {
        LiftHome();
    }

    //If Y is pressed, set lift PID target to loading position
    else if (master.get_digital(DIGITAL_Y)){
        LiftLoad();
    }

    //If X is pressed, set lift PID target to scoring position
    else if (master.get_digital(DIGITAL_X)) {
        LiftScore();
    }

    //If B is pressed, run manual control function
    else if (master.get_digital(DIGITAL_B)) {
        LiftManualControl();
    }
}