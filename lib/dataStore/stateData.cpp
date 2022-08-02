#include "stateData.h"

StateMachine::StateEnum* StateData::state;

int8_t StateData::driveSpeed; //should we have setters and getters for these sorts of things?
int8_t StateData::driveSteer;



int StateData::IR::leftIRStrength;
int StateData::IR::rightIRStrength;
int StateData::IR::detectedThreshold;
int StateData::IR::kp;
int StateData::IR::kd;
int StateData::IR::lasterror;
int StateData::IR::setpoint;

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

int StateData::reflectances::kp;
int StateData::reflectances::kd;
int StateData::reflectances::detectedThreshold;
int StateData::reflectances::setpoint; 
int StateData::reflectances::lasterror;

int8_t StateData::rightMotorSpeed;
int8_t StateData::leftMotorSpeed;

long int StateData::lineLastNoContactTime;
