#include "main.h"

enum ColorMode {
  BlueMode,
  RedMode,
  NoSortMode
};

inline ColorMode current_mode = NoSortMode;

void ToggleColorMode() {
    if (current_mode == BlueMode) {
      current_mode = RedMode;
    } else if (current_mode == RedMode) {
      current_mode = NoSortMode;
    } else {
      current_mode = BlueMode;
    }
    pros::lcd::print(4, "Mode: %s", current_mode == BlueMode ? "Blue" : (current_mode == RedMode ? "Red" : "No Sort"));
}

void ColorSort() {
  pros::delay(2000);
  master.rumble("---");
  while (true) {
    double IntakeColorHue = intakeColor.get_hue();
    int IntakeColorProximity = intakeColor.get_proximity();
    
    if (current_mode == BlueMode) {  
      if ((IntakeColorHue) < 17 && (IntakeColorProximity <= 300)) {
        IntakeControlActive = false;
        pros::delay(20);
        IntakeMove(0);
        pros::delay(40);
        IntakeControlActive = true;
      } 
    }
    else if (current_mode == RedMode) {
      if (((IntakeColorHue > 190) && (IntakeColorHue) < 350) && (IntakeColorProximity <= 255)) {
        IntakeControlActive = false;
        pros::delay(10);
        IntakeMove(0);
        pros::delay(80);
        IntakeControlActive = true;
      } 
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}

void ColorSensorLight(int LightLevel) {
  intakeColor.set_led_pwm(LightLevel);
}