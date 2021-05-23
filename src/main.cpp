/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       kohmeikadoya                                              */
/*    Created:      Mon Nov 09 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/robot-config.cpp"

competition Competition;

void autonomous() {
  // rollerBack.spin(forward, 100, percentUnits::pct);
  // task::sleep(1000);
  // rollerBack.stop();
  // driveStraight(40, 24);
  turnToAngle(30,-90);
}

void pre_auton() {
  
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
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
