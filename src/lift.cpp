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

//Function to run lift limit switch reset
void LiftLimitControl() {
    if (DownTog){
        if (liftLimit.get_value()){
            pros::delay(100);
            ResetLiftPosition();
            LiftSetBrakeHold();
              LiftMoveTo(20);
            DownTog = false;
            
        }
        else {
            LiftMoveTo(LiftPID.target - 70);
        }
    }
}

//Function to set lift PID target to start/home position
void LiftHome() {
    if (LiftControlAuto == true) {
        LiftMoveTo(0);
    }

    if (LiftControlDriver == true) {
        DownTog = true;
    }
}

//Function to set lift PID target to loading position
void LiftLoad() {
    DownTog = false;
    LiftPID.target_set(245);
}

//Function to set lift PID target to scoring position
void LiftScore() {
    DownTog = false;
    LiftPID.target_set(1200);
}

//Function to manually control the lift
void LiftManualControl() {
    
    DownTog = false;

    //Increase lift PID target by 30
    LiftMoveTo(LiftPID.target + 30);
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