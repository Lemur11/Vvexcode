#include "vex.h"
#include "devices.h"
#include "pid.h"
#include "utils.h"

PID aiPID(0.1, 0.0, 0.0);

void move(float target, PID &left_pid, PID &right_pid, int units, int timeout, int exit_dist) {
    target = target * units;

	// reset motor encoder readings
	left_motor.resetPosition();
	right_motor.resetPosition();

	// debug
	printf("Target: %f\n", target); 

	// get initial readings and set prev err
	float l_reading = left_motor.position(degrees);
	float r_reading = right_motor.position(degrees);
	left_pid.set_prev(target - l_reading);
	right_pid.set_prev(target - r_reading);
	
	// loop
	Brain.Timer.clear();
	while (true) {
		// exit condition
		if (exit_dist != 0) {
			if (fabs((l_reading + r_reading)/2 - target) < exit_dist) {
				break;
			}
		}

		if (Brain.Timer.time(msec) > timeout) {
			break;
		}

		if (fabs((l_reading + r_reading)/2 - target) < 20 && fabs(left_pid.get_deriv()) < 0.2 && fabs(right_pid.get_deriv()) < 0.2) {
			break;
		}
		// get readings
		l_reading = left_motor.position(degrees);
		r_reading = right_motor.position(degrees);
		
		//debug
		Brain.Screen.printAt(1, 100, "Left: %f\nRight: %f", l_reading, r_reading);

		// pid calc and move
		left_motors.spin(fwd, left_pid.cycle(target, l_reading), voltageUnits::volt);
		right_motors.spin(fwd, right_pid.cycle(target, r_reading), voltageUnits::volt);

		wait(20, msec);
	};
	// stop motors
	left_motors.stop();
	right_motors.stop();
}


void turn(float degrees, PID &turn_pid, int timeout) {
	printf("Turning\n");
	float turn_factor = 1;
	
	// initial readings
	float reading = (float)imu.heading();
	float target = target_cal(reading + degrees);
	printf("Target: %f\n", target);
	float err = wrap(target, reading);
	
	// set pid prev error to prevent massive deriv at start
	turn_pid.set_prev(-err);

	float turn_vol;

	Brain.Timer.clear();
	while (true) {
		// loop end control
		if (Brain.Timer.time(msec) > timeout) {
			break;
		}

		if (fabs(err) < 1 && fabs(turn_pid.get_deriv()) < 0.5) {
			break;
		}
		// get heading
		reading = (float)imu.heading();
		Brain.Screen.printAt(1, 100, "HEAD: %f", reading);

		// if dc imu stop turning
		if (!imu.installed()) {
			Brain.Screen.printAt(1, 500, "IMU ERR");
			break;
		}
		// pid calculation
		err = wrap(target, reading);
		turn_vol = turn_pid.cycle(0, err);


		// move motors
		left_motors.spin(fwd, -turn_vol * turn_factor, voltageUnits::volt);
		right_motors.spin(fwd, turn_vol * turn_factor, voltageUnits::volt);

		wait(60, msec);
	}
	// stop motors
	left_motors.stop();
	right_motors.stop();
}

void turn_to_heading(float degrees, PID &turn_pid, int timeout, float turn_factor) {
	printf("Turning\n");
	// float turn_factor = 1;
	
	// initial readings
	float reading = (float)imu.heading();
    float target = degrees;
	printf("Target: %f\n", target);
	float err = wrap(target, reading); 
	
	// set pid prev error to prevent massive deriv at start
	turn_pid.set_prev(-err);

	float turn_vol;

	Brain.Timer.clear();
	while (true) {
		// loop end control
		if (Brain.Timer.time(msec) > timeout) {
			break;
		}

		if (fabs(err) < 2 && fabs(turn_pid.get_deriv()) < 0.5) {
			break;
		}
		// get heading
		reading = (float)imu.heading();
		Brain.Screen.printAt(1, 100, "HEAD: %f", reading);

		// if dc imu stop turning
		if (!imu.installed()) {
			Brain.Screen.printAt(1, 500, "IMU ERR");
			break;
		}
		// pid calculation
		err = wrap(target, reading);
		turn_vol = turn_pid.cycle(0, err);


		// move motors
		left_motors.spin(fwd, -turn_vol * turn_factor, voltageUnits::volt);
		right_motors.spin(fwd, turn_vol * turn_factor, voltageUnits::volt);

		wait(60, msec);
	}
	// stop motors
	left_motors.stop();
	right_motors.stop();
}

void aiTurn(float degrees, PID &turn_pid, int timeout, aivision::colordesc& desc) {
    printf("Turning\n");
	float turn_factor = 1;
	
	// initial readings
	float reading = (float)imu.heading();
	float target = target_cal(reading + degrees);
	printf("Target: %f\n", target);
	float err = wrap(target, reading);
	
	// set pid prev error to prevent massive deriv at start
	turn_pid.set_prev(-err);

	float turn_vol;

	Brain.Timer.clear();
	while (true) {
		// loop end control
		if (Brain.Timer.time(msec) > timeout) {
			break;
		}

		if (fabs(err) < 12) {break;}
		// get heading
		reading = (float)imu.heading();
		Brain.Screen.printAt(1, 100, "HEAD: %f", reading);

		// if dc imu stop turning
		if (!imu.installed()) {
			Brain.Screen.printAt(1, 500, "IMU ERR");
			break;
		}
		// pid calculation
		err = wrap(target, reading);
		turn_vol = turn_pid.cycle(0, err);


		// move motors
		left_motors.spin(fwd, -turn_vol * turn_factor, voltageUnits::volt);
		right_motors.spin(fwd, turn_vol * turn_factor, voltageUnits::volt);

		wait(60, msec);
	}
    ai.takeSnapshot(desc);
    if (ai.objects[0].exists == true) {
        // err = ai.objects[0].angle;
    }
    else {
        left_motors.stop();
        right_motors.stop(); 
        return;
    }
    // aiPID.set_prev(-err);
    while (true) {
        ai.takeSnapshot(desc);
        err = ai.objects[0].angle;

        // loop end control
		if (Brain.Timer.time(msec) > timeout) {
			break;
		}

		if (fabs(90-err) < 5) {
			break;
		}
		else if (err > 95) {
			left_motors.spin(fwd, -100, voltageUnits::volt);
        	right_motors.spin(fwd, 100, voltageUnits::volt);
		}
		else {
			left_motors.spin(fwd, 100, voltageUnits::volt);
        	right_motors.spin(fwd, -100, voltageUnits::volt);
		}

        // move motors
        left_motors.spin(fwd, -turn_vol * turn_factor, voltageUnits::volt);
        right_motors.spin(fwd, turn_vol * turn_factor, voltageUnits::volt);

        wait(20, msec);
    }
	// stop motors
	left_motors.stop();
	right_motors.stop();
}