#include "robot.h"
#include <math.h>

Robot::Robot(bool tether, controller* c) : rollerBack(0), leftMotorA(0), leftMotorB(0), rightMotorA(0), rightMotorB(0), 
leftIntake(0), rightIntake(0), turningWheel(0), yeet(0) {
  if (tether) {
    leftMotorA = motor(PORT1, ratio18_1, true);
    leftMotorB = motor(PORT5, ratio18_1, false);
    rightMotorA = motor(PORT3, ratio18_1, false);
    rightMotorB = motor(PORT4, ratio18_1, true);
    rollerBack = motor(PORT6, ratio18_1, false);
    yeet = motor(PORT7, ratio18_1, true);
    rightIntake = motor(PORT8, ratio6_1, true);
    leftIntake = motor(PORT10, ratio6_1, false);
    turningWheel = motor(PORT20, ratio18_1, true);
    driveType = ARCADE;
    turnTargetMultiplier = 14.1;
  } else {
    leftMotorA = motor(PORT12, ratio18_1, false);
    leftMotorB = motor(PORT16, ratio18_1, true);
    rightMotorA = motor(PORT13, ratio18_1, false);
    rightMotorB = motor(PORT14, ratio18_1, true);
    rollerBack = motor(PORT18, ratio18_1, false);
    yeet = motor(PORT19, ratio6_1, false);
    rightIntake = motor(PORT17, ratio6_1, true);
    leftIntake = motor(PORT11, ratio6_1, false);
    turningWheel = motor(PORT15, ratio18_1, true);
    driveType = ARCADE;
    turnTargetMultiplier = 14.1;
  }
  isTether = tether;
  
  robotController = c; 
}

void Robot::teleop() {
  robotController->Screen.clearScreen();
  int milliseconds = 0;

  bool L1 = robotController->ButtonL1.pressing();
  bool L2 = robotController->ButtonL2.pressing();
  bool R1 = robotController->ButtonR1.pressing();
  bool R2 = robotController->ButtonR2.pressing();
  bool A = robotController->ButtonA.pressing();

  float leftJoystick = (driveType == ARCADE) ? robotController->Axis3.position()^3 + robotController->Axis1.position()^3: robotController->Axis3.position()^3;
  float rightJoystick = (driveType == ARCADE) ? robotController->Axis3.position()^3 + robotController->Axis1.position()^3: robotController->Axis2.position()^3;

  if (fabs(leftJoystick) > 5) {
    float percent = (driveType == ARCADE) ? (pow((robotController->Axis3.position()/100.00f), 3.00f) + pow((robotController->Axis1.position()/100.00f), 5.00f))*100.00f : leftJoystick;
    leftMotorA.spin(forward, percent, percentUnits::pct);
    leftMotorB.spin(forward, percent, percentUnits::pct);
  } else {
    leftMotorA.stop();
    leftMotorB.stop();
  }

  if (fabs(rightJoystick) > 5) {
    float percent = (driveType == ARCADE) ? (pow((robotController->Axis3.position()/100.00f), 3.00f) - pow((robotController->Axis1.position()/100.00f), 5.00f))*100.00f : rightJoystick;
    rightMotorA.spin(forward, percent, percentUnits::pct);
    rightMotorB.spin(forward, percent, percentUnits::pct);
  } else {
    rightMotorA.stop();
    rightMotorB.stop();
  }

  if(driveType == ARCADE) { turningWheel.spin(reverse, pow((robotController->Axis1.position()/100.00f), 5.00f)*100.00f, pct); }

  if (isTether? L2 : L1) {
        rollerBack.spin(reverse, 100, percentUnits::pct);
        yeet.spin(reverse, 100, percentUnits::pct);
  }

  if (R1 || R2) {
    rightIntake.spin(R1 ? forward : reverse, 100, percentUnits::pct);
    rollerBack.spin(R1 ? forward : reverse, 100, percentUnits::pct);
    leftIntake.spin(R1 ? forward : reverse, 100, percentUnits::pct);
    yeet.spin(reverse, R1 ? 15 : 100, percentUnits::pct);
  }

  if (isTether? L1 : L2) {
    if (shootAllowed) {
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
      shootAllowed = true;
    }
  } else {
    shootAllowed = false;
  }

  if (!(L1 || L2 || R1 || R2 || A)) {
    rightIntake.stop(brakeType::coast);
    rollerBack.stop(brakeType::coast);
    leftIntake.stop(brakeType::coast);
    yeet.stop(brakeType::coast);
  }
}

void Robot::driveStraight(float percent, float dist, float accPercent) {
  float startPos = (leftMotorA.position(degrees) + rightMotorA.position(degrees)) / 2;
  float sumErr = 0;
  float target = 25.6 * fabs(dist);
  float currDist = 0;
  while (currDist < target) {
    float pidPercent = fabs(target - currDist) / target + sumErr * 0.001;
    pidPercent = std::max(-1.0f, std::min(1.0f, pidPercent));
    float modPercent = percent;
    if (fabs(currDist / target) < accPercent && percent > 5) {
      modPercent = 5 + fabs(currDist / (target * accPercent)) * (percent - 5);
    }
    currDist = fabs(((leftMotorA.position(degrees) + rightMotorA.position(degrees)) / 2) - startPos);
    sumErr = std::max(-100.0f, std::min(100.0f, sumErr + currDist));
    setLeftVelocity(dist > 0 ? forward : reverse, modPercent * pidPercent);
    setRightVelocity(dist > 0 ? forward : reverse, modPercent * pidPercent);
  }
  stopLeft();
  stopRight();
}

void Robot::driveTimed(float percent, float driveTime) {
  int milliseconds = vex::timer::system();
  while (vex::timer::system() < milliseconds + driveTime) {
    setLeftVelocity(forward, percent);
    setRightVelocity(forward, percent);
  }
  stopLeft();
  stopRight();
}

void Robot::driveStraight(float percent, float dist) {
  driveStraight(percent, dist, 0.1); //acc is from 0 to 1
}

void Robot::turnToAngle(float percent, float turnAngle) {
  float startPos = turningWheel.position(degrees);
  float currPos = startPos;
  float target = fabs(turnAngle * turnTargetMultiplier);
  float sumErr = 0;
  while (fabs(currPos - startPos) < target) {
    float currErrorP = fmin(1, fmax(-1, 2*(target - fabs(currPos - startPos)) / target) + sumErr*0.000001);
    sumErr += currErrorP;
    setLeftVelocity(turnAngle < 0 ? reverse : forward, currErrorP*percent/2.5);
    setRightVelocity(turnAngle < 0 ? forward : reverse, currErrorP*percent/2.5);
    turningWheel.spin(turnAngle > 0 ? reverse : forward, currErrorP*percent, percentUnits::pct);
    currPos = turningWheel.position(degrees);
  }
  turningWheel.stop();
  stopLeft();
  stopRight();
}

void Robot::startIntake() {
  rightIntake.spin(forward, 100, percentUnits::pct);
  rollerBack.spin(forward, 100, percentUnits::pct);
  leftIntake.spin(forward, 100, percentUnits::pct);
  yeet.spin(reverse, 15, percentUnits::pct);
}

void Robot::startOuttake() {
  rightIntake.spin(reverse, 50, percentUnits::pct);
  rollerBack.spin(reverse, 50, percentUnits::pct);
  leftIntake.spin(reverse, 50, percentUnits::pct);
  yeet.spin(reverse, 50, percentUnits::pct);
}

void Robot::stopIntake() {
  rightIntake.stop();
  rollerBack.stop();
  leftIntake.stop();
  yeet.stop();
}

void Robot::shoot(float shootTime) {
  int milliseconds = vex::timer::system();
  while(vex::timer::system() < milliseconds + 400) {
    yeet.spin(reverse, 100, percentUnits::pct);
    rollerBack.spin(reverse, 100, percentUnits::pct);
  }
  milliseconds = vex::timer::system();
  while(vex::timer::system() < milliseconds + shootTime) {
    yeet.spin(forward, 100, percentUnits::pct);
    rollerBack.spin(forward, 100, percentUnits::pct);
  }
  yeet.stop();
  rollerBack.stop();
}

void Robot::setLeftVelocity(directionType d, double percent) {
  leftMotorA.spin(d, percent, percentUnits::pct);
  leftMotorB.spin(d, percent, percentUnits::pct);
}

void Robot::setRightVelocity(directionType d, double percent) {
  rightMotorA.spin(d, percent, percentUnits::pct);
  rightMotorB.spin(d, percent, percentUnits::pct);
}

void Robot::stopLeft() {
  leftMotorA.stop();
  leftMotorB.stop();
}

void Robot::stopRight() {
  rightMotorA.stop();
  rightMotorB.stop();
}

