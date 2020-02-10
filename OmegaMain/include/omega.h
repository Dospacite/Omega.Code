#include "vex.h"
#include "math.h"

using namespace vex;

class Movement {

  public:
  static void rotateForDistance(motor Motor, double diameter, double distanceToTravel, bool waitForFinish=true) {
    rotateForDistance(forward, Motor, diameter*M_PI, distanceToTravel, 100, waitForFinish);
  }
  /*
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
};
