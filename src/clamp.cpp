#include "main.h"

void ClampDown(bool ClampState) {
    clampBack.set(ClampState);
}

void ClampControl() {
    if (master.get_digital(DIGITAL_R2)) {
        ClampDown(true);
      } 
      else if (master.get_digital(DIGITAL_R1)) {
        ClampDown(false);
      } 
}