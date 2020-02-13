#include "vex.h"
#include "omega.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// HandRight            motor         12              
// HandLeft             motor         1               
// MoveLeft             motor         19              
// MoveRight            motor         16              
// LifterRight          motor         3               
// LifterLeft           motor         18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----


using namespace vex;
competition Competition;

void autonomous(void) {
  motor MovementMotors[2] = {
    MoveRight,
    MoveLeft
  };
  motor HandMotors[2] = {
    HandRight,
    HandLeft
  };

  motor Lifters[2] = {
    LifterRight,
    LifterLeft
};
  Movement::rotateForDistance(forward, MoveLeft, 10.16, 178.435, 50, false);
  Movement::rotateForDistance(forward, MoveLeft, 10.16, 178.435, 50);
}


void usercontrol(void) {
  motor MovementMotors[2] = {
    MoveRight,
    MoveLeft
  };
  motor HandMotors[2] = {
    HandRight,
    HandLeft
  };

  motor Lifters[2] = {
    LifterRight,
    LifterLeft
  };

  motor ArmMotors[2] = {
    ArmRight,
    ArmLeft
  };


  Controller1.Screen.print("     Omega - Kaan");
  Controller1.rumble(".-"); //Syntax => "-" for long, "." for short, " " for pause.


  while(true) {
    Movement::axisMovement(Controller1, MovementMotors);
    Buttons::buttonFunction(Controller1.ButtonR2, Controller1.ButtonR1, HandMotors, 100);
    if (Controller1.ButtonX.pressing() || Controller1.ButtonB.pressing()) {
      Buttons::buttonFunction(Controller1.ButtonX, Controller1.ButtonB, Lifters, 100);
    }
    else if(Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()){
      Buttons::buttonFunction(Controller1.ButtonL1, Controller1.ButtonL2, Lifters, 20);
    }
    else {
      Buttons::armControl(Controller1.ButtonUp, Controller1.ButtonDown, Lifters, ArmMotors, 50);
    }
    vex::task::sleep(20);
  }
}


int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
}