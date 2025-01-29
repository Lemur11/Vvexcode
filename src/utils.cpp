#include "utils.h"
#include <cmath>

float wrap(float target, float reading) {
    float delta = fmod((reading - target + 540.0), 360.0) - 180.0;
    return -delta;
}

int sgn(float x) {
    return (x > 0) - (x < 0);
}  


int joystick(int inp) {
	if (abs(inp) < 15) {
		return 0;
	}
	else {
		return inp;
	}
}

float target_cal(float x) {
	if (x < 0) {
		return 360 + x;
	}
	else {
		return fmod(x, 360);
	}
}

/**
 * Scales a joystick to drive voltage scale.
 * Values get multiplied by 12 because motors can
 * output a max of 12 volts.
 * 
 * @param percent The input joystick reading.
 * @return The equivalent value in volts.
 */

float to_volt(float percent){
  return(percent*12.0/100.0);
}

/**
 * Deadband function for joystick control.
 * If the joystick value is small, we should just consider it 0.
 * 
 * @param input The input joystick value.
 * @param width Minimum value to not get zeroed out.
 * @return The deadbanded value.
 */

float deadband(float input, float width){
  if (std::fabs(input)<width){
    return(0);
  }
  return(input);
}
