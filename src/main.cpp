#include "../include/robot.cpp"

competition Competition;
controller Controller1(controllerType::primary);
controller Controller2(controllerType::partner);

Robot* mainBotP;
Robot* tetherBotP;

int mainTeleop() {
  while(true) {
    mainBotP->teleop();
    // task::sleep(10);
    tetherBotP->teleop();
    // task::sleep(10);
  }
  return 0;
}

void userControl(void) {
  task controlLoop1(mainTeleop);
}

int mainAuto(void) {
  this_thread::sleep_for(10);
  mainBotP->driveStraight(30, 26);
  mainBotP->turnToAngle(90, 65);
  mainBotP->startIntake();
  mainBotP->driveTimed(30, 2500);
  mainBotP->driveStraight(30, -3);
  mainBotP->driveTimed(30, 500);
  mainBotP->driveStraight(30, -3);
  mainBotP->driveTimed(30, 500);
  this_thread::sleep_for(1000);
  mainBotP->stopIntake();
  mainBotP->shoot(2000);
  mainBotP->shoot(2000);
  mainBotP->startOuttake();
  mainBotP->driveStraight(30, -12);
  mainBotP->turnToAngle(100, -53);
  mainBotP->startIntake();
  mainBotP->driveStraight(40, 63);
  mainBotP->stopIntake();
  return 0;
}

int tetherAuto(void) {
  this_thread::sleep_for(8000);
  tetherBotP->driveStraight(30, 24);
  tetherBotP->turnToAngle(20, -129);
  tetherBotP->startIntake();
  tetherBotP->driveTimed(30, 2000);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->stopIntake();
  tetherBotP->shoot(700);
  tetherBotP->shoot(700);
  tetherBotP->driveStraight(30, -30);
  tetherBotP->startOuttake();
  tetherBotP->turnToAngle(100, 60);
  tetherBotP->stopIntake();
  tetherBotP->startIntake();
  tetherBotP->driveTimed(30, 3000);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 500);
  tetherBotP->stopIntake();
  tetherBotP->driveStraight(30, -6);
  tetherBotP->startIntake();
  tetherBotP->driveStraight(30, 6);
  this_thread::sleep_for(1000);
  tetherBotP->stopIntake();
  tetherBotP->shoot(700);
  return 0;
}

void autonomous() {
  thread auto2(tetherAuto);
  thread auto1(mainAuto);
  // std::thread auto2(tetherAuto);
  // std::thread auto1(mainAuto);
  // task auto1(mainAuto);
  // task auto2(tetherAuto);
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
