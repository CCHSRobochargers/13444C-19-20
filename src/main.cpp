/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LDM                  motor         11
// RDM                  motor         20
// LLM                  motor         2
// RLM                  motor         9
// LFM                  motor         3
// RFM                  motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
// define your global instances of motors and other devices here
motor_group LiftMotors = motor_group(LLM, RLM);
motor_group FlapperMotors = motor_group(LFM, RFM);


  int wheeldiameter = 4; //this is the diameter of the wheels in inches
  double wheelcircumference = 3.1415 * wheeldiameter; // this is the approximate circumference of the wheels in inches
  void drive (double inches) {
    //math to convert how far we want to go to how into how far the motors turn
    double rotations = inches / wheelcircumference;
    //a positive inches value causes the robot to move forward, while a negative value makes the robot reverse
    
    LDM.spinFor(rotations, turns, false); //bool waitforcompletion is set to false so that both motors will run at once
    RDM.spinFor(rotations, turns);

    //reset motor positions so it doesnt mess us up later
    //I actually dont think it matters but better safe than sorry I guess
    LDM.setPosition(0, turns);
    RDM.setPosition(0, turns);
  }

  double turndiameter = 16.0625; //this is the approximate distance between the wheels, which is the diameter of the circle around which the motors will turn
  double turncircumference = turndiameter * 3.1415; //this is the approximate circumference of the circle the robot turns around
  void turn (int degreestoturn) {
    double rotations = degreestoturn / 360 * turncircumference / wheelcircumference; //maths to convert the amount of degrees we want to turn to a value of rotations for the motors
    LDM.spinFor(rotations, turns, false);
    //the right motor must turn the opposite way or the robot will drive straight
    RDM.spinFor(-1 * rotations, turns);

    //a positive value of degreestoturn causes the left motor to go forward and the right motor in reverse
    //thus, a positive value will cause a clockwise turn, and a negative value a counterclockwise turn

    LDM.setPosition(0, turns);
    RDM.setPosition(0, turns); //again, resetting the motor even though I'm not sure it's necessary
  }
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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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

  drive(30);

  drive(-12);
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
  Brain.Screen.print("Absolutly No pressure Drive to win :) ");
  LDM.setVelocity(50, vex::velocityUnits::pct);
  RDM.setVelocity(50, vex::velocityUnits::pct);

  LiftMotors.setStopping(hold);
  FlapperMotors.setStopping(hold);
  // Create an infinite loop so that the program can pull remote control values
  // every iteration. This loop causes the program to run forever.
  while (1) {

    // Drive Control
    // Set the left and right motor to spin forward using the controller's Axis
    // positions as the velocity value.
    if (Controller1.Axis3.position() < 10 && Controller1.Axis3.position() > -10) {
      LDM.stop();
    } 
    else {
    LDM.spin(vex::directionType::fwd, Controller1.Axis3.position(),
             vex::velocityUnits::pct);
    }
    if (Controller1.Axis2.position() < 10 && Controller1.Axis2.position() > -10) {
    RDM.stop();
    }
    else {
    RDM.spin(vex::directionType::fwd, Controller1.Axis2.position(),
             vex::velocityUnits::pct);
    }         

    if (Controller1.ButtonR1.pressing()) {
      LiftMotors.spin(forward);
    } else if (Controller1.ButtonR2.pressing()) {
      LiftMotors.spin(reverse);
    } else {
      LiftMotors.stop();
    }

    if (Controller1.ButtonL1.pressing()) {
      FlapperMotors.spin(forward);
    } else if (Controller1.ButtonL2.pressing()) {
      FlapperMotors.spin(reverse);
    } else {
      FlapperMotors.stop();
    }

    // Sleep the task for a short amount of time to prevent wasted resources.
    vex::task::sleep(20);
  }
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
