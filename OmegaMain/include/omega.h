#include "vex.h"
#include "math.h"

using namespace vex;

class Movement {

  public:

  static void rotateForDistance(motor Motor, double diameter, double distanceToTravel, bool waitForFinish=true) {
    rotateForDistance(forward, Motor, diameter*M_PI, distanceToTravel, 100, waitForFinish);
  }
  /* function -> rotateForDistance
  * Finds the degree required to travel the distance given and spins the motor for that amount.
  * @param dir Default vex::directionType. Either forward or reverse.
  * @param Motor motor that will be spun.
  * @param circumference Circumference of the wheel being used. Can be found with pi * diameter.
  * @param distanceToTravel Distance that the motor will travel for. Should be used as centimeters.
  * @param power Power that the motor will be powered with. Affects speed.
  * @param waitForFinish Whether or not the program will wait until the motor finishes spinning.
  */
  static void rotateForDistance(directionType dir, motor Motor, float circumference, float distanceToTravel, int power, bool waitForFinish=true) {
    Motor.rotateFor(distanceToTravel/circumference*360, rotationUnits::deg, power, velocityUnits::pct, waitForFinish);
  }

  /* function -> axisMovement
  * Powers the motors from the input it gets at the given "controller".
  * @param controller Controller that the axis values will be taken from.
  * @param MotorArray[] Motor array that includes the motors that will be powered. [Right, Left]
  * @param threshold=5 The minimum absolute value that will power the motors. Reduces battery usage.
  */
  static void axisMovement(controller controller, motor MotorArray[], int threshold=5) {
    int powerLeft = (controller.Axis3.position() + controller.Axis4.position());
    int powerRight = (controller.Axis3.position() - controller.Axis4.position());
    if(threshold > abs(powerLeft) || threshold > abs(powerRight)) {
      MotorArray[0].spin(forward, powerLeft, pct);
      MotorArray[1].spin(forward, powerRight, pct);
    }
  }
};

class Buttons {
	
  public:
  
  /* function -> buttonFunction
  * Powers the given motors when either button is pressed.
  * @param button1 Button that will power the motors forward.
  * @param button2 Button that will power the motors reverse.
  * @param MotorArray[] Motors that will be powered when either buttons are pressed.
  * @param power Power that the motors will be powered with.
  */
  static void buttonFunction(controller::button button1, controller::button button2, motor MotorArray[], uint16_t power) {
    if (button1.pressing()) {
      MotorArray[0].spin(directionType::fwd, power, velocityUnits::pct);
      MotorArray[1].spin(directionType::fwd, power, velocityUnits::pct);
    } 
    else if (button2.pressing()) {
      MotorArray[0].spin(directionType::rev, power, velocityUnits::pct);
      MotorArray[1].spin(directionType::rev, power, velocityUnits::pct);
    }
    else {
      MotorArray[0].stop(brakeType::hold);
      MotorArray[1].stop(brakeType::hold);
    }
  }
  /*
  * Powers the given motors when either button is pressed. At the same time, powers the motors given with the LiftArray by a small amount.
  * @param button1 Button that will power the motors forward.
  * @param button2 Button that will power the motors reverse.
  * @param LiftArray[] Motors that will be powered by a small amount when either buttons are pressed.
  * @param MotorArray[] Motors that will be powered when either buttons are pressed.
  * @param power Power that the motors in MotorArray will be powered with.
  */
  static void armControl(controller::button button1, controller::button button2, motor LiftArray[2], motor MotorArray[2], int power) {
    if (button1.pressing()) {
      LiftArray[0].spin(forward, 10, pct);
      LiftArray[1].spin(forward, 10, pct);
      MotorArray[0].spin(directionType::fwd, power, velocityUnits::pct);
      MotorArray[1].spin(directionType::fwd, power, velocityUnits::pct);
    }
    else if (button2.pressing()) {
      LiftArray[0].spin(reverse, 10, pct);
      LiftArray[1].spin(reverse, 10, pct);
      MotorArray[0].spin(directionType::rev, power, velocityUnits::pct);
      MotorArray[1].spin(directionType::rev, power, velocityUnits::pct);
    }
    else {
      LiftArray[0].stop(brakeType::hold);
      LiftArray[1].stop(brakeType::hold);
      MotorArray[0].stop(brakeType::hold);
      MotorArray[1].stop(brakeType::hold);
    }
  }
};
