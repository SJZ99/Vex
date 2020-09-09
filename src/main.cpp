

#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftmotor            motor         10              
// rightmotor           motor         1               
// armmotor             motor         8               
// Controller1          controller                    
// crabmotor            motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

int main() {

  vexcodeInit();
  
  while(1){
    //輪子
    leftmotor.spin(forward,Controller1.Axis2.position(percent)- Controller1.Axis1.position(percent) + Controller1.Axis3.position(percent) - Controller1.Axis4.position(percent),pct);
    rightmotor.spin(forward,Controller1.Axis2.position(percent)- Controller1.Axis1.position(percent) - Controller1.Axis3.position(percent)+ Controller1.Axis4.position(percent),pct);
    //手臂
    if (Controller1.ButtonL1.pressing()){
      armmotor.spin(forward,20,pct);
    }
    else if (Controller1.ButtonL2.pressing()){
      armmotor.spin(reverse,20,pct);
    }
    else{
      armmotor.spin(forward,0,pct);
      armmotor.stop(hold);
    }  } 
    //爪子
    if (Controller1.ButtonR1.pressing()){
      crabmotor.spin(forward,200,pct);
    }
    else if (Controller1.ButtonR2.pressing()){
      crabmotor.spin(reverse,200,pct);
    }
    else{
      crabmotor.spin(forward,0,pct);
      crabmotor.stop(hold);
    //button
    if(Controller1.ButtonA.pressing()){
      leftmotor.spin(forward,50,pct);
      rightmotor.spin(forward,-50,pct);
    }else if(Controller1.ButtonB.pressing()){
      leftmotor.spin(forward,-50,pct);
      rightmotor.spin(forward,50,pct);
    }
    }








}
