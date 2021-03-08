#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
#ifdef BASE1
  motor leftMotorA = motor(PORT1, ratio18_1, true);
  motor leftMotorB = motor(PORT2, ratio18_1, false);
  motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

  motor rightMotorA = motor(PORT17, ratio18_1, true);
  motor rightMotorB = motor(PORT18, ratio18_1, false);
  motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

  motor leftIntake = motor(PORT15, ratio6_1, true);

  motor rollerBack = motor(PORT14, ratio6_1, true);

  motor yeet = motor(PORT3,ratio6_1,true);
#else
  motor leftMotorA = motor(PORT1, ratio18_1, true);
  motor leftMotorB = motor(PORT2, ratio18_1, false);
  motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

  motor rightMotorA = motor(PORT9, ratio18_1, false);
  motor rightMotorB = motor(PORT10, ratio18_1, true);
  motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

  motor leftIntake = motor(PORT12, ratio6_1, true);

  motor rollerBack = motor(PORT19, ratio6_1, true);

  motor yeet = motor(PORT5,ratio6_1,false);
#endif

motor rightIntake = motor(PORT20, ratio6_1, true);


                                  // Left             Right           WHeel Circumfernece , Wheel base, Wheel Track, Units, Gear ratio
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 3.25*3.14, 5, 8, inches, 84.0/60.0);
controller Controller1 = controller(primary);


// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position()^3;
      int drivetrainRightSideSpeed = Controller1.Axis2.position()^3;
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }

    bool isActionIntake = false;

    if(Controller1.ButtonL1.pressing()){
      leftIntake.spin(reverse, 100, percentUnits::pct);
      rightIntake.spin(forward, 100, percentUnits::pct);

      isActionIntake = true;
    }else if (Controller1.ButtonL2.pressing()) {
      rightIntake.spin(reverse, 100, percentUnits::pct);
      leftIntake.spin(forward, 100, percentUnits::pct);

      isActionIntake = true;
    }

    if(Controller1.ButtonR1.pressing()){
      rightIntake.spin(forward, 100, percentUnits::pct);
      rollerBack.spin(forward, 100, percentUnits::pct);
      leftIntake.spin(forward, 100, percentUnits::pct);
      isActionIntake = true;
    }else if (Controller1.ButtonR2.pressing()) {
      rightIntake.spin(reverse, 100, percentUnits::pct);
      rollerBack.spin(reverse, 100, percentUnits::pct);
      leftIntake.spin(reverse, 100, percentUnits::pct);
      isActionIntake = true;
    }
    
    //If no intake button pressed, stop all intake motors
    if(!isActionIntake){
      rightIntake.stop(brakeType::coast);
      rollerBack.stop(brakeType::coast);
      leftIntake.stop(brakeType::coast);
    }

    if(Controller1.ButtonA.pressing())
      yeet.spin(forward,100,percentUnits::pct);
    else
      yeet.stop(brakeType::hold);

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}