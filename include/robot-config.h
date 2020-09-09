using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftmotor;
extern motor rightmotor;
extern motor armmotor;
extern controller Controller1;
extern motor crabmotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );