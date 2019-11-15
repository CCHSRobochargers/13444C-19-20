using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LDM;
extern motor RDM;
extern motor LLM;
extern motor RLM;
extern motor RFM;
extern motor LFM;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );