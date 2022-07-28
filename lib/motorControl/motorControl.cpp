#include "motorControl.h"

using namespace motors;

DriveMotor::DriveMotor(PinName forwardPin, PinName reversePin){
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    speed = 0;      
}

void DriveMotor::setup(){
    pinMode(forwardPin,OUTPUT);
    pinMode(reversePin,OUTPUT);
}

void DriveMotor::setDirection(DriveMotor::Direction direction){
    this->direction = direction;
}

DriveMotor::Direction DriveMotor::getDirection(){
    return direction;
}

void DriveMotor::setSpeed(uint8_t speed){
    this->speed = speed;
}

uint8_t DriveMotor::getSpeed(){
    return speed;
}

uint8_t DriveMotor::toPWM(uint8_t speed){
    return speed;
}

void DriveMotor::updatePWMs(){
    uint8_t newForwardPinValue;
    uint8_t newReversePinValue;

    switch(direction){
        case DriveMotor::Direction::FORWARD:
            newForwardPinValue = toPWM(speed);
            newReversePinValue = 0;
            break;
        case DriveMotor::Direction::BACKWARD:
            newForwardPinValue = 0;
            newReversePinValue = toPWM(speed);
            break;
    }
    if(forwardPinValue != newForwardPinValue || reversePinValue != newReversePinValue){
        forwardPinValue = newForwardPinValue;
        reversePinValue = newReversePinValue;
        pwm_start(forwardPin, PWMFreq, forwardPinValue, RESOLUTION_7B_COMPARE_FORMAT);
        pwm_start(reversePin, PWMFreq, reversePinValue, RESOLUTION_7B_COMPARE_FORMAT);
    }
}



MotorManager::MotorManager(){
    motors[DRIVE_LEFT] = new DriveMotor(PA_9, PA_1);
    motors[DRIVE_RIGHT] = new DriveMotor(PA_0, PA_10);
}

MotorManager::~MotorManager(){
    for(DriveMotor* motor : motors){
        delete motor;
    }
}

void MotorManager::setup(){
    for(DriveMotor* motor : motors){
        motor->setup();
    }
}

void MotorManager::poll(){

    int8_t rightSpeed, leftSpeed;
    
    if(StateData::driveSpeed+StateData::driveSteer > INT8_MAX){
        leftSpeed = INT8_MAX;
        rightSpeed = INT8_MAX-2*StateData::driveSteer;
    } else if(StateData::driveSpeed+StateData::driveSteer < INT8_MIN){
        rightSpeed = INT8_MAX;
        leftSpeed = INT8_MAX-2*StateData::driveSteer;
    } else {
        leftSpeed = StateData::driveSpeed+StateData::driveSteer;
        rightSpeed = StateData::driveSpeed - StateData::driveSteer;
    }

    if(rightSpeed >= 0){
        motors[DRIVE_RIGHT]->setSpeed(rightSpeed);
        motors[DRIVE_RIGHT]->setDirection(DriveMotor::Direction::FORWARD);
    } else {
        motors[DRIVE_RIGHT]->setSpeed(-1*rightSpeed);
        motors[DRIVE_RIGHT]->setDirection(DriveMotor::Direction::BACKWARD);
    }

    if(leftSpeed >= 0){
        motors[DRIVE_LEFT]->setSpeed(leftSpeed);
        motors[DRIVE_LEFT]->setDirection(DriveMotor::Direction::FORWARD);
    } else {
        motors[DRIVE_LEFT]->setSpeed(-1*leftSpeed);
        motors[DRIVE_LEFT]->setDirection(DriveMotor::Direction::BACKWARD);
    }

    for(DriveMotor* motor : motors){
        motor->updatePWMs();
    }
}