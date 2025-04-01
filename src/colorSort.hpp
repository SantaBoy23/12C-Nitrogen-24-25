#include "main.h"

enum ColorMode {
    BLUE_MODE,
    RED_MODE,
    NO_SORT_MODE
}

void toggle_color_mode() {
    if (current_mode == BLUE_MODE) {
      current_mode = RED_MODE;
    } else if (current_mode == RED_MODE) {
      current_mode = NO_SORT_MODE;
    } else {
      current_mode = BLUE_MODE;
    }
    pros::lcd::print(4, "Mode: %s", current_mode == BLUE_MODE ? "Blue" : (current_mode == RED_MODE ? "Red" : "No Sort"));
}