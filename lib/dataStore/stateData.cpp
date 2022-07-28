#include "stateData.h"

StateMachine::StateEnum* StateData::state;

int8_t StateData::driveSpeed; //should we have setters and getters for these sorts of things?
int8_t StateData::driveSteer;



double StateData::IR::leftIRStrength;
double StateData::IR::rightIRStrength;

sensors::SwitchState StateData::switches::clawLimitSwitch;

double StateData::reflectances::clawReflectance;
double StateData::reflectances::leftReflectance;
double StateData::reflectances::rightReflectance;

double StateData::magnets::clawHall;

int StateData::encoders::leftEncoderCount;
int StateData::encoders::rightEncoderCount;
uint8_t armServoPos;
uint8_t clawServoPos;   
uint8_t StateData::elbowServoPos;
uint8_t StateData::clawServoPos;   
