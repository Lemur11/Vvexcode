/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       simon                                                     */
/*    Created:      1/11/2025, 1:48:16 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "utils.h"
#include "devices.h"
#include "motions.h"
#include "autons.h"
#include "ladybrown.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  lb.initialize();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  ai.startAwb();
  wait(2, sec);
  // lb.move(29, false);
  // intake.spin(fwd, 12, volt);
  while (0) {
    // get readings
		double l_reading = left_motor.position(degrees);
		double r_reading = right_motor.position(degrees);
		
		//debug
		Brain.Screen.printAt(1, 100, "Left: %f\nRight: %f", l_reading, r_reading);
    Brain.Screen.printAt(1, 200, "Head: %f", imu.heading());

    wait(20, msec);
  }
  skills();
  while (true) {

    // driving
    float drive = deadband(controller(primary).Axis3.value(), 5);
    float turn = deadband(controller(primary).Axis1.value(), 5);
    left_motors.spin(fwd, to_volt(drive+turn), volt);
    right_motors.spin(fwd, to_volt(drive-turn), volt);

    // Take a snapshot of the red objects detected by 
    // the AI Vision Sensor.
    ai.takeSnapshot(Red);

    // Clear the screen/reset so that we can display 
    // new information.
    // Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    // Print the largest detected object's CenterX
    // coordinate to the Brain's screen.
    Brain.Screen.print("Angle: %f", ai.objects[0].angle);
    Brain.Screen.setCursor(1, 20);
    Brain.Screen.print("Area: %d", ai.objects[0].area);
    // Wait 0.5 seconds before repeating the loop and
    // taking a new snapshot.
    wait(20, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
//  while (true){ 
//   // Take a snapshot of the red objects detected by 
//   // the AI Vision Sensor.
//   ai.takeSnapshot(Red);

//   // Clear the screen/reset so that we can display 
//   // new information.
//   // Brain.Screen.clearScreen();
//   Brain.Screen.setCursor(1, 1);

//   // Print the largest detected object's CenterX
//   // coordinate to the Brain's screen.
//   Brain.Screen.print("Object Count: %d", ai.objectCount);
//   // Wait 0.5 seconds before repeating the loop and
//   // taking a new snapshot.
//   wait(20, msec);
// }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}