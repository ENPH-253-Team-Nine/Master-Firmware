#include <Arduino.h>

#include <stateMachine.h>
#include <lights.h>
#include <motorControl.h>
#include <stateData.h>

StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

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

  if(*StateData::state == StateMachine::StateEnum::Error){
    StateData::driveSpeed = -64;
  } else {
    StateData::driveSpeed = 64;
  }
}