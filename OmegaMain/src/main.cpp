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

//Spins all motors in the MotorArray[] for the given time. Has (on average) 1.4ms delay between each motor.
bool spinForMS(motor MotorArray[2], uint16_t time, int power = 100, int motorCount = 2) {
    for (int i = 0; i < motorCount; i++) {
        MotorArray[i].spin(directionType::fwd, power, pct);
    }
    task::sleep(time);
    for (int i = 0; i < motorCount; i++) {
      MotorArray[i].stop(brakeType::hold);
    }
    return false;
}

//autonomous function that is called before the usercontrol period, lasts 15 seconds.
void autonomous(void) {
  motor MovementMotors[2] = {
    MoveLeft,
    MoveRight
  };
  motor HandMotors[2] = {
    HandLeft,
    HandRight
  };

  motor Lifters[2] = {
    LifterRight,
    LifterLeft
};
  Movement::rotateForDistance(forward, MoveLeft, 10.16, 178.435, 50, false);
  Movement::rotateForDistance(forward, MoveLeft, 10.16, 178.435, 50);
}

//Takes two arrays and an integer, spins all the motors in the MotorArray[] forward if the first button
//is pressed, and reverse if the second one is pressed. Stops every motor if nothing is pressed.
bool buttonFunction(controller::button button1, controller::button button2, motor MotorArray[], uint16_t power, uint16_t motorCount = 2) {
    if (button1.pressing()) {
        for (int i = 0; i < motorCount; i++) {
            MotorArray[i].spin(directionType::fwd, power, velocityUnits::pct);
        }
    } else if (button2.pressing()) {
        for (int i = 0; i < motorCount; i++) {
            MotorArray[i].spin(directionType::rev, power, velocityUnits::pct);
        }
    } else {
        for (int i = 0; i < 2; i++) {
            MotorArray[i].stop(brakeType::hold);
        }
    }
    return false;
}

//Reads axis values from the given controller, spins the motors according to the values.
//Left Motor => Axis4 + Axis3
//Right Motor => Axis4 - Axis3
bool axisMovement(controller controller) {
    int powerLeft = (controller.Axis3.position() + controller.Axis4.position());
    int powerRight = (controller.Axis3.position() - controller.Axis4.position());
    MoveLeft.spin(forward, powerLeft, pct);
    MoveRight.spin(forward, powerRight, pct);

    return false;
}

//usercontrol function that runs after the autonomous period, lasts 45 seconds. Will not work if the controller is not plugged.
void usercontrol(void) {
  motor MovementMotors[2] = {
    MoveLeft,
    MoveRight
  };
  motor HandMotors[2] = {
    HandLeft,
    HandRight
  };

  motor Lifters[2] = {
    LifterRight,
    LifterLeft
};
  
  Controller1.Screen.print("Omega - Kaan");
  Controller1.rumble("- - -"); //Syntax => "-" for long, "." for short, " " for pause.

  while(true) {
    axisMovement(Controller1); //axisMovement(controller ismi)
    buttonFunction(Controller1.ButtonR2, Controller1.ButtonR1, HandMotors, 100,2); //buttonFunction(buton 1, buton 2, motor listesi, güç, motor sayısı)
    if(!(Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing())) {
      buttonFunction(Controller1.ButtonX, Controller1.ButtonB, Lifters, 100, 2);
    }
    else {
      buttonFunction(Controller1.ButtonL1, Controller1.ButtonL2, Lifters, 20, 2);
    } 
    vex::task::sleep(20);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
}