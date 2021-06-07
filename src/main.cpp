/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       kohmeikadoya                                              */
/*    Created:      Mon Nov 09 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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
  // this_thread::sleep_for(10);
  // mainBotP->driveStraight(30, 26);
  // mainBotP->turnToAngle(15, 121);
  // mainBotP->startIntake();
  // mainBotP->driveTimed(30, 3500);
  // this_thread::sleep_for(2000);
  // mainBotP->stopIntake();
  // mainBotP->shoot(900);
  // mainBotP->startOuttake();
  // mainBotP->driveStraight(30, -12);
  // mainBotP->turnToAngle(15, -87);
  // mainBotP->startIntake();
  // mainBotP->driveStraight(40, 57);
  // mainBotP->stopIntake();
  return 0;
}

int tetherAuto(void) {
  tetherBotP->driveStraight(30, 24);
  tetherBotP->turnToAngle(20, -120);
  tetherBotP->startIntake();
  tetherBotP->driveTimed(30, 2000);
  this_thread::sleep_for(2000);
  tetherBotP->stopIntake();
  tetherBotP->shoot(900);
  tetherBotP->startOuttake();
  tetherBotP->driveStraight(30, -30);
  tetherBotP->stopIntake();
  tetherBotP->turnToAngle(20, 78);
  tetherBotP->startIntake();
  tetherBotP->driveTimed(30, 3000);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 0.5);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 0.5);
  tetherBotP->driveStraight(30, -3);
  tetherBotP->driveTimed(30, 0.5);
  tetherBotP->stopIntake();
  tetherBotP->driveStraight(30, -6);
  tetherBotP->turnToAngle(10, -60);
  tetherBotP->shoot(600);
  tetherBotP->turnToAngle(10, 60);
  tetherBotP->driveStraight(30, 6);
  tetherBotP->shoot(600);
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
