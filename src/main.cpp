#include <Arduino.h>

#include <stateMachine.h>
#include <lights.h>
#include <motorControl.h>
#include <stateData.h>
#include <trajectoryPlanning.h>
#include <sensors.h>
#include <bridge.h>
#include <arm.h>
#include <HMI.h>

long int lastrun;

#include <servoControl.h>

//#define GPIO_AF0_SWJ           ((uint8_t)0x00)  



StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

trajectory::TrajectoryManager *trajectoryManager = new trajectory::TrajectoryManager();

sensors::SensorManager *sensorManager = new sensors::SensorManager();

bridge::BridgeManager *bridgeManager = new bridge::BridgeManager();

arm::ArmManager *armManager = new arm::ArmManager();
servos::ServoManager *servoManager = new servos::ServoManager();
HMI::HMIManager* hmiManager = new HMI::HMIManager();

void setup()
{
  lightManager->setup();
  motorManager->setup();
  hmiManager->setup(); //hmi manager must be setup before sensor manager for reasons
  sensorManager->setup();
  servoManager->setup();


  Serial.begin(9600);
  lastrun = millis();
  //pinMode(PB3, OUTPUT);


}

void loop()
{
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
  bridgeManager->poll();
  armManager->poll();
  servoManager->poll();
  hmiManager->poll();
}