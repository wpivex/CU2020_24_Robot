#pragma once
#include "vex.h"

using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern controller Controller2;

motor rollerBack(PORT18, ratio6_1, false);
// A global instance of brain used for printing to the V5 Brain screen

// VEXcode device constructors
motor leftMotorA(PORT11, ratio18_1, false);
motor leftMotorB(PORT12, ratio18_1, true);

motor rightMotorA(PORT13, ratio18_1, false);
motor rightMotorB(PORT14, ratio18_1, true);

motor_group LeftDriveSmart(leftMotorA, leftMotorB);
motor_group RightDriveSmart(rightMotorA, rightMotorB);

motor leftIntake(PORT16, ratio6_1, false);
motor rightIntake(PORT17, ratio6_1, true);

motor yeet(PORT19, ratio6_1, false);

motor leftMotorADrive2(PORT1, ratio18_1, true);  // 11
motor leftMotorBDrive2(PORT5, ratio18_1, false); // 12
motor_group LeftDrive2Smart(leftMotorADrive2, leftMotorBDrive2);

motor rightMotorADrive2(PORT3, ratio18_1, true);
motor rightMotorBDrive2(PORT4, ratio18_1, false);
motor_group RightDrive2Smart(rightMotorADrive2, rightMotorBDrive2);

// Left             Right           WHeel Circumfernece , Wheel base, Wheel
// Track, Units, Gear ratio
drivetrain Drivetrain(LeftDriveSmart, RightDriveSmart, 3.25 * 3.14, 5, 8, inches, 84.0 / 60.0);
drivetrain Drivetrain2(LeftDrive2Smart, RightDrive2Smart,3.25 * 3.14, 5, 8, inches, 84.0 / 60.0);

motor rollerBack2(PORT6, ratio18_1, false);
motor yeet2(PORT7, ratio18_1, true); // 20

motor rightIntake2(PORT8, ratio6_1, true);
motor leftIntake2(PORT10, ratio6_1, false);

controller Controller1(primary);
controller Controller2(controllerType::partner);

void driveStraight(float percent, float dist);
void turnToAngle(float percent, float turnAngle);

void userControl( void );