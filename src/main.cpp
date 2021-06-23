#include "../include/robot.cpp"

competition Competition;
controller Controller1(controllerType::primary);
controller Controller2(controllerType::partner);

Robot* mainBotP;
Robot* tetherBotP;

int mainTeleop() {
  while(true) {
    mainBotP->teleop();
    tetherBotP->teleop();
  }
  return 0;
}

void userControl(void) {
  task controlLoop1(mainTeleop);
}

int mainAuto(void) {
  mainBotP->driveStraight(40, 36);
  // this_thread::sleep_for(10);
  // mainBotP->driveStraight(30, 26);
  // mainBotP->turnToAngle(60, -77);
  // mainBotP->startIntake();
  // mainBotP->driveTimed(30, 2500);
  // mainBotP->driveStraight(30, -3);
  // mainBotP->driveTimed(30, 500);
  // mainBotP->driveStraight(30, -3);
  // mainBotP->driveTimed(30, 500);
  // this_thread::sleep_for(1000);
  // mainBotP->stopIntake();
  // mainBotP->shoot(1000);
  // mainBotP->shoot(1000);
  // mainBotP->startOuttake();
  // mainBotP->driveStraight(30, -12);
  // mainBotP->turnToAngle(60, 55);
  // mainBotP->startIntake();
  // mainBotP->driveStraight(40, 56);
  // mainBotP->stopIntake();
  return 0;
}

int tetherAuto(void) {
  tetherBotP->driveStraight(40, 36);
  // this_thread::sleep_for(8000);
  // tetherBotP->driveStraight(30, 24);
  // tetherBotP->turnToAngle(60, 77);
  // tetherBotP->startIntake();
  // tetherBotP->driveTimed(30, 3000);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->stopIntake();
  // tetherBotP->shoot(1000);
  // tetherBotP->shoot(1000);
  // tetherBotP->startOuttake();
  // tetherBotP->driveStraight(30, -30);
  // tetherBotP->turnToAngle(60, -55);
  // tetherBotP->stopIntake();
  // tetherBotP->startIntake();
  // tetherBotP->driveTimed(30, 3000);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->driveStraight(30, -5);
  // tetherBotP->driveTimed(30, 500);
  // tetherBotP->stopIntake();
  // tetherBotP->driveStraight(30, -6);
  // tetherBotP->startIntake();
  // tetherBotP->driveStraight(30, 6);
  // this_thread::sleep_for(1000);
  // tetherBotP->stopIntake();
  // tetherBotP->shoot(1000);
  return 0;
}

void autonomous() {
  thread auto2(tetherAuto);
  thread auto1(mainAuto);
}

void pre_auton() {
  
}

int main() {
  Robot mainBot = Robot(false, &Controller1);
  Robot tetherBot = Robot(true, &Controller2);
  mainBotP = &mainBot;
  tetherBotP = &tetherBot;
  //All the control code is in robot config, that seems to be the new template
  //Auton and other non-controller stuff can go here
    // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
