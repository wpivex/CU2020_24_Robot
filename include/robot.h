#pragma once
#include "vex.h"

using namespace vex;
// VEXcode devices

// extern controller Controller1;
// extern controller Controller2;

class Robot {
  public:
    Robot(bool tether, controller* c);
    motor rollerBack;
    motor leftMotorA;
    motor leftMotorB;
    motor rightMotorA;
    motor rightMotorB;
    motor leftIntake;
    motor rightIntake;
    motor turningWheel;
    motor yeet;

    controller* robotController;

    void driveStraight(float percent, float dist);
    void driveStraight(float percent, float dist, float accPercent);
    void driveTimed(float percent, float driveTime);
    void turnToAngle(float percent, float turnAngle);
    void startIntake();
    void stopIntake();
    void startOuttake();
    void shoot(float shootTime);

    void userControl( void );
    void teleop( void );
    void init();
    void setLeftVelocity(directionType d, double percent);
    void setRightVelocity(directionType d, double percent);
    void stopLeft();
    void stopRight();

    enum DriveType { ARCADE, TANK };
    DriveType driveType;
    bool shootAllowed = true;
    float turnTargetMultiplier;
};