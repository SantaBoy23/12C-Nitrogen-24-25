#include "main.h"

ez::Drive chassis(
    {-15, -16, -17},     // Left Chassis Ports
    {18, 19, 20},  // Right Chassis Ports
    10, 3.25, 450); // IMU port, Wheel Diameter, Drivebase RPM

ez::tracking_wheel horiz_tracker(6, 2, 4.33);  // Horizontal Tracking Wheel
// ez::tracking_wheel vert_tracker(9, 2.75, 4.0);   // Verical Tracking Wheel

void initialize() {

  void ResetLiftPosition();

  LiftPID.exit_condition_set(80, 50, 300, 150, 500, 500);

  ez::ez_template_print(); // Print EZ Template Branding

  pros::delay(500);  // Allow Legacy Ports to Configure

  pros::lcd::initialize(); // Initialize LCD Screen
  pros::lcd::register_btn1_cb(ToggleColorMode); // Print Color Sort Selector

  chassis.odom_tracker_front_set(&horiz_tracker); //Horizontal Tracking Wheel
  // chassis.odom_tracker_left_set(&vert_tracker); //Vertical Tracking Wheel

  // Chassis Controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);   // Sets the active brake kP
  
  default_constants(); // Set default autonomous constants

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    {"Solo AWP Blue\n\nRegular Solo AWP for Blue. Start on Ring Side.", SoloAWPBlue},
    {"Solo AWP Red\n\nRegular Solo AWP for Red. Start on Ring Side.", SoloAWPRed},
    {"Solo AWP Alternate Blue\n\nSingle Side Solo AWP for Blue. Start on Goal Side.", SoloAWPAltBlue},
    {"Solo AWP Alternate Red\n\nSingle Side Solo AWP for Red. Start on Goal Side.", SoloAWPAltRed},
    {"Safe Goal Side Blue\n\nSafe/Quals Goal Side for Blue. Start on Goal Side.", GoalSideQualsBlue},
    {"Safe Goal Side Red\n\nSafe/Quals Goal Side for Red. Start on Goal Side.", GoalSideQualsRed},
    {"Safe Ring Side Blue\n\nSafe/Quals Ring Side for Blue. Start on Ring Side.", RingSideQualsBlue},
    {"Safe Ring Side Red\n\nSafe/Quals Ring Side for Red. Start on Ring Side.", RingSideQualsRed},
    {"Elims Goal Side Blue\n\nRegular/Elims Goal Side for Blue. Start on Goal Side.", GoalSideElimsBlue},
    {"Elims Goal Side Red\n\nRegular/Elims Goal Side for Red. Start on Goal Side.", GoalSideElimsRed},
    {"Elims Goal Side Alternate Blue\n\nGoal Rush/Elims Goal Side for Blue. Start on Goal Side.", GoalSideElimsAltBlue},
    {"Elims Goal Side Alternate Red\n\nGoal Rush/Elims Goal Side for Red. Start on Goal Side.", GoalSideElimsAltRed},
    {"Elims Ring Side Blue\n\nRing Rush/Elims Ring for Blue. Start on Ring Side.", RingSideElimsBlue},
    {"Elims Ring Side Red\n\nRing Rush/Elims Ring for Red. Start on Ring Side.", RingSideElimsRed},
    {"Goal Side Neutral Stake Red\n\nGets neutral stake for Red. Start on goal Side.", RedGoalNeutralStake},
    {"Goal Side Neutral Stake Blue\n\nGets neutral stake for Blue. Start on goal Side.", BlueGoalNeutralStake},
    {"Do Nothing\n\nDo Nothing for Blue and Red. Start anywhere.", DoNothingAuto},
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  ColorSensorLight(100);
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

void disabled() {
}

void lift_task();
void ColorSort();

pros::Task Lift_Task(lift_task); // Turn on lift control/task
pros::Task ColorSort_Task(ColorSort); // Turn on color sort

void competition_initialize() {
}

void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ColorSortAuto = true; // Set color sort to autonomous mode
  LiftControlAuto = true; // Set lift control to autonomous mode

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}


// Simplifies printing tracker values to the brain screen
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

// EZ Template Extras such as PID Tuner and autonomous trigger
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();
      chassis.pid_tuner_full_enable(true);

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

// Driver Control
void opcontrol() {
  ColorSortAuto = false; // Disable automous color sort
  ColorSortDriver = true; // Enable driver control color sort

  LiftControlAuto = false; // Disable automous lift control
  LiftControlDriver = true; // Enable driver lift control

  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  // Put all robot control functions in this loop
  while (true) {
    ez_template_extras();
    chassis.opcontrol_tank();
    IntakeControl();
    LiftControl();
    LiftLimitControl();
    DoinkerControl();
    ClampControl();
    ColorSortKill();
    pros::delay(ez::util::DELAY_TIME);
  }
}
