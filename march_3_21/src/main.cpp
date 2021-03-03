/*                             
                                     (                                                                                             
     )      )     )    )     )       )\ )  (                                     (                                 )               
  ( /(   ( /(  ( /( ( /(  ( /( (    (()/(  )\    )     )    (          (  (      )\           )             (   ( /(   (   (       
  )\())  )\()) )\()))\()) )(_)))\    /(_))((_)( /(    (     )\   (     )\))(   (((_)   (     (     `  )    ))\  )\()) ))\  )(   (  
 ((_)\  ((_)\ ((_)\((_)\ ((_) ((_)  (_))_| _  )(_))   )\  '((_)  )\ ) ((_))\   )\___   )\    )\  ' /(/(   /((_)(_))/ /((_)(()\  )\ 
| | (_)| | (_)/  (_)/ (_)|_  )| __| | |_  | |((_)_  _((_))  (_) _(_/(  (()(_) ((/ __| ((_) _((_)) ((_)_\ (_))( | |_ (_))   ((_)((_)
|_  _| |_  _|| () | | |   / / | _|  | __| | |/ _` || '  \() | || ' \))/ _` |   | (__ / _ \| '  \()| '_ \)| || ||  _|/ -_) | '_|(_-<
  |_|    |_|  \__/  |_|  /___||___| |_|   |_|\__,_||_|_|_|  |_||_||_| \__, |    \___|\___/|_|_|_| | .__/  \_,_| \__|\___| |_|  /__/
                                                                      |___/                       |_|                                                        
*/
//isaac worsencroft
//haden hodge 
//44012E 2020-2021 vex change up 

#include "vex.h"

using namespace std;
using namespace vex;

competition Competition;

  double  xlocation;
  double  ylocation;
  double  AvrageXVelocity; 
  double  AvrageYVelocity;
  double  AvrageRotation;
  double  oreantation; 
  double  lastPostionCheckTime;
  //skills selection varubles
    bool    sideselect       =  false ;
    bool    redtest          =  false ;
    bool    bluetest         =  false ;
    bool    skills           =  false ;
    bool    popAuton         =  false ;
    bool    RedonRedSide     =  false ;
    bool    RedonBlueSide    =  false ;
    bool    BlueonBlueSide   =  false ;
    bool    BlueonRedSide    =  false ;
  double  drivespeedCurent=.88;
  double  drivespeedhigh=.88;
  double  drivespeedlow=.40;
  int     xscreen;
  int     yscreen;
  int     redBallsAray[32]; 
  int     trackedItems;
//auton refrance callbacks//
//temporaroly spins the intakes
void shootForGoal   (int t){
      FShoot.spin(fwd ,     99, percentUnits::pct);
      BShoot.spin(fwd ,     95, percentUnits::pct);
      wait(t,timeUnits::msec);
      FShoot.stop();
      BShoot.stop();
}
//used to move the robot in cardne directions
  //(in the tearms of bow, port, starboard, and sturn)
void carnelMovment  (int t, int s, string robotheading){

    if       (robotheading=="bow"){
      FRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BRdrive.spin(directionType::fwd,s,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
         }
    else if (robotheading=="starboard"){
      FRdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BLdrive.spin(directionType::rev,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
    }
    else if (robotheading=="sturn"){
      FRdrive.spin(directionType::rev,s,percentUnits::pct);
      FLdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s,percentUnits::pct);
      BLdrive.spin(directionType::rev,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
    }
    else if (robotheading=="port"){
      FRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
    }
}
//recalibrates the inertal sensor
void calibrateInert (void){
  inertial1.calibrate();
   //while (inertial1.isCalibrating()) {
    wait(2000, msec);
  //}
}
//checks if the angle of the robot falls with in an exeptable range
void CheckAngle     (int maxAngle, int minAngle){
  bool goodUP; 
  bool goodDown;
  int tempAngle;
  //conver angle
  if(false/*inertial1.angle()>180*/){
    //tempAngle=abs(inertial1.angle()-180);
  }
  else{
    tempAngle=inertial1.angle();
  }
  if(tempAngle>maxAngle){
     goodUP = false;
      FRdrive.spin(directionType::rev,25,percentUnits::pct);
      FLdrive.spin(directionType::fwd,25,percentUnits::pct);
      BRdrive.spin(directionType::rev,25,percentUnits::pct);
      BLdrive.spin(directionType::fwd,25,percentUnits::pct);
      while(!goodUP){
      wait(125, timeUnits::msec);
      if (inertial1.heading()<maxAngle){
        goodUP=true;
      }
      }
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
  }
  if(tempAngle<minAngle){
     goodDown = false;
      FRdrive.spin(directionType::fwd,25,percentUnits::pct);
      FLdrive.spin(directionType::rev,25,percentUnits::pct);
      BRdrive.spin(directionType::fwd,25,percentUnits::pct);
      BLdrive.spin(directionType::rev,25,percentUnits::pct);
      while(!goodDown){
      wait(125, timeUnits::msec);
      if (inertial1.angle()>minAngle){
        goodDown=true;
      }
      }
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
  }  

}
//spins the robot
  //(in the tearms of "clockwise" and "anti-clockwise")
void spinMeDaddy    (int t, double s, string directionOfSpin){
  if (directionOfSpin=="anti-clockwise"){
    s=s*-1;
  }
  else {}
      FRdrive.spin(directionType::rev,s,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
      
}
//spins the robot with some flair but is less acuret 
  //(in the tearms of "clockwise" and "anti-clockwise")
void letsDrift      (int t, double s,  string directionOfSpin ){
    if (directionOfSpin=="anti-clockwise"){
      FRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::rev,s/4,percentUnits::pct);
      BRdrive.spin(directionType::fwd,s,percentUnits::pct);
      BLdrive.spin(directionType::rev,s/4,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop(brakeType::brake);
      FLdrive.stop(brakeType::brake);
      BRdrive.stop(brakeType::brake);
      BLdrive.stop(brakeType::brake);
  }
  else {
      FRdrive.spin(directionType::rev,s/4,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s/4,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(t, timeUnits::msec);
      FRdrive.stop(brakeType::brake);
      FLdrive.stop(brakeType::brake);
      BRdrive.stop(brakeType::brake);
      BLdrive.stop(brakeType::brake);
      }
}
//tells the intake to turn on and if on what dirction to spin 
void intakeAuton    (bool On, bool takein){
  if      (On&&takein){
      Rintake.spin(fwd ,     85, percentUnits::pct);
      Lintake.spin(fwd ,     85, percentUnits::pct);
  }
  else if (On){
      Rintake.spin(reverse , 85, percentUnits::pct);
      Lintake.spin(reverse , 85, percentUnits::pct);
  }
  else{
      Rintake.stop();
      Lintake.stop();
  }
}
//turns on the shoot
void shootAuton     (bool On){
  if (On){
      FShoot.spin(fwd ,     99, percentUnits::pct);
      BShoot.spin(fwd ,     95, percentUnits::pct);
  }
  else {
      FShoot.stop();
      BShoot.stop();
  }
}
//cycle ball out of goals 
void NewAutonSelect (bool skillsTest){
  if(skillsTest){
    skills      = true;
    sideselect  = true;
  }
  else{
    bool goalstoscore[] = {false, false, false, false};
    bool doneYetDude    = false;
    Brain.Screen.clearScreen();
      while (!sideselect) {
    if (Brain.Screen.pressing()) { 
          Brain.Screen.clearScreen();
  xscreen = Brain.Screen.xPosition();
  yscreen = Brain.Screen.yPosition();
      if (yscreen < 151) {
        if (xscreen < 160) {

          goalstoscore[1]   = true;
        }
        if (xscreen >= 320) {
 
          goalstoscore[2]   = true;
        }
        if (xscreen <= 320 && xscreen >= 160) {

          goalstoscore[3]   = true;
        }
      }
      else {
        if (xscreen >= 240) {       
        Brain.Screen.clearScreen(green);
        skills          = true; 
        doneYetDude     = true;
         }
         else {
           if(goalstoscore[1]||goalstoscore[2]||goalstoscore[3]){
             if(!(goalstoscore[1]&&goalstoscore[2])||!(goalstoscore[2]&&goalstoscore[3])||!(goalstoscore[1]&&goalstoscore[3])){
               popAuton=true;
             }
           }
         }     
      }
    }
    sideselect          = true;
  }
  }}
//drives forward and backward to remove balls from goals
void tugBall        (int cylces){
  for(int i = 0; i<=cylces; i++){
  carnelMovment(250, 50,"sturn");
  carnelMovment(250, 50,"bow");}
}
//desides what happens when a bumper is pressed

//skills only auto correction 
void prsisionMovment(int t, int s, string robotheading, int max, int min) {
  
	int curentAngle= inertial1.angle();			//the value given by the ineral sensor
	int curentAngleAjusted;	//-180 to 180 value 
		if (curentAngle < 60 || curentAngle>300) {
			if (curentAngle > 180) {
				curentAngleAjusted = curentAngle - 180;
			}
		}
  int maxAngle;	//-180 to 180 value 
		if (max < 60 || max>300) {
			if (max > 180) {
				maxAngle = max - 180;
			}
		}
  int minAngle;	//-180 to 180 value 
		if (min < 60 || min >300) {
			if (min > 180) {
				minAngle = min - 180;
			}
		}
    Brain.Screen.clearLine();
    Brain.Screen.print("level one");
    for(int i = 0; i < t; i++) {
		
    if      (robotheading=="bow"){
      FRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BRdrive.spin(directionType::fwd,s,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(1, timeUnits::msec);
         }
    else if (robotheading=="starboard"){
      FRdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::fwd,s,percentUnits::pct);
      BLdrive.spin(directionType::rev,s,percentUnits::pct);
      wait(1, timeUnits::msec);
    }
    else if (robotheading=="sturn"){
      FRdrive.spin(directionType::rev,s,percentUnits::pct);
      FLdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s,percentUnits::pct);
      BLdrive.spin(directionType::rev,s,percentUnits::pct);
      wait(1, timeUnits::msec);
    }
    else if (robotheading=="port"){
      FRdrive.spin(directionType::fwd,s,percentUnits::pct);
      FLdrive.spin(directionType::rev,s,percentUnits::pct);
      BRdrive.spin(directionType::rev,s,percentUnits::pct);
      BLdrive.spin(directionType::fwd,s,percentUnits::pct);
      wait(1, timeUnits::msec);
    }
		while(i % 1000 == 0) {
    if(inertial1.angle()>maxAngle){
      FRdrive.spin(directionType::rev,25,percentUnits::pct);
      FLdrive.spin(directionType::fwd,25,percentUnits::pct);
      BRdrive.spin(directionType::rev,25,percentUnits::pct);
      BLdrive.spin(directionType::fwd,25,percentUnits::pct);
      waitUntil(inertial1.angle()<maxAngle);    
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop(); 
  }
  if(inertial1.angle()<minAngle){
      FRdrive.spin(directionType::fwd,25,percentUnits::pct);
      FLdrive.spin(directionType::rev,25,percentUnits::pct);
      BRdrive.spin(directionType::fwd,25,percentUnits::pct);
      BLdrive.spin(directionType::rev,25,percentUnits::pct);
      waitUntil(inertial1.angle()>minAngle);    
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
  }  
		}
	wait(1, timeUnits::msec);
  }
      FRdrive.stop();
      FLdrive.stop();
      BRdrive.stop();
      BLdrive.stop();
}
/*  __    __  __  ____  _____  _  _  _____  __  __  _____  __  __  ___ 
   /__\  (  )(  )(_  _)(  _  )( \( )(  _  )(  \/  )(  _  )(  )(  )/ __)
  /(__)\  )(__)(   )(   )(_)(  )  (  )(_)(  )    (  )(_)(  )(__)( \__ \
 (__)(__)(______) (__) (_____)(_)\_)(_____)(_/\/\_)(_____)(______)(___/
  */
//blue  on  red
void BORAuton       (){
  intakeAuton(true, false);
  carnelMovment(875, 50, "bow");
  wait(125,timeUnits::msec);
  spinMeDaddy(950, 25, "anti-clockwise");
  intakeAuton(true, true);
  wait(125,timeUnits::msec);
  carnelMovment(1300, 50, "bow");
  shootForGoal(1000);
  carnelMovment(750, 40, "sturn");
  spinMeDaddy(1000, 23, "anti-clockwise");
  intakeAuton(false, true);
}
  //red   on  red
void RORAuton       (){
  intakeAuton(true, false);
  carnelMovment(875, 50, "bow");
  wait(125,timeUnits::msec);
  spinMeDaddy(1000, 25, "anti-clockwise");
  intakeAuton(true, true);
  wait(125,timeUnits::msec);
  carnelMovment(1000, 50, "bow");
  shootForGoal(1000);
  carnelMovment(750, 40, "sturn");
  wait(125,timeUnits::msec);
  spinMeDaddy(925, 22, "anti-clockwise");
  intakeAuton(false, true);
  carnelMovment(1425, 50, "bow");
  shootAuton(true);
  wait(25, timeUnits::msec);
  shootAuton(false);
  spinMeDaddy(700, 25, "clockwise");
  wait(150,timeUnits::msec);
  carnelMovment(750, 55, "bow");
  shootForGoal(1100);
  intakeAuton(true, true);
  carnelMovment(675, 50, "sturn");
  wait(150,timeUnits::msec);
  intakeAuton(false, true);
  spinMeDaddy(700, 22.5, "anti-clockwise");
  wait(100,timeUnits::msec);
  carnelMovment(950, 50, "bow");
  spinMeDaddy(300, 25, "clockwise");
  intakeAuton(true, true);
  carnelMovment(1000, 65, "bow");
  carnelMovment(300, 80, "sturn");
  carnelMovment(400, 85, "bow");
  shootForGoal(1200);
  wait(100,timeUnits::msec);
  intakeAuton(false, false);
  carnelMovment(300, 80, "sturn");
  
}
  //blue  on  blue
void BOBAuton       (){
 //shootForGoal(1000);
   intakeAuton(true, false);
  carnelMovment(875, 50, "bow");
  wait(125,timeUnits::msec);
  spinMeDaddy(1000, 25, "clockwise");
  intakeAuton(true, true);
  wait(125,timeUnits::msec);
  carnelMovment(1000, 50, "bow");
  carnelMovment(125, 40, "sturn");
  carnelMovment(125, 50, "bow");
  shootForGoal(1400);
  carnelMovment(750, 40, "sturn");
  spinMeDaddy(1000, 23, "anti-clockwise");
  intakeAuton(false, true);
  carnelMovment(1000, 40, "sturn");
}
  //red   on  blue
void ROBAuton       (){
     intakeAuton(true, false);
  carnelMovment(875, 50, "bow");
  wait(125,timeUnits::msec);
  spinMeDaddy(1000, 25, "anti-clockwise");
  intakeAuton(true, true);
  wait(125,timeUnits::msec);
  carnelMovment(1000, 50, "bow");
  shootForGoal(1000);
  carnelMovment(750, 40, "sturn");
  wait(125,timeUnits::msec);
  spinMeDaddy(925, 22, "anti-clockwise");
  intakeAuton(false, true);
  carnelMovment(1425, 50, "bow");
  shootAuton(true);
  wait(100, timeUnits::msec);
  shootAuton(false);
  spinMeDaddy(700, 25, "clockwise");
  wait(150,timeUnits::msec);
  carnelMovment(750, 55, "bow");
  shootForGoal(1100);
  intakeAuton(true, true);
  carnelMovment(675, 50, "sturn");
  wait(150,timeUnits::msec);
  intakeAuton(false, true);
}
  //skils
void SKIAuton       (){
  intakeAuton(true, false);
  wait(250,timeUnits::msec);  
  intakeAuton(true, true);
  carnelMovment(1700, 25, "bow");
  wait(125,timeUnits::msec);
  intakeAuton(false, true);
  spinMeDaddy(1000, 24, "clockwise");
  wait(125,timeUnits::msec);
  carnelMovment(1200, 49, "bow");
  shootForGoal(1400);
  carnelMovment(1720, 40, "sturn");
  wait(125,timeUnits::msec);
  spinMeDaddy(900, 25, "clockwise");
  wait(125,timeUnits::msec);
  carnelMovment(925, 60, "sturn");
  wait(300,timeUnits::msec);
  carnelMovment(300, 60, "sturn");
  wait(150,timeUnits::msec);
  intakeAuton(true, true);
  carnelMovment(3000, 25, "bow");
  //carnelMovment(1000, 40, "sturn");
}

//threads//

int sensorTread     () {
    //calls back what to do when a bumper is pressed or another sensor is trigared 
    while(true){
      AvrageRotation  = ((gyroAlpha.rotation()-inertial1.rotation())/2);
      AvrageXVelocity = (((((AccAlpha.acceleration()+AccBata.acceleration()-AccGamma.acceleration()+inertial1.acceleration(axisType::zaxis))/4)+.13)*9.80665)+0.04);
      AvrageYVelocity = (((((AccAlphay.acceleration()+AccBatay.acceleration()-AccGammay.acceleration()+inertial1.acceleration(axisType::xaxis))/4)+.13)*9.80665)+0.04);
      this_thread::sleep_for(100);
    }
  return 0;
}
//handles the joystick contoled movment of the robot duing drive contol 
int driveThread     () {
  thread bumberTread      = thread(sensorTread);
  while (true) {
    // You must sleep threads by using the 'this_thread::sleep_for(unit in
    // msec)' command to prevent this thread from using all of the CPU's
    // resources.
      FRdrive.spin(directionType::fwd, ( drivespeedhigh*controller1.Axis3.position()-drivespeedCurent*controller1.Axis1.position()), percentUnits::pct);
      FLdrive.spin(directionType::fwd, ( drivespeedhigh*controller1.Axis3.position()+drivespeedCurent*controller1.Axis1.position()), percentUnits::pct);
      BRdrive.spin(directionType::fwd, ( drivespeedhigh*controller1.Axis3.position()-drivespeedCurent*controller1.Axis1.position()), percentUnits::pct);
      BLdrive.spin(directionType::fwd, ( drivespeedhigh*controller1.Axis3.position()+drivespeedCurent*controller1.Axis1.position()), percentUnits::pct);
      
        

      FRdrive.setBrake(brakeType::brake);
      FLdrive.setBrake(brakeType::brake);
      BRdrive.setBrake(brakeType::coast);
      BLdrive.setBrake(brakeType::coast);
    
      this_thread::sleep_for(5);
  }
  return 0;
}

int locationOfRobot (){
  while(true){
  
  double xAcceliration = 9.80665*inertial1.acceleration(axisType::zaxis);
  double yAcceliration = 9.80665*inertial1.acceleration(axisType::yaxis);
  
  xlocation=xAcceliration*((-lastPostionCheckTime+vex::timer::systemHighResolution())/1000000);
  ylocation=yAcceliration*((-lastPostionCheckTime+vex::timer::systemHighResolution())/1000000);
  lastPostionCheckTime=vex::timer::systemHighResolution();
  this_thread::sleep_for(15);
  }
  return 0;
}

int ballTracking    (){
  while(true){
    trackedItems=spycam.objectCount;
    //Brain.Screen.setCursor(3, 1);
    //Brain.Screen.print(trackedItems);
    this_thread::sleep_for(100);
  }
  return 0;
}
//draws debuginfo while driving 
int infoDisplay     (){
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(ylocation );
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(xlocation);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print(trackedItems);
    Brain.Screen.newLine();
    Brain.Screen.print("Avrage Rotation :: ");
    Brain.Screen.print(AvrageRotation);
    Brain.Screen.newLine();
    Brain.Screen.print("Acceliration :: ");
    Brain.Screen.print(AvrageXVelocity);
    Brain.Screen.newLine();
    Brain.Screen.print("Acceliration y :: ");
    Brain.Screen.print(AvrageYVelocity);
    Brain.Screen.newLine();
    Brain.Screen.print(FRdrive.temperature(temperatureUnits::fahrenheit));
    Brain.Screen.print("-      FR");
    Brain.Screen.newLine();
    Brain.Screen.print(FLdrive.temperature(temperatureUnits::fahrenheit)); 
    Brain.Screen.print("-      FL"); 
    Brain.Screen.newLine();
    Brain.Screen.print(BRdrive.temperature(temperatureUnits::fahrenheit)); 
    Brain.Screen.print("-      BR"); 
    Brain.Screen.newLine();
    Brain.Screen.print(BRdrive.temperature(temperatureUnits::fahrenheit));
    Brain.Screen.print("-      BL");      
    this_thread::sleep_for(100);
  }
  return 0;
}
/* 
(  _ \(  _ \(_  _)( \/ )( ___)(  _ \   / __)(  _  )( \( )(_  _)(  _  )(  )  
 )(_) ))   / _)(_  \  /  )__)  )   /  ( (__  )(_)(  )  (   )(   )(_)(  )(__ 
(____/(_)\_)(____)  \/  (____)(_)\_)   \___)(_____)(_)\_) (__) (_____)(____)*/
//compition call back that is run during driver contol period
void driveTime      (void) {
  // Initializing Robot
    vexcodeInit();
  //treads
    thread ballTrackinga    = thread(ballTracking);
    thread bumberTread      = thread(sensorTread);
    thread myThread         = thread(driveThread);
    thread locationTracking = thread(locationOfRobot);
    thread Displayinfo      = thread(infoDisplay);
  //main drive loop other than joystick input(joystick handled by driveTread)
  while(1){
    if(controller1.ButtonDown.pressing()){
      //cycleGoals(2);
      //SKIAuton();
      inertial1.calibrate();
      wait(100, timeUnits::msec);
    }
    if(controller1.ButtonLeft.pressing()){    
        drivespeedCurent=drivespeedlow;
    }
    else{
        drivespeedCurent=drivespeedhigh;        
      }
    if(controller1.ButtonR1.pressing()){
      FShoot.spin(fwd ,     98, percentUnits::pct);
      BShoot.spin(fwd ,     98, percentUnits::pct);
    }
    else if(controller1.ButtonR2.pressing()) {
      FShoot.spin(reverse , 65, percentUnits::pct);
      BShoot.spin(reverse , 65, percentUnits::pct);

    }
     
    
    else {
      FShoot.stop(brakeType::coast);
      BShoot.stop(brakeType::coast);
    }

     if(controller1.ButtonL2.pressing()){
      Rintake.spin(fwd ,     95, percentUnits::pct);
      Lintake.spin(fwd ,     95, percentUnits::pct);
    }
    else if(controller1.ButtonB.pressing()||controller1.ButtonL1.pressing()) {
      Lintake.spin(reverse , 95, percentUnits::pct);
      Rintake.spin(reverse , 95, percentUnits::pct);

    }

    else {
    Lintake.stop(brakeType::coast);
    Rintake.stop(brakeType::coast);
    }
  }
  
}
//compition call back that is run during the start of the match
void pre_auton      (void){  
  inertial1.calibrate();
   //while (inertial1.isCalibrating()) {
    wait(2000, msec);
  //}
  Brain.Screen.setPenColor    (white);
  Brain.Screen.setFillColor   (black);
  Brain.Screen.drawLine       (240, 0, 240, 150);
  Brain.Screen.drawLine       (0, 150, 700, 150);
  Brain.Screen.setFillColor   (red);
  Brain.Screen.drawRectangle  (1, 1, 240, 149);
  Brain.Screen.setFillColor   (blue);
  Brain.Screen.drawRectangle  (240, 1, 240, 149);
  Brain.Screen.setFillColor   (green);
  Brain.Screen.drawRectangle  (1, 151, 700, 240);
  Brain.Screen.drawLine       (160, 0, 160, 150);
  Brain.Screen.drawLine       (320, 0, 320, 150);
  while (!sideselect) {
    if(controller1.ButtonB.pressing()&&!Brain.Screen.pressing()){
      
      sideselect=true;
      
    }
    if (Brain.Screen.pressing()) { 
          Brain.Screen.clearScreen();
  xscreen = Brain.Screen.xPosition();
  yscreen = Brain.Screen.yPosition();
      if (yscreen < 151) {
        if (xscreen < 160) {
          Brain.Screen.clearScreen(red);
          RedonRedSide    = true;
          sideselect      = true;
        }
        if (xscreen >= 320) {
          Brain.Screen.clearScreen(blue);
          BlueonBlueSide  = true;
          sideselect      = true;
        }
        if (xscreen <= 240 && xscreen >= 160) {
          Brain.Screen.clearScreen(orange);
          RedonBlueSide   = true;
          sideselect      = true;
        }
        if (xscreen >= 240 && xscreen <= 320) {
          Brain.Screen.clearScreen(purple);
          BlueonRedSide   = true;
          sideselect      = true;
        }
      } else {
        Brain.Screen.clearScreen(green);
        skills            = true;
        sideselect        = true;
      }      vex::task::sleep(200);
    }
  } 
}
//depending on what auton that is chosen during pre-auton will run the respective auton during the autonumus period
void auton          (void){
      lastPostionCheckTime=0;
             if (RedonRedSide   == true){RORAuton();}
        else if (RedonBlueSide  == true){ROBAuton();}
        else if (BlueonBlueSide == true){BOBAuton();}
        else if (BlueonRedSide  == true){BORAuton();}
        else if (skills         == true){SKIAuton();}
        else                            {           }
}
//main method that calls the rest of the program
int main            () {
  thread ballTrackinga  = thread(ballTracking);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(auton);
  Competition.drivercontrol(driveTime);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}