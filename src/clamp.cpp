#include "main.h"

//Parallel function for changing clamp state
void ClampDown(bool ClampState) {
    clampBack.set(ClampState);
}

//Function for clamp driver control
void ClampControl() {

  //If R2 is pressed, put clamp down
  if (master.get_digital(DIGITAL_R2)) {
      ClampDown(true);
  } 
  
  //If R2 is pressed, put clamp up
  else if (master.get_digital(DIGITAL_R1)) {
    ClampDown(false);
  } 
}