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
  chassis.pid_drive_set(-13.4_in, DRIVE_SPEED, true);
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

  //push into corner 2 times
  
  chassis.pid_drive_set(-7_in, 70, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(12_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, 105, true);
  chassis.pid_wait_quick_chain();
  /*chassis.pid_drive_set(9_in, 90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, 105, true);
  chassis.pid_wait();*/
  pros::delay(100);

  //go forwards, do a 180, drop goal, put up lb, back up
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-236_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  ClampDown(false);
  LiftMoveTo(1340);
  chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
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

  //turn to ring and start intake
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
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //move out of corner, stop intake, and turn towards alliance rings
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();

  //start intake, drive to alliance rings and drop right doinker
  IntakeMove(127);
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  DoinkerRightDrop(true);

  //move away from alliance rings and lift doinker
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
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

  //put down doinker and start intake
  DoinkerLeftDrop(true);
  IntakeMove(127);

  //drive to 4 ring stack
  chassis.pid_drive_set(-40_in, 127, false);
  chassis.pid_wait();
  
  //wait a bit and then turn off intake
  pros::delay(100);
  IntakeMove(0);
  pros::delay(100);

  //swing to mogo and clamp
  chassis.pid_drive_set(1.4_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -85_deg, SWING_SPEED, 5);
  chassis.pid_wait();
  DoinkerLeftDrop(false);
  pros::delay(400);

  //move back a little and clamp
  chassis.pid_drive_set(2.5_in, 50, true);
  chassis.pid_wait();
  ClampDown(true);

  //turn to line up with rings
  chassis.pid_turn_set(-102_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive over rings
  pros::delay(150);
  IntakeMove(127);
  chassis.pid_drive_set(-34_in, 80, true);
  chassis.pid_wait();

  //turn in general direction of corner
  chassis.pid_turn_set(-160_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive over to corner
  chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //turn towards corner
  chassis.pid_turn_set(-114_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive into corner and drive back
  chassis.pid_drive_set(-4.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //grab last ring
  chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //drive away from corner
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  //turn towards starting position
  chassis.pid_turn_set(111_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to alliance stake rings
  chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //drop doinker, wait a bit
  DoinkerLeftDrop(true);
  pros::delay(50);
  
  //drive back, wait a bit
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);

  //lift doinker and drive forward
  DoinkerLeftDrop(false);
  chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //move lift to loading position
  LiftMoveTo(195);

  //turn towards alliance stake
  chassis.pid_turn_set(-167_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive a bit forward
  chassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  IntakeMove(0);
  LiftMoveTo(1300);
}

void RingSideElimsBlue() {

  //put down doinker and start intake
  DoinkerRightDrop(true);
  IntakeMove(127);

  //drive to 4 ring stack
  chassis.pid_drive_set(-40_in, 127, false);
  chassis.pid_wait();
  
  //wait a bit and then turn off intake
  pros::delay(100);
  IntakeMove(0);
  pros::delay(100);

  //swing to mogo and clamp
  chassis.pid_drive_set(1.4_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 85_deg, SWING_SPEED, 5); //used to be 90
  chassis.pid_wait();
  DoinkerRightDrop(false);
  pros::delay(400);

  //move back a little and clamp
  chassis.pid_drive_set(2.5_in, 50, true);
  chassis.pid_wait();
  ClampDown(true);

  //turn to line up with rings
  chassis.pid_turn_set(102_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive over rings
  pros::delay(150);
  IntakeMove(127);
  chassis.pid_drive_set(-34_in, 80, true);
  chassis.pid_wait();

  //turn in general direction of corner
  chassis.pid_turn_set(160_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive over to corner
  chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //turn towards corner
  chassis.pid_turn_set(114_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive into corner and drive back
  chassis.pid_drive_set(-4.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //grab last ring
  chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  //drive away from corner
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  //turn towards starting position
  chassis.pid_turn_set(-111_deg, TURN_SPEED);
  chassis.pid_wait();

  //drive to alliance stake rings
  chassis.pid_drive_set(-31.7_in, DRIVE_SPEED, true);
  chassis.pid_wait();
   
  //drop doinker, wait a bit
  DoinkerRightDrop(true);
  pros::delay(50);
  
  //drive back, wait a bit
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);

  //lift doinker and drive forward
  DoinkerRightDrop(false);
  chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //move lift to loading position
  LiftMoveTo(195);

  //turn towards alliance stake
  chassis.pid_turn_set(165_deg, TURN_SPEED); //used to be 168, if too far, other way
  chassis.pid_wait();

  //drive a bit forward
  chassis.pid_drive_set(2_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //put ring on alliance stake
  IntakeMove(0);
  LiftMoveTo(1300);
}

void DoNothingAuto(){
  DoNothing();
}