#include "robot-config.h"

bool shoot = false;
int milliseconds = 0;

bool shoot2 = false;
int milliseconds2 = 0;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool DrivetrainLNeedsToBeStopped_Controller2 = true;
bool DrivetrainRNeedsToBeStopped_Controller2 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while (true) {
    if (RemoteControlCodeEnabled) {
      // Control Base 1:
      //--------------------------------------------//

      // calculate the drivetrain motor velocities from the controller joystick
      // axies left = Axis3 right = Axis2
      int drivetrainLeftSideSpeed = 10;  // Controller1.Axis3.position()^3;
      int drivetrainRightSideSpeed = 10; // Controller1.Axis2.position()^3;

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
        // reset the toggle so that the deadband code knows to stop the left
        // motor next time the input is in the deadband range
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
        // reset the toggle so that the deadband code knows to stop the right
        // motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }

      // only tell the left drive motor to spin if the values are not in the
      // deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        // Arcade
        LeftDriveSmart.setVelocity(
            (Controller1.Axis3.value() ^ 3 + Controller1.Axis1.value() ^ 3),
            velocityUnits::pct); //(Axis3+Axis4)/2;
        // LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the
      // deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(
            (Controller1.Axis3.value() ^ 3 - Controller1.Axis1.value() ^ 3),
            velocityUnits::pct); //(Axis3-Axis4)/2;

        // RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }

      // Control Base 2:
      //--------------------------------------------//

      // calculate the drivetrain motor velocities from the controller joystick
      // axies left = Axis3 right = Axis2
      drivetrainLeftSideSpeed = Controller2.Axis3.position() ^ 3;
      drivetrainRightSideSpeed = Controller2.Axis2.position() ^ 3;

      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller2) {
          // stop the left drive motor
          LeftDrive2Smart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller2 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left
        // motor next time the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller2 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller2) {
          // stop the right drive motor
          RightDrive2Smart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller2 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right
        // motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller2 = true;
      }

      // only tell the left drive motor to spin if the values are not in the
      // deadband range
      if (DrivetrainLNeedsToBeStopped_Controller2) {
        LeftDrive2Smart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDrive2Smart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the
      // deadband range
      if (DrivetrainRNeedsToBeStopped_Controller2) {
        RightDrive2Smart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDrive2Smart.spin(forward);
      }
    }

    bool isActionIntake = false;

    if (Controller1.ButtonL1.pressing()) {
      leftIntake.spin(reverse, 100, percentUnits::pct);
      rightIntake.spin(forward, 100, percentUnits::pct);

      isActionIntake = true;
    } else if (Controller1.ButtonL2.pressing()) {
      rightIntake.spin(reverse, 100, percentUnits::pct);
      leftIntake.spin(forward, 100, percentUnits::pct);

      isActionIntake = true;
    }

    if (Controller1.ButtonR1.pressing()) {
      rightIntake.spin(forward, 100, percentUnits::pct);
      rollerBack.spin(forward, 100, percentUnits::pct);
      leftIntake.spin(forward, 100, percentUnits::pct);
      yeet.spin(reverse, 15, percentUnits::pct);
      isActionIntake = true;
    } else if (Controller1.ButtonR2.pressing()) {
      rightIntake.spin(reverse, 100, percentUnits::pct);
      rollerBack.spin(reverse, 100, percentUnits::pct);
      leftIntake.spin(reverse, 100, percentUnits::pct);
      yeet.spin(reverse, 100, percentUnits::pct);
      isActionIntake = true;
    }

    if (Controller1.ButtonA.pressing()) {
      if (shoot) {
        if (vex::timer::system() > milliseconds + 100) {
          yeet.spin(forward, 100, percentUnits::pct);
          rollerBack.spin(forward, 100, percentUnits::pct);
          isActionIntake = true;
        } else {
          rightIntake.spin(reverse, 100, percentUnits::pct);
          rollerBack.spin(reverse, 100, percentUnits::pct);
          leftIntake.spin(reverse, 100, percentUnits::pct);
          yeet.spin(reverse, 100, percentUnits::pct);
          isActionIntake = true;
        }
      } else {
        milliseconds = vex::timer::system();
        shoot = true;
        isActionIntake = true;
      }
    } else {
      shoot = false;
    }

    // If no intake button pressed, stop all intake motors
    if (!isActionIntake) {
      rightIntake.stop(brakeType::coast);
      rollerBack.stop(brakeType::coast);
      leftIntake.stop(brakeType::coast);
      yeet.stop(brakeType::coast);
    }

    isActionIntake = false;

    if (Controller2.ButtonR1.pressing()) {
      rightIntake2.spin(forward, 100, percentUnits::pct);
      rollerBack2.spin(forward, 100, percentUnits::pct);
      leftIntake2.spin(forward, 100, percentUnits::pct);
      yeet2.spin(reverse, 15, percentUnits::pct);
      isActionIntake = true;
    } else if (Controller2.ButtonR2.pressing()) {
      rightIntake2.spin(reverse, 100, percentUnits::pct);
      rollerBack2.spin(reverse, 100, percentUnits::pct);
      leftIntake2.spin(reverse, 100, percentUnits::pct);
      yeet2.spin(reverse, 100, percentUnits::pct);
      isActionIntake = true;
    }

    if (Controller2.ButtonA.pressing()) {
      if (shoot2) {
        if (vex::timer::system() > milliseconds2 + 100) {
          yeet2.spin(forward, 100, percentUnits::pct);
          rollerBack2.spin(forward, 100, percentUnits::pct);
          isActionIntake = true;
        } else {
          rightIntake2.spin(reverse, 100, percentUnits::pct);
          rollerBack2.spin(reverse, 100, percentUnits::pct);
          leftIntake2.spin(reverse, 100, percentUnits::pct);
          yeet2.spin(reverse, 100, percentUnits::pct);
          isActionIntake = true;
        }
      } else {
        milliseconds2 = vex::timer::system();
        shoot2 = true;
        isActionIntake = true;
      }
    } else {
      shoot2 = false;
    }

    // If no intake button pressed, stop all intake motors
    if (!isActionIntake) {
      rightIntake2.stop(brakeType::coast);
      rollerBack2.stop(brakeType::coast);
      leftIntake2.stop(brakeType::coast);
      yeet2.stop(brakeType::coast);
    }

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

void driveStraight(float percent, float dist) {
  float startPos = (LeftDrive2Smart.position(degrees) + RightDrive2Smart.position(degrees)) / 2;
  float currPos = (LeftDrive2Smart.position(degrees) + RightDrive2Smart.position(degrees)) / 2;
  while(currPos-startPos < dist*24) {
    RightDrive2Smart.setVelocity(percent*(dist*24-currPos+startPos)/(dist*24), percentUnits::pct);
    RightDrive2Smart.spin(forward);
    LeftDrive2Smart.setVelocity(percent*(dist*24-currPos+startPos)/(dist*24), percentUnits::pct);
    LeftDrive2Smart.spin(forward);
    currPos = (LeftDrive2Smart.position(degrees) + RightDrive2Smart.position(degrees)) / 2;
  }
  RightDrive2Smart.stop();
  LeftDrive2Smart.stop();
}

void turnToAngle(float percent, float turnAngle) {
  //left is positive, ew
  float startPos = RightDrive2Smart.position(degrees) / 2;
  float currPos = RightDrive2Smart.position(degrees) / 2;
  float target = abs(turnAngle*1.2);
  while(abs(currPos-startPos) < target) {
    Controller2.Screen.clearScreen();
    Controller2.Screen.setCursor(0, 0);
    Controller2.Screen.print(currPos-startPos);
    RightDrive2Smart.setVelocity(percent, percentUnits::pct);
    RightDrive2Smart.spin(turnAngle > 0 ? reverse : forward);
    LeftDrive2Smart.setVelocity(percent, percentUnits::pct);
    LeftDrive2Smart.spin(turnAngle > 0 ? forward : reverse);
    currPos = RightDrive2Smart.position(degrees) / 2;
  }
  RightDrive2Smart.stop();
  LeftDrive2Smart.stop();
}

void userControl(void) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}