#include "devices.h"
#include "utils.h"

using namespace vex;

brain Brain;
controller Controller;

motor left_motor = motor(PORT9, ratio6_1, true);
motor right_motor = motor(PORT11, ratio6_1);

// i wish i could discard these but...
motor a = motor(PORT10);
motor b = motor(PORT20, true);
motor c = motor(PORT12, true); 
motor d = motor(PORT1);

motor_group left_motors = motor_group(left_motor, a, b);
motor_group right_motors = motor_group(right_motor, c, d);

motor x = motor(PORT4, true);
motor y = motor(PORT17);
motor_group intake(x, y);
motor lady_brown(PORT16);

digital_out mogo(Brain.ThreeWirePort.A);
digital_out doinker(Brain.ThreeWirePort.B);

inertial imu(PORT2);

vex::aivision::colordesc Red(1, 219, 66, 29, 50, 1);
vex::aivision::colordesc Blue(2, 109, 246, 143, 10, 0.2);

rotation rot(PORT18);
distance intakeD(PORT14);
aivision ai(PORT16, Red);