#include <Arduino.h>

#include <stateMachine.h>
#include <lights.h>
#include <motorControl.h>
#include <stateData.h>
#include <trajectoryPlanning.h>

StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

trajectory::TrajectoryManager *trajectoryManager = new trajectory::TrajectoryManager();

void setup()
{
  lightManager->setup();
  motorManager->setup();
}

void loop()
{
  stateManager->poll();
  lightManager->poll();
  motorManager->poll();
  trajectoryManager->poll();
  
  // below code good for testing motor control. Will be removed in a PR or two.
  /*if(*StateData::state == StateMachine::StateEnum::Error){
    StateData::driveSpeed = -64;
  } else {
    StateData::driveSpeed = 64;
  }*/
}