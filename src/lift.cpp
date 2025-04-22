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
    LiftMoveTo(LiftPID.target + 30);
}

//Function to reset lift motor positions
void ResetLiftPosition() {
    liftRight.tare_position();
    liftLeft.tare_position();
}

//Function to set lift motors to brake hold mode
void LiftSetBrakeHold() {
    liftRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

//Function to set lift motors to brake coast mode
void LiftSetBrakeCoast() {
    liftRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    liftLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//Function to set lift PID target to start/home position
void LiftHome() {
    /*
    //If the lift limit switch is pressed, reset the lift position
    if (liftLimit.get_value()){
        pros::delay(20);
        ResetLiftPosition();
        LiftSetBrakeHold();
        LiftMoveTo(0);
    }

    //If the lift limit switch is not being pressed, bring the lift home. Target is negative to counteract slippage.
    else {
        LiftMoveTo(-50);
    }
    */

    LiftMoveTo(0);
}

//Function to set lift PID target to loading position
void LiftLoad() {
    LiftPID.target_set(180);
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