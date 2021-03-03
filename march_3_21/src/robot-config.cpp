#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
controller controller1;

// VEXcode device constructors
motor   FRdrive = motor   (PORT8  , ratio18_1, true  );
motor   FLdrive = motor   (PORT10 , ratio18_1, false );
motor   BRdrive = motor   (PORT19 , ratio18_1, true  );
motor   BLdrive = motor   (PORT9 , ratio18_1, false );
motor   FShoot  = motor   (PORT11 , ratio18_1, false );
motor   BShoot  = motor   (PORT12 , ratio18_1, true  );
motor   Rintake = motor   (PORT17 , ratio18_1, false );
motor   Lintake = motor   (PORT15   , ratio18_1, true  );

analog_in balz  = analog_in (Brain.ThreeWirePort.A   );
accelerometer AccAlphay = accelerometer  (Brain.ThreeWirePort.B);
accelerometer AccBatay  = accelerometer  (Brain.ThreeWirePort.C);
accelerometer AccGammay = accelerometer  (Brain.ThreeWirePort.D);
accelerometer AccAlpha  = accelerometer  (Brain.ThreeWirePort.E);
accelerometer AccBata   = accelerometer  (Brain.ThreeWirePort.F);
accelerometer AccGamma  = accelerometer  (Brain.ThreeWirePort.G);
gyro          gyroAlpha = gyro           (Brain.ThreeWirePort.H);

inertial inertial1 = inertial(PORT6);
vision  spycam = vision(PORT7);
// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}