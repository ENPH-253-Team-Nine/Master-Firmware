#include <Arduino.h>

#include <stateMachine.h>
#include <lights.h>

Lights::LightManager *lightManager = new Lights::LightManager();

StateMachine::StateManager *stateManager = new StateMachine::StateManager();

void setup()
{
  lightManager->setup();
}

void loop()
{
  stateManager->poll();
  lightManager->poll();
}