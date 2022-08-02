#include <Arduino.h>

#include <stateMachine.h>
#include <lights.h>
#include <motorControl.h>
#include <stateData.h>
#include <trajectoryPlanning.h>
#include <sensors.h>
#include <bridge.h>
#include <arm.h>

long int lastrun;

long int lastSerialSend;

#include <servoControl.h>

StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

trajectory::TrajectoryManager *trajectoryManager = new trajectory::TrajectoryManager();

sensors::SensorManager *sensorManager = new sensors::SensorManager();

bridge::BridgeManager *bridgeManager = new bridge::BridgeManager();

arm::ArmManager *armManager = new arm::ArmManager();
servos::ServoManager *servoManager = new servos::ServoManager();

void setup()
{
  lightManager->setup();
  motorManager->setup();
  sensorManager->setup();
  //servoManager->setup();
  lastSerialSend = 0;
  //servoManager->setup();
  trajectoryManager->setup();


  Serial.begin(9600);
  lastrun = millis();
}

void loop()
{

  // if(millis()>=lastSerialSend+1000){
  //   Serial.print("L, R: "); Serial.print(StateData::reflectances::leftReflectance);
  //   Serial.print(", "); Serial.print(StateData::reflectances::rightReflectance);
  //   Serial.print(", Speed: "); Serial.print(StateData::driveSpeed);
  //   Serial.print(", Steer: "); Serial.print(StateData::driveSteer);
  //   Serial.print(", Right Speed: "); Serial.print(StateData::rightMotorSpeed);
  //   Serial.print(", Left Speed: "); Serial.print(StateData::leftMotorSpeed);
  //   Serial.println();
  //   lastSerialSend = millis();
  // }
  if(millis()>=lastSerialSend+1000){
    Serial.print("(IR) L, R: "); Serial.print(StateData::IR::leftIRStrength);
    Serial.print(", "); Serial.print(StateData::IR::rightIRStrength);
    Serial.print(", Speed: "); Serial.print(StateData::driveSpeed);
    Serial.print(", Steer: "); Serial.print(StateData::driveSteer);
    Serial.print(", Right Speed: "); Serial.print(StateData::rightMotorSpeed);
    Serial.print(", Left Speed: "); Serial.print(StateData::leftMotorSpeed);
    Serial.println();
    lastSerialSend = millis();
  }
  sensorManager->poll();
  if (*StateData::state == StateMachine::StateEnum::Error)
  {
    StateData::clawServoPos = 180;
  }
  else
  {
    StateData::clawServoPos = 0;
  }

  stateManager->poll();
  lightManager->poll();
  motorManager->poll();
  trajectoryManager->poll();
  //bridgeManager->poll();
  //armManager->poll();
  //servoManager->poll();

}