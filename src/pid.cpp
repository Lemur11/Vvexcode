#include "vex.h"
#include "pid.h"
#include "utils.h"

PID::PID(float p, float i, float d, float windup_val, bool integral_zero_at_sign_change, float windup_range) : 
        kp(p), ki(i), kd(d), windup(windup_val), zero_at_sign_change(integral_zero_at_sign_change), windup_range(windup_range) {};

float PID::cycle(float reference, float reading) {
    error = reference - reading;
    if (fabs(error) < windup_range) {
        if (zero_at_sign_change && (sgn(error) != sgn(prev_error))) {
            err_sum = error;
        }
        else {
            err_sum += error;
        }
    }
    err_sum = clamp(err_sum, -windup, windup);
    delta = error - prev_error;
    printf("Delta: %f", delta);
    prev_error = error;

    vol = kp * error + err_sum * ki + delta * kd;
    vol = clamp(vol, -12000.0f, 12000.0f);
    // printf("E: %f\n", error);
    
    return vol;
}

void PID::set_prev(float val) {
    prev_error = val;
}

void PID::reset_sum() {
    err_sum = 0;
}

float PID::get_prev() {
    return prev_error;
}

float PID::get_deriv() {
    return delta;
}

void PID::set_consts(float kp, float ki, float kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}
