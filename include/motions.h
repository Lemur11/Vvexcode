#pragma once

#include "vex.h"
#include "pid.h"
void move(float target, PID &left_pid, PID &right_pid, int units=1, int timeout=10000, int exit_dist=0);
void turn(float degrees, PID &turn_pid, int timeout=10000);
void turn_to_heading(float degrees, PID &turn_pid, int timeout=10000, float turn_factor=1);