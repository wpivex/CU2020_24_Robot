#include "robot.h"
#include <math.h>

void Robot::init(bool tether) {
  if (tether) {
    leftMotorA = motor(PORT1, ratio18_1, true);
    leftMotorB = motor(PORT5, ratio18_1, false);
    rightMotorA = motor(PORT3, ratio18_1, true);
    rightMotorB = motor(PORT4, ratio18_1, false);
    rollerBack = motor(PORT6, ratio18_1, false);
    yeet = motor(PORT7, ratio18_1, true);
    rightIntake = motor(PORT8, ratio6_1, true);
    leftIntake = motor(PORT10, ratio6_1, false);
    robotController = &Controller2;
    driveType = TANK;
  } else {
    leftMotorA = motor(PORT1, ratio18_1, true);
    leftMotorB = motor(PORT5, ratio18_1, false);
    rightMotorA = motor(PORT3, ratio18_1, true);
    rightMotorB = motor(PORT4, ratio18_1, false);
    rollerBack = motor(PORT6, ratio18_1, false);
    yeet = motor(PORT7, ratio18_1, true);
    rightIntake = motor(PORT8, ratio6_1, true);
    leftIntake = motor(PORT10, ratio6_1, false);
    robotController = &Controller1;
    driveType = ARCADE;
  }
  LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
  RightDriveSmart = motor_group(rightMotorA, rightMotorB);
  Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 3.25 * 3.14, 5, 8, inches, 84.0 / 60.0);
}

int Robot::teleop() {
  while (true) {
    bool shoot = false;
    int milliseconds = 0;

    bool stopLeft = true;
    bool stopRight = true;

    bool L1 = robotController->ButtonL1.pressing();
    bool L2 = robotController->ButtonL2.pressing();
    bool R1 = robotController->ButtonR1.pressing();
    bool R2 = robotController->ButtonR2.pressing();
    bool A = robotController->ButtonA.pressing();

    int leftSpeed = 10;  // robotController->Axis3.position()^3;
    int rightSpeed = 10; // robotController->Axis2.position()^3;

    if (abs(leftSpeed) <= 5) {
      if (stopLeft) {
        LeftDriveSmart.stop();
        stopLeft = false;
      }
    } else {
      stopLeft = true;
    }
    if (abs(rightSpeed) <= 5) {
      if (stopRight) {
        RightDriveSmart.stop();
        stopRight = false;
      }
    } else {
      stopRight = true;
    }

    if (!stopLeft) {
      if (driveType == ARCADE) {
        LeftDriveSmart.setVelocity((robotController->Axis3.value() ^
                                    3 + robotController->Axis1.value() ^ 3),
                                    velocityUnits::pct);
      } else if (driveType == TANK) {
        LeftDriveSmart.setVelocity(leftSpeed, velocityUnits::pct);
      }
      LeftDriveSmart.spin(forward);
    }
    if (!stopRight) {
      if (driveType == ARCADE) {
        RightDriveSmart.setVelocity((robotController->Axis3.value() ^
                                      3 - robotController->Axis1.value() ^ 3),
                                    velocityUnits::pct);
      } else if (driveType == TANK) {
        RightDriveSmart.setVelocity(rightSpeed, velocityUnits::pct);
      }
      RightDriveSmart.spin(forward);
    }

    if (L1 || L2) {
      leftIntake.spin(L1 ? reverse : forward, 100, percentUnits::pct);
      rightIntake.spin(L1 ? forward : reverse, 100, percentUnits::pct);
    }

    if (R1 || R2) {
      rightIntake.spin(R1 ? forward : reverse, 100, percentUnits::pct);
      rollerBack.spin(R1 ? forward : reverse, 100, percentUnits::pct);
      leftIntake.spin(R1 ? forward : reverse, 100, percentUnits::pct);
      yeet.spin(reverse, R1 ? 15 : 100, percentUnits::pct);
    }

    if (A) {
      if (shoot) {
        if (vex::timer::system() > milliseconds + 100) {
          yeet.spin(forward, 100, percentUnits::pct);
          rollerBack.spin(forward, 100, percentUnits::pct);
        } else {
          rightIntake.spin(reverse, 100, percentUnits::pct);
          rollerBack.spin(reverse, 100, percentUnits::pct);
          leftIntake.spin(reverse, 100, percentUnits::pct);
          yeet.spin(reverse, 100, percentUnits::pct);
        }
      } else {
        milliseconds = vex::timer::system();
        shoot = true;
      }
    } else {
      shoot = false;
    }

    if (!(L1 || L2 || R1 || R2 || A)) {
      rightIntake.stop(brakeType::coast);
      rollerBack.stop(brakeType::coast);
      leftIntake.stop(brakeType::coast);
      yeet.stop(brakeType::coast);
    }

    wait(20, msec);
  }
  return 0;
}

void Robot::driveStraight(float percent, float dist, float accPercent) {
  float startPos =
      (LeftDriveSmart.position(degrees) + RightDriveSmart.position(degrees)) /
      2;
  float currPos =
      (LeftDriveSmart.position(degrees) + RightDriveSmart.position(degrees)) /
      2;
  float sumErr = 0;
  float target = 25.6 * dist;
  float currDist = currPos - startPos;
  while (currDist < target) {
    float pidPercent = (target - currDist) / target + sumErr * 0.001;
    pidPercent = std::max(-1.0f, std::min(1.0f, pidPercent));
    float modPercent = percent;
    if (currDist < accPercent && percent > 5) {
      modPercent = 5 + currDist / accPercent * (percent - 5);
    }
    RightDriveSmart.setVelocity(modPercent * pidPercent, percentUnits::pct);
    RightDriveSmart.spin(forward);
    LeftDriveSmart.setVelocity(modPercent * pidPercent, percentUnits::pct);
    LeftDriveSmart.spin(forward);
    currDist = ((LeftDriveSmart.position(degrees) +
                 RightDriveSmart.position(degrees)) /
                2) -
               startPos;
    sumErr = std::max(-100.0f, std::min(100.0f, sumErr + currDist));
    Controller2.Screen.clearScreen();
    Controller2.Screen.setCursor(0, 0);
    Controller2.Screen.print(currDist);
  }
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
}

void Robot::driveStraight(float percent, float dist) {
  driveStraight(percent, dist, 10.0);
}

void Robot::turnToAngle(float percent, float turnAngle) {
  // left is positive, ew
  motor_group accurateSide = turnAngle > 0
                                 ? RightDriveSmart
                                 : LeftDriveSmart; // this is super cursed help
  // motor_group badSide = turnAngle > 0 ? LeftDrive2Smart : RightDrive2Smart;
  float startPos = accurateSide.position(degrees);
  // float badStartPos = badSide.position(degrees);
  float currPos = accurateSide.position(degrees);
  float target = abs(turnAngle * 3);
  while (abs(currPos - startPos) < target) {
    RightDriveSmart.setVelocity(percent, percentUnits::pct);
    RightDriveSmart.spin(turnAngle < 0 ? reverse : forward);
    LeftDriveSmart.setVelocity(percent, percentUnits::pct);
    LeftDriveSmart.spin(turnAngle < 0 ? forward : reverse);
    currPos = accurateSide.position(degrees);
  }
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
}

void Robot::userControl(void) {
  vex::task controlLoop(Robot::teleop);
}