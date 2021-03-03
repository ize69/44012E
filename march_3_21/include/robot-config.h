//basic needed divices 
  using namespace vex;
  extern brain Brain;
  extern controller controller1;
// VEXcode devices

//motors
  extern motor FRdrive;
  extern motor FLdrive;
  extern motor BRdrive;
  extern motor BLdrive;
  extern motor FShoot;
  extern motor BShoot;
  extern motor Lintake;
  extern motor Rintake;

//v5    sensors
  extern inertial inertial1; 
  extern vision spycam;

//3pin  sensors
  //A//
  //not in use
  
  //B//
  //not in use
  extern accelerometer AccAlphay;
  extern accelerometer AccBatay;
  //E//
  extern accelerometer AccGammay;
  //C//
  extern accelerometer AccAlpha;
  //D//
  extern accelerometer AccBata;
  //E//
  extern accelerometer AccGamma;
  //F/
  
  //G//
  //not in use 
  //H//
  extern gyro   gyroAlpha;
 

//gets things started
  void  vexcodeInit( void );