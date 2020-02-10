#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;

controller Controller1 = controller(primary);

motor HandRight = motor(PORT12, ratio18_1, false);
motor HandLeft = motor(PORT1, ratio18_1, true);

motor MoveRight = motor(PORT16, ratio18_1, false);
motor MoveLeft = motor(PORT19, ratio18_1, true);

motor LifterRight = motor(PORT3, ratio18_1, false);
motor LifterLeft = motor(PORT18, ratio18_1, true);

