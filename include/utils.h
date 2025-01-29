#pragma once

#include "vex.h"

float wrap(float target, float reading);
int sgn(float x);
int joystick(int inp);
float target_cal(float x);
template <typename T> T clamp(T val, T min, T max) {
    if (val < min) {
        return min;
    }
    else if (val > max) {
        return max;
    }
    else {
        return val;
    }
}

float to_volt(float percent);
float deadband(float input, float width);