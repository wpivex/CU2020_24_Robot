#pragma once
#include "vex.h"

using namespace vex;
// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1(primary);
extern controller Controller2(controllerType::partner);

class Robot {
  public:
    Robot();
    motor rollerBack;
    motor leftMotorA;
    motor leftMotorB;
    motor rightMotorA;
    motor rightMotorB;
    motor leftIntake;
    motor rightIntake;
    motor yeet;

    motor_group LeftDriveSmart;
    motor_group RightDriveSmart;

    drivetrain Drivetrain;

    controller Controller1;
    controller Controller2;
    controller* robotController;

    void driveStraight(float percent, float dist);
    void driveStraight(float percent, float dist, float accPercent);
    void turnToAngle(float percent, float turnAngle);

    void userControl( void );
    void init( bool tether );
    int teleop( void );

    enum DriveType { ARCADE, TANK };
    DriveType driveType;
};