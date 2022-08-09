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

int StateData::sonar::sonarSweepTarget;

int8_t StateData::HMI::settingSelectIndex;
int8_t StateData::HMI::settingLevel;
bool StateData::HMI::HMIDisplayEnabled = true;

StateData::persistent::StoredSettings StateData::persistent::storedSettings;

uint8_t* StateData::persistent::storedSettings_bytes = reinterpret_cast<uint8_t *>(&StateData::persistent::storedSettings);

void StateData::persistent::getFromMemory(){
    eeprom_buffer_fill();
    for(int i=0; i<sizeof(StateData::persistent::storedSettings); i++){
        StateData::persistent::storedSettings_bytes[i]=eeprom_buffered_read_byte(i);
    }
}

void StateData::persistent::storeInMemory(){
    for(int i=0; i<sizeof(StateData::persistent::storedSettings); i++){
        eeprom_buffered_write_byte(i, StateData::persistent::storedSettings_bytes[i]);
    }
    eeprom_buffer_flush();
}

