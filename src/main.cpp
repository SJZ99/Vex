

#include "vex.h"
#include <cmath>

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
double m_quickStopAccumulator = 0, leftout, rightout;
void armMotorForward(){
  armmotor.spin(forward, 20, pct);
}
double max(double val, double num){
  if(val >= num)
    return val;
  else 
    return num;
}
void curvatureDrive(double xSpeed, double zRotation, bool isQuickTurn) {
    // xSpeed = MathUtil.clamp(xSpeed, -1.0, 1.0);
    if(xSpeed < 0.05 & xSpeed > -0.05){
      xSpeed = 0;
    }//簡易死區設定
    // zRotation = MathUtil.clamp(zRotation, -1.0, 1.0);
    double angularPower;
    bool overPower;
    double m_quickStopAlpha = 0.1;
    if (isQuickTurn) {
      if (sqrt(pow(xSpeed, 2)) < 0.1) {
        m_quickStopAccumulator = (1 - 0.1) * m_quickStopAccumulator
            + m_quickStopAlpha * zRotation * 2;
      }

      overPower = true;
      angularPower = zRotation;
    } else {
      overPower = false;
      angularPower = sqrt(pow(xSpeed, 2)) * zRotation - m_quickStopAccumulator;

      if (m_quickStopAccumulator > 1) {
        m_quickStopAccumulator -= 1;
      } else if (m_quickStopAccumulator < -1) {
        m_quickStopAccumulator += 1;
      } else {
        m_quickStopAccumulator = 0.0;
      }
    }

    double leftMotorOutput = xSpeed - angularPower;
    double rightMotorOutput = xSpeed + angularPower;

    // If rotation is overpowered, reduce both outputs to within acceptable range
    if (overPower) {
      if (leftMotorOutput > 1.0) {
        rightMotorOutput -= leftMotorOutput - 1.0;
        leftMotorOutput = 1.0;
      } else if (rightMotorOutput > 1.0) {
        leftMotorOutput -= rightMotorOutput - 1.0;
        rightMotorOutput = 1.0;
      } else if (leftMotorOutput < -1.0) {
        rightMotorOutput -= leftMotorOutput + 1.0;
        leftMotorOutput = -1.0;
      } else if (rightMotorOutput < -1.0) {
        leftMotorOutput -= rightMotorOutput + 1.0;
        rightMotorOutput = -1.0;
      }
    }

    // Normalize the wheel speeds
    double maxMagnitude = max(sqrt(pow(leftMotorOutput, 2)), sqrt(pow(rightMotorOutput, 2)));
    if (maxMagnitude > 1.0) {
      leftMotorOutput /= maxMagnitude;
      rightMotorOutput /= maxMagnitude;
    }
    leftout=  leftMotorOutput;
    rightout = rightMotorOutput;

  }
int main() {

  vexcodeInit();
  // Controller1.ButtonL1.released(armMotorForward); 
  // uint32_t i = 0;
  // int sleep = 0;
  
  while(1){
    //輪子
    // int left = Controller1.Axis2.position(percent) + Controller1.Axis1.position(percent) + Controller1.Axis3.position(percent) + Controller1.Axis4.position(percent);
    // int right = Controller1.Axis2.position(percent) - Controller1.Axis1.position(percent) + Controller1.Axis3.position(percent) - Controller1.Axis4.position(percent);

    // for(int i = 0; i < 1000; i++){
    //   left = Controller1.Axis2.position(percent) + Controller1.Axis1.position(percent) + Controller1.Axis3.position(percent) + Controller1.Axis4.position(percent);
    //   right = Controller1.Axis2.position(percent) - Controller1.Axis1.position(percent) + Controller1.Axis3.position(percent) - Controller1.Axis4.position(percent);

    //   motionL[i] = left;
    //   motionR[i] = right;
    // }
    curvatureDrive(Controller1.Axis2.position(percent), -Controller1.Axis4.position(percent), Controller1.ButtonR1.pressing() || Controller1.ButtonL1.pressing());
    leftmotor.spin(forward, leftout * 30, pct);
    rightmotor.spin(forward, rightout * 30, pct);
    // vex::task::sleep(100);

    // for(int i = 0; i < 1000; i++){
    //   leftmotor.spin(forward, motionL[i], pct);
    //   rightmotor.spin(forward, motionR[i], pct);
    // }

    // //手臂
    // if (Controller1.ButtonL1.pressing()){
    //   armmotor.spin(forward,20,pct);
    // }
    // else if (Controller1.ButtonL2.pressing()){
    //   armmotor.spin(reverse,20,pct);
    // }
    // else{
    //   armmotor.spin(forward,0,pct);
    //   armmotor.stop(hold);
    // }  } 
    // //爪子
    // if (Controller1.ButtonR1.pressing()){
    //   crabmotor.spin(forward,200,pct);
    // }
    // else if (Controller1.ButtonR2.pressing()){
    //   crabmotor.spin(reverse,200,pct);
    // }
    // else{
    //   crabmotor.spin(forward,0,pct);
    //   crabmotor.stop(hold);
    // //button
    // if(Controller1.ButtonA.pressing()){
    //   leftmotor.spin(forward,50,pct);
    //   rightmotor.spin(forward,-50,pct);
    // }else if(Controller1.ButtonB.pressing()){
    //   leftmotor.spin(forward,-50,pct);
    //   rightmotor.spin(forward,50,pct);
    // }
  }








}
