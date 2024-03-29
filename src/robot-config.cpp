#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LDM = motor(PORT11, ratio18_1, false);
motor RDM = motor(PORT20, ratio18_1, true);
motor LLM = motor(PORT2, ratio18_1, true);
motor RLM = motor(PORT9, ratio18_1, false);
motor RFM = motor(PORT8, ratio18_1, false);
motor LFM = motor(PORT3, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}