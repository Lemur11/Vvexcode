#include "vex.h"
#include "devices.h"
#include "pid.h"
#include "autons.h"
#include "motions.h"
#include "ladybrown.h"

// move pids
PID left_pid = PID(0.032, 0, 0.15);
PID right_pid = PID(0.032, 0, 0.15);

// turn pid
PID turn_pid = PID(0.23, 0.08, 0.3, 100000.0f, true, 15.0);
// PID turn_pid = PID(0.3, 0.08, 0.3, 100000.0f, true, 15.0);

void test() {
    printf("Moving");
    turn(20, turn_pid);
    turn(40, turn_pid);
    turn(90, turn_pid);

}

void skills() {
    intake.spin(fwd, 600, rpm);
    wait(0.5, sec);
    move(680, left_pid, right_pid);
    turn_to_heading(90, turn_pid);
    move(-1000, left_pid, right_pid);
    mogo.set(true);
    wait(0.2, sec);
    turn_to_heading(0, turn_pid);
    move(800, left_pid, right_pid);
    turn_to_heading(320, turn_pid);
    move(1840, left_pid, right_pid);
    turn_to_heading(350, turn_pid, 10000);
    move(1200, left_pid, right_pid);
    wait(0.3, sec);
    move(-1260, left_pid, right_pid);
    turn_to_heading(270, turn_pid);
    wait(0.5, sec);
    lb.move(29);
    move(1000, left_pid, right_pid, 1, 800);
    int counter = 0;
    while (true) {
        if (intake.velocity(rpm) < 10) {
            counter++;
        }
        else {
            counter = 0;
        }
        if (counter > 50) {
            break;
        }
        wait(20, msec);
    }
    intake.spin(reverse, 100, rpm);
    lb.move(160);
    wait(1.2, sec);
    lb.move(10);
    move(-600, left_pid, right_pid);
    lb.off();
    intake.spin(fwd, 600, rpm);
    turn_to_heading(180, turn_pid);
    move(1180, left_pid, right_pid);
    wait(0.5, sec);
    move(900, left_pid, right_pid);
    wait(0.5, sec);
    move(600, left_pid, right_pid);
    wait(0.5, sec);
    turn_to_heading(315, turn_pid);
    move(900, left_pid, right_pid, 1, 1000);
    turn_to_heading(20, turn_pid);
    mogo.set(false);
    intake.spin(reverse, 100, rpm);
    move(-800, left_pid, right_pid, 1, 800);
    move(400, left_pid, right_pid);
    turn_to_heading(270, turn_pid);
    intake.stop();
    move(-1500, left_pid, right_pid);
    turn_to_heading(276, turn_pid);
    move(-1900, left_pid, right_pid);
    wait(0.3, sec);
    move(-400, left_pid, right_pid, 1, 700);
    mogo.set(true);
    intake.spin(fwd, 600, rpm);
    turn_to_heading(358, turn_pid);
    move(900, left_pid, right_pid);
    turn_to_heading(30, turn_pid);
    move(1580, left_pid, right_pid);
    turn_to_heading(90, turn_pid);
    lb.move(29);
    move(1000, left_pid, right_pid, 1, 800);
    counter = 0;
    while (true) {
        if (intake.velocity(rpm) < 10) {
            counter++;
        }
        else {
            counter = 0;
        }
        if (counter > 50) {
            break;
        }
        wait(20, msec);
    }
    intake.spin(reverse, 100, rpm);
    lb.move(160);
    wait(1.2, sec);
    lb.move(10);
    move(-600, left_pid, right_pid);
    lb.off();
    intake.spin(fwd, 600, rpm);
    turn_to_heading(170, turn_pid);
    move(1180, left_pid, right_pid);
    wait(0.5, sec);
    move(900, left_pid, right_pid);
    wait(0.5, sec);
    move(600, left_pid, right_pid, 1, 800);
    wait(0.5, sec);
    turn_to_heading(45, turn_pid);
    move(900, left_pid, right_pid, 1, 800);
    turn_to_heading(315, turn_pid);
    mogo.set(false);
    intake.spin(reverse, 100, rpm);
    move(-800, left_pid, right_pid, 1, 800);
    move(400, left_pid, right_pid);
    turn_to_heading(348, turn_pid);
    intake.spin(fwd, 600, rpm);
    move(1500, left_pid, right_pid);
    move(1800, left_pid, right_pid);




}