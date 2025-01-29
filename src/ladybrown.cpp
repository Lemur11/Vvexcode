#include "ladybrown.h"
#include <cmath>
#include <memory>

void LadyBrown::func() {
    while(true) {
        this->update();
        task::sleep(10);
    }
}

int task_() {
    LadyBrown::getInstance().func();
    return(0);
}

void LadyBrown::initialize() {
    update_task = vex::task(task_);
    lb_pid.set_prev(0);
}

void LadyBrown::update() {
    if (fabs(this->target - rot.position(degrees)) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
        at_target = true;
    }
    else {
        at_target = false;
    }
    if (on) {
        int reading = rot.position(degrees);
        printf("Reading: %d\n", reading);
        if (reading > 250) {
            reading = -(360-reading);
        }
        float vol = lb_pid.cycle(target, reading);
        // printf("Vol: %f\n", vol);
        float angle_rad = (114.0f - reading) * (M_PI / 180.0f);
        // printf("Angle rad: %f\n", angle_rad);
        // printf("FF: %f\n", ff_K * sin(angle_rad));
        lady_brown.spin(fwd, vol + ff_K * sin(angle_rad), volt);
    }
}

void LadyBrown::move(int target, bool blocking) {
    on = true;
    lb_pid.reset_sum();
    lb_pid.set_prev((target - rot.position(degrees)));
    printf("Tar %d\n", target);
    this->target = target;
    if (blocking) {
        while (true) {
            if (fabs(this->target - rot.position(degrees)) < pos_deadzone && lb_pid.get_deriv() < vel_deadzone) {
                break;
            }
            wait(20, msec);
        }
    }
}

void LadyBrown::off() {
    on = false;
    lady_brown.stop();
}

bool LadyBrown::done() {
    return at_target;
}