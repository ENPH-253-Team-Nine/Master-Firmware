#include "stateData.h"

StateMachine::StateEnum* StateData::state;

std::string StateData::debugStateName;

bool StateData::mockLED;

int8_t StateData::driveSpeed; //should we have setters and getters for these sorts of things?
int8_t StateData::driveSteer;

double StateData::IR::leftIRStrength;
double StateData::IR::rightIRStrength;

sensors::SwitchState StateData::switches::clawLimitSwitch;

double StateData::reflectances::clawReflectance;

double StateData::magnets::clawHall;

int StateData::encoders::leftEncoderCount;
int StateData::encoders::rightEncoderCount;
uint8_t armServoPos;
uint8_t clawServoPos;   
uint8_t StateData::elbowServoPos;
uint8_t StateData::clawServoPos;   

int StateData::testSettingOne;
int StateData::testSettingTwo;
int StateData::testSettingThree;
int StateData::testSettingFour;
int StateData::testSettingFive;
int StateData::testSettingSix;



int8_t StateData::HMI::settingSelectIndex;
int8_t StateData::HMI::settingLevel;

