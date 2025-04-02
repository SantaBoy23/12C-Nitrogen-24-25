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
  pros::lcd::print(0, "ColorSort Running...");
  while (true) {
    if (current_mode == BlueMode) {  
      if ((intakeColor.get_hue()) < 17 && (intakeColor.get_proximity() <= 300)) {
        pros::delay(50);
        IntakeMove(0);
        pros::delay(100);
      } 
      else {
        DoNothing();
      }
    }
    else if (current_mode == RedMode) {
      if (((intakeColor.get_hue()) > 190) && ((intakeColor.get_hue()) < 350) && (intakeColor.get_proximity() <= 255)) {
        pros::delay(50);
        IntakeMove(0);
        pros::delay(100);
      } 
      else {
        DoNothing();
      } 
    }
    else {
      DoNothing();
    }
  }
}

void ColorSensorLight(int LightLevel) {
  intakeColor.set_led_pwm(LightLevel);
}