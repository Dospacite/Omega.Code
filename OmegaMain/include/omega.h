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
  * 
  */
  static void axisMovement(controller controller, motor MotorArray[], int threshold=5) {
    int powerLeft = (controller.Axis3.position() + controller.Axis4.position());
    int powerRight = (controller.Axis3.position() - controller.Axis4.position());
    if(threshold > abs(powerLeft) || threshold > abs(powerRight)) {
      MotorArray[0].spin(forward, powerLeft, pct);
      MotorArray[1].spin(forward, powerRight, pct);
    }
  }

  /* function -> spinForMS
  *
  */
  static void spinForMS(motor MotorArray[2], uint16_t time, int power = 100, int motorCount = 2) {
    MotorArray[0].spin(directionType::fwd, power, pct);
    MotorArray[0].spin(directionType::fwd, power, pct);
    task::sleep(time);
    MotorArray[0].stop(brakeType::hold);
    MotorArray[1].stop(brakeType::hold);
  }
};

class Buttons {
  public:
  static void buttonFunction(controller::button button1, controller::button button2, motor MotorArray[], uint16_t power, uint16_t motorCount = 2) {
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
