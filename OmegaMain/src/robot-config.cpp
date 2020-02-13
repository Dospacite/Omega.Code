#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;

controller Controller1 = controller(primary);

motor HandRight = motor(PORT12, ratio18_1, true);
motor HandLeft = motor(PORT1, ratio18_1, false);

motor MoveRight = motor(PORT16, ratio18_1, true);
motor MoveLeft = motor(PORT19, ratio18_1, false);

motor LifterRight = motor(PORT3, ratio18_1, true);
motor LifterLeft = motor(PORT18, ratio18_1, false);

motor ArmRight = motor(PORT20, ratio18_1, true);
motor ArmLeft = motor(PORT17, ratio18_1, false);

