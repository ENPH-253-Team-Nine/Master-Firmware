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


StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

trajectory::TrajectoryManager *trajectoryManager = new trajectory::TrajectoryManager();

sensors::SensorManager *sensorManager = new sensors::SensorManager();

bridge::BridgeManager *bridgeManager = new bridge::BridgeManager();

arm::ArmManager *armManager = new arm::ArmManager();

void setup()
{
  lightManager->setup();
  motorManager->setup();
  sensorManager->setup();

  Serial.begin(9600);
  lastrun = millis();
}

void loop()
{
  sensorManager->poll();
  stateManager->poll();
  lightManager->poll();
  motorManager->poll();
  trajectoryManager->poll();
  bridgeManager->poll();
  armManager->poll();

  
  // below code good for testing motor control. Will be removed in a PR or two.
  /*if(*StateData::state == StateMachine::StateEnum::Error){
    StateData::driveSpeed = -64;
  } else {
    StateData::driveSpeed = 64;
  }*/
}