#pragma once
#include "vex.h"

using namespace vex;
// VEXcode devices

extern controller Controller1;
extern controller Controller2;

class Robot {
  public:
    Robot(bool tether);
    motor rollerBack;
    motor leftMotorA;
    motor leftMotorB;
    motor rightMotorA;
    motor rightMotorB;
    motor leftIntake;
    motor rightIntake;
    motor yeet;

    controller Controller1;
    controller Controller2;

    motor_group LeftDriveSmart;
    motor_group RightDriveSmart;

    controller* robotController;

    void driveStraight(float percent, float dist);
    void driveStraight(float percent, float dist, float accPercent);
    void turnToAngle(float percent, float turnAngle);

    void userControl( void );
    void teleop( void );

    enum DriveType { ARCADE, TANK };
    DriveType driveType;
};