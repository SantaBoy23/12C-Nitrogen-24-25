#include "main.h"

const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

void default_constants() {

  chassis.drive_imu_scaler_set(1.0281);

  // P, I, D, and Start I
  chassis.pid_drive_constants_forward_set(17.80, 0.0, 102.50);
  chassis.pid_drive_constants_backward_set(17.80, 0.0, 102.50);  // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(12.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.015, 17.25, 15.0);   // Turn in place constants
  chassis.pid_swing_constants_forward_set(6.90, 0.0, 55.0);
  chassis.pid_swing_constants_backward_set(6.90, 0.0, 55.0);   // Swing constants
  chassis.pid_odom_angular_constants_set(6.4, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(2.75, 0.0, 36.0);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.8);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void SoloAWPBlue(){ 

  //set starting angle
  chassis.drive_angle_set(45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15_in);
  ClampDown(true);
  chassis.pid_wait();

  //start intake
  IntakeMove(127);

  //turn to first ring
  chassis.pid_turn_set(-107_deg, TURN_SPEED); //used to be -110
  chassis.pid_wait();

  //drive to ring
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from ring
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards 4 ring stack
  chassis.pid_turn_set(-155_deg, TURN_SPEED);
  chassis.pid_wait();

  //drop ring rush mech
  DoinkerRightDrop(true);

  //drive to 4 ring stack
  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from 4 ring stack and raise doinker
  chassis.pid_drive_set(42_in, DRIVE_SPEED, true); //used to be 40
  chassis.pid_wait();
  DoinkerRightDrop(false);

  //turn rings near alliance stake
  chassis.pid_turn_set(82_deg, TURN_SPEED); //used to be 78
  chassis.pid_wait();

  //drop mogo
  ClampDown(false);

  //drive to rings
  chassis.pid_drive_set(-40_in, DRIVE_SPEED, true); 
  chassis.pid_wait();

  //stop intaking and leave one ring in intake
  IntakeMove(0);

  //delay to let ring fall out of intake
  pros::delay(200);

  //turn towards other mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(20_in, 50, true);
  chassis.pid_wait_until(19);
  ClampDown(true);
  chassis.pid_wait();

  //delay to prevent jamming
  pros::delay(150);

  //start intaking
  IntakeMove(127);

  //turn to other rings
  chassis.pid_turn_set(87_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to other rings
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from rings
  chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //put lb up
  LiftMoveTo(1100);

  //turn towards ladder
  chassis.pid_turn_set(-135_deg, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //drive to ladder
  chassis.pid_drive_set(-12_in, 50, true);
  chassis.pid_wait();

}

void SoloAWPRed(){

  //set starting angle
  chassis.drive_angle_set(-45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15_in);
  ClampDown(true);

  //start intake
  IntakeMove(127);

  //turn to first ring
  chassis.pid_turn_set(107_deg, TURN_SPEED); //used to be -110
  chassis.pid_wait();

  //drive to ring
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from ring
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards 4 ring stack
  chassis.pid_turn_set(155_deg, TURN_SPEED);
  chassis.pid_wait();

  //drop ring rush mech
  DoinkerLeftDrop(true);

  //drive to 4 ring stack
  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from 4 ring stack and raise doinker
  chassis.pid_drive_set(42_in, DRIVE_SPEED, true); //used to be 40
  chassis.pid_wait();
  DoinkerLeftDrop(false);

  //turn rings near alliance stake
  chassis.pid_turn_set(-82_deg, TURN_SPEED); //used to be 78
  chassis.pid_wait();

  //drop mogo
  ClampDown(false);

  //drive to rings
  chassis.pid_drive_set(-40_in, DRIVE_SPEED, true); 
  chassis.pid_wait();

  //stop intaking and leave one ring in intake
  IntakeMove(0);

  //delay to let ring fall out of intake
  pros::delay(200);

  //turn towards other mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(20_in, 50, true);
  chassis.pid_wait_until(19);
  ClampDown(true);

  //delay to prevent jamming
  pros::delay(150);

  //start intaking
  IntakeMove(127);

  //turn to other rings
  chassis.pid_turn_set(-87_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to other rings
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drive back from rings
  chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //put lb up
  LiftMoveTo(1100);

  //turn towards ladder
  chassis.pid_turn_set(135_deg, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //drive to ladder
  chassis.pid_drive_set(-12_in, 50, true);
  chassis.pid_wait();
}

void SoloAWPAltBlue () {

  //set starting angle
  chassis.drive_angle_set(-45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15.3_in);
  ClampDown(true);

  //turn towards centered rings
  chassis.pid_turn_set(-42.5_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to centered rings and reset lb
  LiftHome();
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drop right doinker
  DoinkerLeftDrop(true);

  //drive forwards
  pros::delay(250);
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //lift doinker
  DoinkerLeftDrop(false);
  pros::delay(250);

  //Turn towards ring and start intake
  chassis.pid_turn_set(-65_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);

  //Move to ring
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED);
  chassis.pid_wait();

//move forward
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(250);

  //turn towards center rings and stop intake
  chassis.pid_turn_set(-133_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move (0);

  //move to center rings and drop doinker
  chassis.pid_drive_set(-39_in, 90, true);
  chassis.pid_wait_until(-24_in);
  DoinkerLeftDrop(true);

  //move backwards and lift doinker and start intake
  chassis.pid_drive_set(28_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(24_in);
  DoinkerLeftDrop(false);
  intake.move(-127);

  //turn towards ring and start intake
  chassis.pid_turn_set(-140_deg, TURN_SPEED);
  chassis.pid_wait();
  IntakeMove(127);

  //move to ring
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards rings
  chassis.pid_turn_set(92_deg, TURN_SPEED);
  chassis.pid_wait();

  //move to rings and stop intake
  intake.move(127);
  chassis.pid_drive_set(-22_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.move(0);

  //drop goal and turn to goal
  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  ClampDown(false);
  chassis.pid_turn_set(-3_deg, TURN_SPEED);
  chassis.pid_wait();

  //move to goal and grab goal and start intake
  
  chassis.pid_drive_set(9_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(8.6_in);
  ClampDown(true);
  pros::delay(50);
  intake.move(127);

  //turn towards tower and put lb up
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  LiftMoveTo(1150);

  //move into tower
  chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void SoloAWPAltRed () {
  //set starting angle
  chassis.drive_angle_set(45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15.3_in);
  ClampDown(true);

  //turn towards centered rings
  chassis.pid_turn_set(42.5_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to centered rings and reset lb
  LiftHome();
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drop right doinker
  DoinkerRightDrop(true);

  //drive forwards
  pros::delay(250);
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //lift doinker
  DoinkerRightDrop(false);
  pros::delay(250);

  //Turn towards ring and start intake
  chassis.pid_turn_set(65_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);

  //Move to ring
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED);
  chassis.pid_wait();

  //move forward
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(250);

  //turn towards center rings and stop intake
  chassis.pid_turn_set(133_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move (0);

  //move to center rings and drop doinker
  chassis.pid_drive_set(-39_in, 90, true);
  chassis.pid_wait_until(-24_in);
  DoinkerRightDrop(true);

  //move backwards and lift doinker and start intake
  chassis.pid_drive_set(28_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(24_in);
  DoinkerRightDrop(false);
  intake.move(127);

  //turn towards ring and start intake
  chassis.pid_turn_set(140_deg, TURN_SPEED);
  chassis.pid_wait();

  //move to ring
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards rings
  chassis.pid_turn_set(-92_deg, TURN_SPEED);
  chassis.pid_wait();

  //move to rings and stop intake
  intake.move(127);
  chassis.pid_drive_set(-22_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.move(0);

  //drop goal and turn to goal
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  ClampDown(false);
  chassis.pid_turn_set(3_deg, TURN_SPEED);
  chassis.pid_wait();
  

  //move to goal and grab goal and start intake
  chassis.pid_drive_set(10.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(10.4_in);
  ClampDown(true);
  pros::delay(50);
  intake.move(127);
  
  //swing towards tower
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, SWING_SPEED, 5);
  chassis.pid_wait_quick_chain();

  //move into tower
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void GoalSideQualsBlue() {

  //set starting angle
  chassis.drive_angle_set(-45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15.3_in);
  ClampDown(true);

  //turn towards centered rings
  chassis.pid_turn_set(-42.5_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to centered rings and reset lb
  LiftHome();
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drop right doinker
  DoinkerLeftDrop(true);

  //drive forwards
  pros::delay(250);
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //lift doinker
  DoinkerLeftDrop(false);
  pros::delay(250);

  //Turn towards ring and start intake
  chassis.pid_turn_set(-65_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);

  //Move to ring
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED);
  chassis.pid_wait();

  //Turn to normal ring
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(110_deg, TURN_SPEED);
  chassis.pid_wait();

  //Drive to normal ring
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards corner
  chassis.pid_turn_set(22_deg, TURN_SPEED);
  chassis.pid_wait();

  //Move to corner
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, 80, true);
  chassis.pid_wait_quick_chain();

  //push into corner 3 times
  chassis.pid_drive_set(-6.5_in, 70, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, 105, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, 105, true);
  chassis.pid_wait();
  pros::delay(100);

  //go forwards, do a 180, drop goal, put up lb, back up
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(236_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  ClampDown(false);
  LiftMoveTo(1340);
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
}

void GoalSideQualsRed() {

  //set starting angle
  chassis.drive_angle_set(45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15.3_in);
  ClampDown(true);

  //turn towards centered rings
  chassis.pid_turn_set(42.5_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to centered rings and reset lb
  LiftHome();
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drop right doinker
  DoinkerRightDrop(true);

  //drive forwards
  pros::delay(250);
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //lift doinker
  DoinkerRightDrop(false);
  pros::delay(250);

  //Turn towards ring and start intake
  chassis.pid_turn_set(65_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);

  //Move to ring
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED);
  chassis.pid_wait();

  //Turn to normal ring
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-110_deg, TURN_SPEED);
  chassis.pid_wait();

  //Drive to normal ring
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards corner
  chassis.pid_turn_set(-22_deg, TURN_SPEED);
  chassis.pid_wait();

  //Move to corner
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, 80, true);
  chassis.pid_wait_quick_chain();

  //push into corner 3 times
  
  chassis.pid_drive_set(-6.5_in, 70, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, 105, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, 105, true);
  chassis.pid_wait();
  pros::delay(100);

  //go forwards, do a 180, drop goal, put up lb, back up
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-236_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  ClampDown(false);
  LiftMoveTo(1340);
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
}

void RingSideQualsBlue() {

}

void RingSideQualsRed() {

  //set starting angle
  chassis.drive_angle_set(-45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo and reset lb
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  LiftHome();

  //drive to mogo, slow down, and clamp
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(2_in, 90, true);
  chassis.pid_wait_until(1.4_in);
  ClampDown(true);

  //turn to ring  and start intake
  chassis.pid_turn_set(147_deg, TURN_SPEED);
  chassis.pid_wait();
  IntakeMove(127);

  //drive to stack and drop doinker
  DoinkerLeftDrop(true);
  chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-20_in);
  DoinkerLeftDrop(true);

  //drive back from ring and lift doinker
  chassis.pid_drive_set(29_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(28_in);
  DoinkerLeftDrop(false);

  //turn into lined up rings and drive into them
  chassis.pid_turn_set(116_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, 100, true);
  chassis.pid_wait_quick_chain();

  //go forwards then turn towards corner rings
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(50_deg, TURN_SPEED);
  chassis.pid_wait();

  //move into corner
  chassis.pid_drive_set(-33_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5.5_in, 50, true);
  chassis.pid_wait_quick_chain();

  //move out of corner, stop intake, and turn towards alliance rings
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  IntakeMove(0);
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();

  //start intake, drive to alliance rings and drop right doinker
  IntakeMove(127);
  chassis.pid_drive_set(-25.8_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-23);
  DoinkerRightDrop(true);

  //move away from alliance rings and lift doinker
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(7_in);
  DoinkerRightDrop(false);

  //turn towards ring, move into ring, then back up
  chassis.pid_turn_set(290_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards ring and ladder, lift lb, and move into ladder
  chassis.pid_turn_set(220_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  LiftMoveTo(1285);
  chassis.pid_drive_set(-11.75_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void GoalSideElimsBlue() {
  
}

void GoalSideElimsRed() {
  
  //set starting angle
  chassis.drive_angle_set(45_deg);

  //drive forward a bit
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  pros::delay(50);
  LiftMoveTo(1450);
  pros::delay(400);

  //drive back from alliance stake
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards mogo and put down lb
  chassis.pid_turn_set(-2_deg, TURN_SPEED);
  chassis.pid_wait();
  LiftHome();

  //drive to mogo and clamp
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(15.3_in);
  ClampDown(true);

  //turn toward ladder rings
  chassis.pid_turn_set(143_deg, TURN_SPEED);
  chassis.pid_wait();

  //start intake slow, move to ladder rings and drop doinker
  IntakeMove(20);
  chassis.pid_drive_set(-26.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-21_in);
  DoinkerRightDrop(true);

  //move out from under ladder, lift doinker, start intake fast
  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(25_in);
  DoinkerRightDrop(false);
  IntakeMove(127);

  //turn to ring, and move into ring
  chassis.pid_turn_set(152_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(250);
  /*
  //turn towards other ladder ring, stop intake, move to ladder ring, and drop doinker.
  chassis.pid_turn_set(123_deg, TURN_SPEED);
  chassis.pid_wait();
  IntakeMove(0);
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-14_in);
  DoinkerRightDrop(true);

  //move out from under ladder and lift doinker, start intake
  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(25_in);
  DoinkerRightDrop(false);
  IntakeMove(127);

  //turn to ring, and move into ring
  chassis.pid_turn_set(134_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  */
  
  //move away from ladder, turn towards rings, move to ring
  chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(267_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards corner
  chassis.pid_turn_set(-26_deg, TURN_SPEED);
  chassis.pid_wait();

  //move to corner
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, 80, true);
  chassis.pid_wait_quick_chain();

  //push into corner 3 times
  chassis.pid_drive_set(-6.5_in, 70, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, 105, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, 105, true);
  chassis.pid_wait();
  pros::delay(100);
  
}

void GoalSideElimsAltBlue(){
  
}

void GoalSideElimsAltRed() {
  //move lift up a bit
  LiftMoveTo(500);

  //start intake
  IntakeMove(127);

  //drive forward at max speed to goal
  chassis.pid_drive_set(-34.5_in, 127, false); //used to be -36

  //once 30 inches are driven, put down lift, then stop intake
  chassis.pid_wait_until(-19_in); //used to be -26
  LiftMoveTo(1500);
  chassis.pid_wait_quick_chain();
  IntakeMove(0);

  //move back quickly
  chassis.pid_drive_set(1_in, 127, true);
  chassis.pid_wait_quick_chain();

  //turn quickly 
  chassis.pid_turn_set(100_deg, 127);
  chassis.pid_wait();

  //turn towards goal
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  //move towards second goal and clamp goal
  chassis.pid_drive_set(16.3_in, 97, true);
  chassis.pid_wait_until(15.5_in);
  ClampDown(true);
  chassis.pid_wait();
  LiftHome();

  //turn towards alliance stake rings
  chassis.pid_turn_set(-47_deg, TURN_SPEED);
  chassis.pid_wait();

  //start intake
  IntakeMove(127);

  //wait for a bit, then stop
  pros::delay(175);
  IntakeMove(0);

  //move to center rings and drop right doinker
  chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  DoinkerRightDrop(true);

  //back up from ring
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  DoinkerRightDrop(false);

  //start intake
  IntakeMove(127);
  //chassis.pid_turn_set(-110_deg, TURN_SPEED);
  //chassis.pid_wait();
  //chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
  //chassis.pid_wait();

}

void RingSideElimsRed() {

  //drop doinker and start intake
  DoinkerLeftDrop(true);
  IntakeMove(127);

  //rush to rings
  chassis.pid_drive_set(-40_in, 127, false);
  chassis.pid_wait_quick_chain();

  //drive back from rings
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void RingSideElimsBlue() {
  
  //set starting angle
  //chassis.drive_angle_set(-170_deg);

  //put down doinker and start intake
  DoinkerRightDrop(true);
  IntakeMove(127);

  //drive to 4 ring stack
  chassis.pid_drive_set(-42_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  //wait a bit and then turn off intake
  pros::delay(200);
  IntakeMove(0);
  LiftMoveTo(1000);

  //swing to mogo and clamp
  chassis.pid_drive_set(1.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, SWING_SPEED, 10);
  chassis.pid_wait();
  DoinkerRightDrop(false);
  pros::delay(400);

  //move back a little and clamp
  chassis.pid_drive_set(2.5_in, 50, true);
  chassis.pid_wait();
  ClampDown(true);

  //turn to line up with rings
  pros::delay(200);
  chassis.pid_turn_set(-80_deg, TURN_SPEED);
  chassis.pid_wait();
  DoinkerRightDrop(false);

  //drive over rings
  IntakeMove(127);
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards other rings
  chassis.pid_turn_set(-95_deg, TURN_SPEED);
  chassis.pid_wait();
  
  //drive over ring
  chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn to corner
  chassis.pid_turn_set(-35_deg, TURN_SPEED);
  chassis.pid_wait();
  DoinkerLeftDrop(false);

  //drive into corner
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18_in, 50, true);
  chassis.pid_wait();

  //drive back from corner
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //drive into corner again
  chassis.pid_drive_set(-10_in, 50, true);
  chassis.pid_wait();

  //drive back from corner
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn towards preload
  chassis.pid_turn_set(92_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to preload
  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  //chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
  //                     true);
  //chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{24_in, 24_in, 90_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  //chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
  //                     true);
  //chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .