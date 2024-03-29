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
#include <serialComm.h>

long int lastrun;
unsigned long lastSerial;

#include <servoControl.h>

//#define GPIO_AF0_SWJ           ((uint8_t)0x00)  



StateMachine::StateManager *stateManager = new StateMachine::StateManager();

lights::LightManager *lightManager = new lights::LightManager();

motors::MotorManager *motorManager = new motors::MotorManager();

trajectory::TrajectoryManager *trajectoryManager = new trajectory::TrajectoryManager();

sensors::SensorManager *sensorManager = new sensors::SensorManager();

bridge::BridgeManager *bridgeManager = new bridge::BridgeManager();

arm::ArmManager *armManager = new arm::ArmManager();
//servos::ServoManager *servoManager = new servos::ServoManager();
HMI::HMIManager* hmiManager = new HMI::HMIManager();

serialComm::SerialManager *serialManager = new serialComm::SerialManager();

void setup()
{
  lightManager->setup();
  motorManager->setup();
  // hmiManager->setup(); //hmi manager must be setup before sensor manager for reasons
  sensorManager->setup();
  //servoManager->setup();
  trajectoryManager->setup();
  serialManager->setup();

  StateData::persistent::getFromMemory();



  Serial.begin(9600);
  lastrun = millis();
  lastSerial = millis();
  //pinMode(PB3, OUTPUT);


}

void loop()
{
  sensorManager->poll();
  serialManager->poll(); // Place before trajectory manager etc to update data first.
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
  //servoManager->poll();
  // hmiManager->poll();

  // if (millis() - lastSerial >= 1000) {
  //   Serial.print("State: "); Serial.println(StateData::debugStateName.c_str());
  //   Serial.print("LF L/R: "); 
  //   Serial.print(StateData::reflectances::lineLeft); Serial.print(", ");
  //   Serial.print(StateData::reflectances::lineRight); Serial.print(", ");
  //   Serial.print("Corr: "); Serial.print(StateData::reflectances::correction); Serial.print(", ");
  //   // Serial.print("Speed: "); Serial.print(StateData::driveSpeed); Serial.print(", ");
  //   Serial.print("Steer: "); Serial.print(StateData::driveSteer); Serial.print(", ");
  //   Serial.print("Motors L/R: "); Serial.print(StateData::leftMotorSpeed); Serial.print(", ");
  //   Serial.print(StateData::rightMotorSpeed); Serial.print(", ");
  //   Serial.println();
  //   lastSerial = millis();
  // }

  if (millis() - lastSerial >= (unsigned long)1000) {
    Serial.print("Received: ");
    Serial.print(StateData::reflectances::lineLeft); Serial.print(", ");
    Serial.print(StateData::reflectances::lineRight); Serial.print(", ");
    Serial.print(StateData::reflectances::edgeReflectanceFL); Serial.print(", ");
    Serial.print(StateData::reflectances::edgeReflectanceFR); Serial.print(", ");
    Serial.print(StateData::reflectances::edgeReflectanceBL); Serial.print(", ");
    Serial.print(StateData::reflectances::edgeReflectanceBR); Serial.print(", ");
    Serial.print(StateData::sonar::sonarObjectAngle); Serial.print(", ");
    Serial.println();
    lastSerial = millis();
  }
}
